/*
 * Copyright 2012, Tim Baker <treectrl@users.sf.net>
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

#include "buildingpreferences.h"
#include "preferences.h"

#include <QDir>

using namespace BuildingEditor;

static const char *KEY_MAPS_DIRECTORY = "MapsDirectory";
static const char *KEY_TILE_SCALE = "MainWindow/CategoryScale";
static const char *KEY_SHOW_GRID = "ShowGrid";
static const char *KEY_GRID_COLOR = "GridColor";
static const char *KEY_HIGHLIGHT_FLOOR = "PreviewWindow/HighlightFloor";
static const char *KEY_HIGHLIGHT_ROOM = "HighlightRoom";
static const char *KEY_SHOW_WALLS = "PreviewWindow/ShowWalls";
static const char *KEY_SHOW_LOWER_FLOORS = "PreviewWindow/ShowLowerFloors";
static const char *KEY_SHOW_ONLY_FLOORS = "PreviewWindow/ShowOnlyFloors";
static const char *KEY_SHOW_OBJECTS = "PreviewWindow/ShowObjects";
static const char *KEY_HIGHLIGHT_UNLIT_ROOMS = "HighlightUnlitRooms";
static const char *KEY_OPENGL = "OpenGL";
static const char *KEY_LEVEL_ISO = "LevelIsomettric";

BuildingPreferences *BuildingPreferences::mInstance = 0;

BuildingPreferences *BuildingPreferences::instance()
{
    if (!mInstance)
        mInstance = new BuildingPreferences;
    return mInstance;
}

void BuildingPreferences::deleteInstance()
{
    delete mInstance;
    mInstance = 0;
}

/*
BuildingPreferences::BuildingPreferences(QObject *parent) :
    QObject(parent),
    mSettings(QLatin1String("TheIndieStone"), QLatin1String("BuildingEd"))
{
    mMapsDirectory = mSettings.value(QLatin1String(KEY_MAPS_DIRECTORY),
                                     Tiled::Internal::Preferences::instance()->mapsDirectory()).toString();
    mShowGrid = mSettings.value(QLatin1String(KEY_SHOW_GRID), true).toBool();
    mGridColor = mSettings.value(QLatin1String(KEY_GRID_COLOR), QColor(Qt::black).name()).toString();
    mHighlightFloor = mSettings.value(QLatin1String(KEY_HIGHLIGHT_FLOOR),
                                      true).toBool();
    mHighlightRoom = mSettings.value(QLatin1String(KEY_HIGHLIGHT_ROOM),
                                     true).toBool();
    mShowWalls = mSettings.value(QLatin1String(KEY_SHOW_WALLS),
                                 true).toBool();
    mShowObjects = mSettings.value(QLatin1String(KEY_SHOW_OBJECTS),
                                 true).toBool();
    mShowLowerFloors = mSettings.value(QLatin1String(KEY_SHOW_LOWER_FLOORS),
                                 true).toBool();
    mShowOnlyFloors = mSettings.value(QLatin1String(KEY_SHOW_ONLY_FLOORS),
                                 false).toBool();
    mHighlightUnlitRooms = mSettings.value(QLatin1String(KEY_HIGHLIGHT_UNLIT_ROOMS),
                                 false).toBool();
    mTileScale = mSettings.value(QLatin1String(KEY_TILE_SCALE),
                                 0.5).toReal();
    mUseOpenGL = mSettings.value(QLatin1String(KEY_OPENGL), false).toBool();
    mLevelIsometric = mSettings.value(QLatin1String(KEY_LEVEL_ISO), false).toBool();
}
*/

BuildingPreferences::BuildingPreferences(QObject *parent) :
    QObject(parent),
    mSettings(QDir::currentPath() + QLatin1String("/settings.ini"), QSettings::IniFormat)
{
    // Synchronisation des préférences avec des valeurs par défaut
    if (!mSettings.contains(QLatin1String(KEY_MAPS_DIRECTORY))) {
        mSettings.setValue(QLatin1String(KEY_MAPS_DIRECTORY),
                           Tiled::Internal::Preferences::instance()->mapsDirectory());
    }

    mMapsDirectory = mSettings.value(QLatin1String(KEY_MAPS_DIRECTORY)).toString();
    mShowGrid = mSettings.value(QLatin1String(KEY_SHOW_GRID), true).toBool();
    mGridColor = QColor(mSettings.value(QLatin1String(KEY_GRID_COLOR), QColor(Qt::black).name()).toString());
    mHighlightFloor = mSettings.value(QLatin1String(KEY_HIGHLIGHT_FLOOR), true).toBool();
    mHighlightRoom = mSettings.value(QLatin1String(KEY_HIGHLIGHT_ROOM), true).toBool();
    mShowWalls = mSettings.value(QLatin1String(KEY_SHOW_WALLS), true).toBool();
    mShowObjects = mSettings.value(QLatin1String(KEY_SHOW_OBJECTS), true).toBool();
    mShowLowerFloors = mSettings.value(QLatin1String(KEY_SHOW_LOWER_FLOORS), true).toBool();
    mShowOnlyFloors = mSettings.value(QLatin1String(KEY_SHOW_ONLY_FLOORS), false).toBool();
    mHighlightUnlitRooms = mSettings.value(QLatin1String(KEY_HIGHLIGHT_UNLIT_ROOMS), false).toBool();
    mTileScale = mSettings.value(QLatin1String(KEY_TILE_SCALE), 0.5).toReal();
    mUseOpenGL = mSettings.value(QLatin1String(KEY_OPENGL), false).toBool();
    mLevelIsometric = mSettings.value(QLatin1String(KEY_LEVEL_ISO), false).toBool();
}

