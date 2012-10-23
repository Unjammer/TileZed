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

#include "buildingtiles.h"

#include "buildingobjects.h"
#include "simplefile.h"

#include "tilesetmanager.h"

#include "tile.h"
#include "tileset.h"

#include <qcoreapplication>

using namespace BuildingEditor;
using namespace Tiled;
using namespace Tiled::Internal;

/////

BuildingTiles *BuildingTiles::mInstance = 0;

BuildingTiles *BuildingTiles::instance()
{
    if (!mInstance)
        mInstance = new BuildingTiles;
    return mInstance;
}

void BuildingTiles::deleteInstance()
{
    delete mInstance;
    mInstance = 0;
}

BuildingTiles::~BuildingTiles()
{
    TilesetManager::instance()->removeReferences(tilesets());
}

BuildingTile *BuildingTiles::get(const QString &categoryName, const QString &tileName)
{
    Category *category = this->category(categoryName);
    return category->get(tileName);
}

QString BuildingTiles::nameForTile(const QString &tilesetName, int index)
{
    // The only reason I'm padding the tile index is so that the tiles are sorted
    // by increasing tileset name and index.
    return tilesetName + QLatin1Char('_') +
            QString(QLatin1String("%1")).arg(index, 3, 10, QLatin1Char('0'));
}

QString BuildingTiles::nameForTile(Tile *tile)
{
    return nameForTile(tile->tileset()->name(), tile->id());
}

bool BuildingTiles::parseTileName(const QString &tileName, QString &tilesetName, int &index)
{
    tilesetName = tileName.mid(0, tileName.lastIndexOf(QLatin1Char('_')));
    QString indexString = tileName.mid(tileName.lastIndexOf(QLatin1Char('_')) + 1);
    // Strip leading zeroes from the tile index
#if 1
    int i = 0;
    while (i < indexString.length() - 1 && indexString[i] == QLatin1Char('0'))
        i++;
    indexString.remove(0, i);
#else
    indexString.remove( QRegExp(QLatin1String("^[0]*")) );
#endif
    index = indexString.toInt();
    return true;
}

QString BuildingTiles::adjustTileNameIndex(const QString &tileName, int offset)
{
    QString tilesetName;
    int index;
    parseTileName(tileName, tilesetName, index);
    index += offset;
    return nameForTile(tilesetName, index);
}

QString BuildingTiles::normalizeTileName(const QString &tileName)
{
    QString tilesetName;
    int index;
    parseTileName(tileName, tilesetName, index);
    return nameForTile(tilesetName, index);
}

BuildingTile *BuildingTiles::tileForDoor(Door *door, const QString &tileName,
                                         bool isFrame)
{
    QString adjustedName = tileName;
    if (door->dir() == BaseMapObject::N)
        adjustedName = adjustTileNameIndex(tileName, 1);
    return get(QLatin1String(isFrame ? "door_frames" : "doors"), adjustedName);
}

BuildingTile *BuildingTiles::tileForWindow(Window *window, const QString &tileName)
{
    QString adjustedName = tileName;
    if (window->dir() == BaseMapObject::N)
        adjustedName = adjustTileNameIndex(tileName, 1);
    return get(QLatin1String("windows"), adjustedName);
}

BuildingTile *BuildingTiles::tileForStairs(Stairs *stairs, const QString &tileName)
{
    return get(QLatin1String("stairs"), tileName);
}

void BuildingTiles::addTileset(Tileset *tileset)
{
    mTilesetByName[tileset->name()] = tileset;
    TilesetManager::instance()->addReference(tileset);
}

void BuildingTiles::writeBuildingTilesTxt()
{
    SimpleFile simpleFile;
    foreach (BuildingTiles::Category *category, categories()) {
        SimpleFileBlock categoryBlock;
        categoryBlock.name = QLatin1String("category");
        categoryBlock.values += SimpleFileKeyValue(QLatin1String("label"),
                                                   category->label());
        categoryBlock.values += SimpleFileKeyValue(QLatin1String("name"),
                                                   category->name());
        SimpleFileBlock tileBlock;
        tileBlock.name = QLatin1String("tiles");
        foreach (BuildingTile *btile, category->tiles())
            tileBlock.values += SimpleFileKeyValue(QLatin1String("tile"),
                                                   btile->name());
        categoryBlock.blocks += tileBlock;
        simpleFile.blocks += categoryBlock;
    }
    QString path = QCoreApplication::applicationDirPath() + QLatin1Char('/')
            + QLatin1String("BuildingTiles.txt");
    simpleFile.write(path);
}

Tiled::Tile *BuildingTiles::tileFor(const QString &tileName)
{
    QString tilesetName;
    int index;
    parseTileName(tileName, tilesetName, index);
    if (!mTilesetByName.contains(tilesetName))
        return 0;
    if (index >= mTilesetByName[tilesetName]->tileCount())
        return 0;
    return mTilesetByName[tilesetName]->tileAt(index);
}

Tile *BuildingTiles::tileFor(BuildingTile *tile)
{
    if (!mTilesetByName.contains(tile->mTilesetName))
        return 0;
    if (tile->mIndex >= mTilesetByName[tile->mTilesetName]->tileCount())
        return 0;
    return mTilesetByName[tile->mTilesetName]->tileAt(tile->mIndex);
}

QString BuildingTiles::defaultExteriorWall() const
{
    return category(QLatin1String("exterior_walls"))->tileAt(0)->name();
}

QString BuildingTiles::defaultDoorTile() const
{
    return category(QLatin1String("doors"))->tileAt(0)->name();
}

QString BuildingTiles::defaultDoorFrameTile() const
{
    return category(QLatin1String("door_frames"))->tileAt(0)->name();
}

QString BuildingTiles::defaultWindowTile() const
{
    return category(QLatin1String("windows"))->tileAt(0)->name();
}

QString BuildingTiles::defaultStairsTile() const
{
    return category(QLatin1String("stairs"))->tileAt(0)->name();
}

/////

bool BuildingTiles::Category::usesTile(Tile *tile) const
{
    return mTileByName.contains(nameForTile(tile));
}

QRect BuildingTiles::Category::categoryBounds() const
{
    if (mName == QLatin1String("exterior_walls"))
        return QRect(0, 0, 4, 2);
    if (mName == QLatin1String("interior_walls"))
        return QRect(0, 0, 4, 2);
    if (mName == QLatin1String("floors"))
        return QRect(0, 0, 1, 1);
    if (mName == QLatin1String("doors"))
        return QRect(0, 0, 4, 1);
    if (mName == QLatin1String("door_frames"))
        return QRect(0, 0, 2, 1);
    if (mName == QLatin1String("windows"))
        return QRect(0, 0, 2, 1);
    if (mName == QLatin1String("stairs"))
        return QRect(0, 0, 3, 2);
    return QRect();
}

/////

QString BuildingTile::name() const
{
    return BuildingTiles::nameForTile(mTilesetName, mIndex);
}

/////
