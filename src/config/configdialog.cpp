#include "configdialog.h"
#include "ui_configdialog.h"

#include <QFileDialog>
#include <QDir>
#include <QSettings>

static QString KEY_CONFIG_DIR = QLatin1String("ConfigDirectory");

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);

    // Utiliser le fichier settings.ini
    QSettings settings(QDir::currentPath() + QLatin1String("/settings.ini"), QSettings::IniFormat);

    QString defaultPath = QDir::currentPath() + QLatin1String("/../") + QLatin1String(".TileZed");
    QString configPath = settings.value(KEY_CONFIG_DIR, defaultPath).toString();
    ui->configDirectory->setText(configPath);

    connect(ui->configBrowse, &QAbstractButton::clicked, this, &ConfigDialog::configBrowse);
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::configBrowse()
{
    QString f = QFileDialog::getExistingDirectory(this, tr("Config Directory"),
                                                  ui->configDirectory->text());
    if (!f.isEmpty()) {
        ui->configDirectory->setText(QDir::toNativeSeparators(f));
    }
}

void ConfigDialog::accept()
{
    // Sauvegarder dans le fichier settings.ini
    QSettings settings(QDir::currentPath() + QLatin1String("/settings.ini"), QSettings::IniFormat);
    settings.setValue(KEY_CONFIG_DIR, ui->configDirectory->text());
    QDialog::accept();
}