QString BuildingPreferences::configPath() const
{
    return Tiled::Internal::Preferences::instance()->configPath();
}

QString BuildingPreferences::configPath(const QString &fileName) const
{
    return configPath() + QLatin1Char('/') + fileName;
}

void BuildingPreferences::setMapsDirectory(const QString &path)
{
    if (mMapsDirectory == path)
        return;
    mMapsDirectory = path;
    mSettings.setValue(QLatin1String(KEY_MAPS_DIRECTORY), path);
    emit mapsDirectoryChanged();
}

void BuildingPreferences::setShowGrid(bool show)
{
    if (show == mShowGrid)
        return;
    mShowGrid = show;
    mSettings.setValue(QLatin1String(KEY_SHOW_GRID), mShowGrid);
    emit showGridChanged(mShowGrid);
}

void BuildingPreferences::setGridColor(const QColor &gridColor)
{
    if (gridColor == mGridColor)
        return;
    mGridColor = gridColor;
    mSettings.setValue(QLatin1String(KEY_GRID_COLOR), mGridColor.name());
    emit gridColorChanged(mGridColor);
}

void BuildingPreferences::setHighlightFloor(bool highlight)
{
    if (highlight == mHighlightFloor)
        return;
    mHighlightFloor = highlight;
    mSettings.setValue(QLatin1String(KEY_HIGHLIGHT_FLOOR), mHighlightFloor);
    emit highlightFloorChanged(mHighlightFloor);
}

void BuildingPreferences::setHighlightRoom(bool highlight)
{
    if (highlight == mHighlightRoom)
        return;
    mHighlightRoom = highlight;
    mSettings.setValue(QLatin1String(KEY_HIGHLIGHT_ROOM), mHighlightRoom);
    emit highlightRoomChanged(mHighlightRoom);
}

void BuildingPreferences::setShowWalls(bool show)
{
    if (show == mShowWalls)
        return;
    mShowWalls = show;
    mSettings.setValue(QLatin1String(KEY_SHOW_WALLS), mShowWalls);
    emit showWallsChanged(mShowWalls);
}

void BuildingPreferences::setShowLowerFloors(bool show)
{
    if (show == mShowLowerFloors)
        return;
    mShowLowerFloors = show;
    mSettings.setValue(QLatin1String(KEY_SHOW_LOWER_FLOORS), mShowLowerFloors);
    emit showLowerFloorsChanged(mShowLowerFloors);
}

void BuildingPreferences::setShowOnlyFloors(bool show)
{
    if (show == mShowOnlyFloors)
        return;
    mShowOnlyFloors = show;
    mSettings.setValue(QLatin1String(KEY_SHOW_ONLY_FLOORS), mShowOnlyFloors);
    emit showOnlyFloorsChanged(mShowOnlyFloors);
}

void BuildingPreferences::setShowObjects(bool show)
{
    if (show == mShowObjects)
        return;
    mShowObjects = show;
    mSettings.setValue(QLatin1String(KEY_SHOW_OBJECTS), mShowObjects);
    emit showObjectsChanged(mShowObjects);
}

void BuildingPreferences::setHighlightUnlitRooms(bool show)
{
    if (show == mHighlightUnlitRooms)
        return;
    mHighlightUnlitRooms = show;
    mSettings.setValue(QLatin1String(KEY_HIGHLIGHT_UNLIT_ROOMS), mHighlightUnlitRooms);
    emit highlightUnlitRoomsChanged(mHighlightUnlitRooms);
}

void BuildingPreferences::setTileScale(qreal scale)
{
    if (scale == mTileScale)
        return;
    mTileScale = scale;
    mSettings.setValue(QLatin1String(KEY_TILE_SCALE), mTileScale);
    emit tileScaleChanged(mTileScale);
}

void BuildingPreferences::setUseOpenGL(bool useOpenGL)
{
    if (useOpenGL == mUseOpenGL)
        return;
    mUseOpenGL = useOpenGL;
    mSettings.setValue(QLatin1String(KEY_OPENGL), mUseOpenGL);
    emit useOpenGLChanged(mUseOpenGL);
}

void BuildingPreferences::setLevelIsometric(bool levels)
{
    if (levels == mLevelIsometric)
        return;
    mLevelIsometric = levels;
    mSettings.setValue(QLatin1String(KEY_LEVEL_ISO), mLevelIsometric);
    emit levelIsometricChanged(mLevelIsometric);
}
