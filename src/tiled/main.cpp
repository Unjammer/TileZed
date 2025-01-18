/*
 * main.cpp
 * Copyright 2008-2011, Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
 * Copyright 2011, Ben Longbons <b.r.longbons@gmail.com>
 * Copyright 2011, Stefan Beller <stefanbeller@googlemail.com>
 *
 * This file is part of Tiled.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "commandlineparser.h"
#include "mainwindow.h"
#include "languagemanager.h"
#include "preferences.h"
#include "tiledapplication.h"
#include "logger.h"
#ifdef ZOMBOID
#include "worlded/worldedmgr.h"
#include "zprogress.h"
#include <QFileInfo>
#include <QMessageBox>
#endif

#include <QDebug>
#include <QtPlugin>
#include <QDir>

#ifdef STATIC_BUILD
Q_IMPORT_PLUGIN(qgif)
Q_IMPORT_PLUGIN(qjpeg)
Q_IMPORT_PLUGIN(qtiff)
#endif

#define STRINGIFY(x) #x
#define AS_STRING(x) STRINGIFY(x)

using namespace Tiled::Internal;

#ifdef ZOMBOID
bool gStartupBlockRendering = true;
#endif

namespace {

class CommandLineHandler : public CommandLineParser
{
public:
    CommandLineHandler();

    bool quit;
    bool showedVersion;
    bool disableOpenGL;

private:
    void showVersion();
    void justQuit();
    void setDisableOpenGL();

    // Convenience wrapper around registerOption
    template <void (CommandLineHandler::*memberFunction)()>
    void option(QChar shortName,
                const QString &longName,
                const QString &help)
    {
        registerOption<CommandLineHandler, memberFunction>(this,
                                                           shortName,
                                                           longName,
                                                           help);
    }
};

} // anonymous namespace


CommandLineHandler::CommandLineHandler()
    : quit(false)
    , showedVersion(false)
    , disableOpenGL(false)
{
    option<&CommandLineHandler::showVersion>(
                QLatin1Char('v'),
                QLatin1String("--version"),
                QLatin1String("Display the version"));

    option<&CommandLineHandler::justQuit>(
                QChar(),
                QLatin1String("--quit"),
                QLatin1String("Only check validity of arguments, "
                              "don't actually load any files"));

    option<&CommandLineHandler::setDisableOpenGL>(
                QChar(),
                QLatin1String("--disable-opengl"),
                QLatin1String("Disable hardware accelerated rendering"));
}

void CommandLineHandler::showVersion()
{
    if (!showedVersion) {
        showedVersion = true;
        qWarning() << "Tiled (Qt) Map Editor"
                   << qPrintable(QApplication::applicationVersion());
        quit = true;
    }
}

void CommandLineHandler::justQuit()
{
    quit = true;
}

void CommandLineHandler::setDisableOpenGL()
{
    disableOpenGL = true;
}

#if !defined(QT_NO_DEBUG) && defined(ZOMBOID) && defined(_MSC_VER)
static void __cdecl invalid_parameter_handler(
   const wchar_t * expression,
   const wchar_t * function,
   const wchar_t * file,
   unsigned int line,
   uintptr_t pReserved)
{
    qDebug() << expression << function << file << line;
}

#endif

int main(int argc, char *argv[])
{
#if !defined(QT_NO_DEBUG) && defined(ZOMBOID) && defined(_MSC_VER)
    _set_invalid_parameter_handler(invalid_parameter_handler);
#endif

    /*
     * On X11, Tiled uses the 'raster' graphics system by default, because the
     * X11 native graphics system has performance problems with drawing the
     * tile grid.
     */
#ifdef Q_WS_X11
    QApplication::setGraphicsSystem(QLatin1String("raster"));
#endif

    TiledApplication a(argc, argv);

#ifdef ZOMBOID
    Q_INIT_RESOURCE(buildingeditor);
#endif

    a.setOrganizationName(QLatin1String("TheIndieStone"));
    a.setApplicationName(QLatin1String("TileZed"));
#ifdef BUILD_INFO_VERSION
    a.setApplicationVersion(QLatin1String(AS_STRING(BUILD_INFO_VERSION)));
#else
    a.setApplicationVersion(QLatin1String("0.8.1"));
#endif

    QDir::setCurrent(QDir::currentPath());
    Preferences *prefs = Preferences::instance();

#ifdef Q_WS_MAC
    a.setAttribute(Qt::AA_DontShowIconsInMenus);
#endif

    LanguageManager *languageManager = LanguageManager::instance();
    languageManager->installTranslators();

    CommandLineHandler commandLine;

    if (!commandLine.parse(QCoreApplication::arguments()))
        return 0;
    if (commandLine.quit)
        return 0;
    if (commandLine.disableOpenGL)
        Preferences::instance()->setUseOpenGL(false);

#ifdef ZOMBOID
    if (a.isRunning()) {
        if (!commandLine.filesToOpen().isEmpty()) {
            foreach (const QString &fileName, commandLine.filesToOpen())
                a.sendMessage(fileName);
            return 0;
        }
    }
#endif
    Logger::instance().log(QLatin1String("Main - Start : %1").arg(a.applicationName()), QLatin1String("INFO"));

    if (prefs->enableDarkTheme())
    {
        QString fileName = QDir::currentPath() + QLatin1String("/theme/") + prefs->themes();
        Logger::instance().log(QLatin1String("MainWindow - Theme : %1").arg(fileName), QLatin1String("INFO"));
        QFile file(fileName);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&file);
        QString stylesheet = in.readAll();

        a.setStyleSheet(stylesheet);
    }
    Logger::instance().log(QLatin1String("Main - Start 2 : %1").arg(a.applicationName()), QLatin1String("INFO"));

    MainWindow w;
#ifdef ZOMBOID
    ZProgressManager::instance()->setMainWindow(&w);
#endif
    w.show();
#ifdef ZOMBOID
    a.setActivationWindow(&w);
    w.connect(&a, &QtSingleApplication::messageReceived, &w, qOverload<const QString&>(&MainWindow::openFile));
    w.readSettings();

    if (!w.InitConfigFiles())
        return 0;

    foreach (QString f, Preferences::instance()->worldedFiles()) {
        if (f.isEmpty())
            continue;
        if (QFileInfo::exists(f) == false) {
            QMessageBox::warning(&w, QLatin1String("Missing PZW"), QLatin1String("WorldEd project not found:\n%1").arg(f));
            continue;
        }
        WorldEd::WorldEdMgr::instance()->addProject(f);
    }

    for (const QString &f : Preferences::instance()->tilePropertiesFiles()) {
        if (f.isEmpty())
            continue;
        if (QFileInfo::exists(f) == false) {
            QMessageBox::warning(&w, QLatin1String("File Not Found"), QLatin1String("Tile properties file not found.\nChange this in the Preferences.\n%1").arg(f));
            continue;
        }
    }
#endif // ZOMBOID

    QObject::connect(&a, &TiledApplication::fileOpenRequest,
                     &w, qOverload<const QString&>(&MainWindow::openFile));

    if (!commandLine.filesToOpen().isEmpty()) {
#ifdef ZOMBOID
        gStartupBlockRendering = false;
#endif
        foreach (const QString &fileName, commandLine.filesToOpen())
            w.openFile(fileName);
    } else {
        w.openLastFiles();
    }

    return a.exec();
}
