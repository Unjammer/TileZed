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

#include "buildingtmx.h"

#include "building.h"
#include "buildingeditorwindow.h"
#include "buildingfloor.h"
#include "buildingmap.h"
#include "buildingpreferences.h"
#include "buildingtemplates.h"
#include "buildingtiles.h"
#include "listofstringsdialog.h"
#include "simplefile.h"

#include "mapcomposite.h"
#include "mapmanager.h"
#include "preferences.h"
#include "tilemetainfomgr.h"
#include "tilesetmanager.h"
#include "tmxmapwriter.h"

#include "map.h"
#include "mapobject.h"
#include "objectgroup.h"
#include "tilelayer.h"
#include "tile.h"
#include "tileset.h"

#include <QDebug>
#include <QDir>
#include <QImage>

using namespace BuildingEditor;
using namespace Tiled;
using namespace Tiled::Internal;

static const char *TXT_FILE = "TMXConfig.txt";

BuildingTMX *BuildingTMX::mInstance = 0;

BuildingTMX *BuildingTMX::instance()
{
    if (!mInstance)
        mInstance = new BuildingTMX;
    return mInstance;
}

void BuildingTMX::deleteInstance()
{
    delete mInstance;
    mInstance = 0;
}

BuildingTMX::BuildingTMX()
{
}

QStringList BuildingTMX::tileLayerNamesForLevel(int level)
{
    QStringList ret;
    foreach (LayerInfo layerInfo, mLayers) {
        if (layerInfo.mType != LayerInfo::Tile)
            continue;
        QString layerName = layerInfo.mName;
        int level2;
        if (MapComposite::levelForLayer(layerName, &level2)) {
            if (level2 != level)
                continue;
            layerName = MapComposite::layerNameWithoutPrefix(layerName);
        }
        ret += layerName;
    }
    return ret;
}

bool BuildingTMX::exportTMX(Building *building, const QString &fileName)
{
    BuildingMap bmap(building);

    Map *map = bmap.mergedMap();
    if (map->orientation() == Map::LevelIsometric) {
        Map *isoMap = MapManager::instance()->convertOrientation(map, Map::Isometric);
        TilesetManager::instance()->removeReferences(map->tilesets());
        delete map;
        map = isoMap;
    }

    foreach (BuildingFloor *floor, building->floors()) {

        // The given map has layers required by the editor, i.e., Floors, Walls,
        // Doors, etc.  The TMXConfig.txt file may specify extra layer names.
        // So we need to insert any extra layers in the order specified in
        // TMXConfig.txt.  If the layer name has a N_ prefix, it is only added
        // to level N, otherwise it is added to every level.  Object layers are
        // added above *all* the tile layers in the map.
        int previousExistingLayer = -1;
        foreach (LayerInfo layerInfo, mLayers) {
            QString layerName = layerInfo.mName;
            int level;
            if (MapComposite::levelForLayer(layerName, &level)) {
                if (level != floor->level())
                    continue;
            } else {
                layerName = tr("%1_%2").arg(floor->level()).arg(layerName);
            }
            int n;
            if ((n = map->indexOfLayer(layerName)) >= 0) {
                previousExistingLayer = n;
                continue;
            }
            if (layerInfo.mType == LayerInfo::Tile) {
                TileLayer *tl = new TileLayer(layerName, 0, 0,
                                              map->width(), map->height());
                if (previousExistingLayer < 0)
                    previousExistingLayer = 0;
                map->insertLayer(previousExistingLayer + 1, tl);
                previousExistingLayer++;
            } else {
                ObjectGroup *og = new ObjectGroup(layerName,
                                                  0, 0, map->width(), map->height());
                map->addLayer(og);
            }
        }

        ObjectGroup *objectGroup = new ObjectGroup(tr("%1_RoomDefs").arg(floor->level()),
                                                   0, 0, map->width(), map->height());

        // Add the RoomDefs layer above all the tile layers
        map->addLayer(objectGroup);

        int delta = (building->floorCount() - 1 - floor->level()) * 3;
        if (map->orientation() == Map::LevelIsometric)
            delta = 0;
        QPoint offset(delta, delta); // FIXME: not for LevelIsometric
        foreach (Room *room, building->rooms()) {
            foreach (QRect rect, floor->roomRegion(room)) {
                MapObject *mapObject = new MapObject(room->internalName, tr("room"),
                                                     rect.topLeft() + offset,
                                                     rect.size());
                objectGroup->addObject(mapObject);
            }
        }
    }

    TmxMapWriter writer;
    bool ok = writer.write(map, fileName);
    if (!ok)
        mError = writer.errorString();
    TilesetManager::instance()->removeReferences(map->tilesets());
    delete map;
    return ok;
}

QString BuildingTMX::txtName()
{
    return QLatin1String(TXT_FILE);
}

QString BuildingTMX::txtPath()
{
    return BuildingPreferences::instance()->configPath(txtName());
}

#define VERSION0 0

// VERSION1
// Move tilesets block to Tilesets.txt
#define VERSION1 1
#define VERSION_LATEST VERSION1

bool BuildingTMX::readTxt()
{
#if 0
    // Make sure the user has chosen the Tiles directory.
    QString tilesDirectory = Preferences::instance()->tilesDirectory();
    QDir dir(tilesDirectory);
    if (tilesDirectory.isEmpty() || !dir.exists()) {
        mError = tr("The Tiles directory specified in the preferences doesn't exist!\n%1")
                .arg(tilesDirectory);
        return false;
    }
#endif

    QFileInfo info(txtPath());
    if (!info.exists()) {
        mError = tr("The %1 file doesn't exist.").arg(txtName());
        return false;
    }

    if (!upgradeTxt())
        return false;

    if (!mergeTxt())
        return false;

    QString path = info.canonicalFilePath();
    SimpleFile simple;
    if (!simple.read(path)) {
        mError = simple.errorString();
        return false;
    }

    if (simple.version() != VERSION_LATEST) {
        mError = tr("Expected %1 version %2, got %3")
                .arg(txtName()).arg(VERSION_LATEST).arg(simple.version());
        return false;
    }

    mRevision = simple.value("revision").toInt();
    mSourceRevision = simple.value("source_revision").toInt();

#if 0
    QStringList missingTilesets;
#endif

    foreach (SimpleFileBlock block, simple.blocks) {
#if 0
        if (block.name == QLatin1String("tilesets")) {
            foreach (SimpleFileKeyValue kv, block.values) {
                if (kv.name == QLatin1String("tileset")) {
                    QString source = tilesDirectory + QLatin1Char('/') + kv.value
                            + QLatin1String(".png");
                    QFileInfo info(source);
                    if (!info.exists()) {
                        Tileset *ts = new Tileset(info.completeBaseName(), 64, 128);
                        // I could save the tileset image height/width and create
                        // a complete "missing" image here, instead I only have
                        // a single tile.
                        ts->loadFromImage(TilesetManager::instance()->missingTile()->image().toImage(),
                                          kv.value + QLatin1String(".png"));
                        ts->setMissing(true);
                        BuildingTilesMgr::instance()->addTileset(ts);
                        mTilesets += ts->name();
                        missingTilesets += QDir::toNativeSeparators(info.absoluteFilePath());
                        continue;
                    }
                    source = info.canonicalFilePath();
                    Tileset *ts = loadTileset(source);
                    if (!ts)
                        return false;
                    BuildingTilesMgr::instance()->addTileset(ts);
                    mTilesets += ts->name();
                } else {
                    mError = tr("Unknown value name '%1'.\n%2")
                            .arg(kv.name)
                            .arg(path);
                    return false;
                }
            }
        } else
#endif
            if (block.name == QLatin1String("layers")) {
            foreach (SimpleFileKeyValue kv, block.values) {
                if (kv.name == QLatin1String("tile")) {
                    mLayers += LayerInfo(kv.value, LayerInfo::Tile);
                } else if (kv.name == QLatin1String("object")) {
                    mLayers += LayerInfo(kv.value, LayerInfo::Object);
                } else {
                    mError = tr("Unknown layer type '%1'.\n%2")
                            .arg(kv.name)
                            .arg(path);
                    return false;
                }
            }
        } else {
            mError = tr("Unknown block name '%1'.\n%2")
                    .arg(block.name)
                    .arg(path);
            return false;
        }
    }

    // Check that TMXConfig.txt contains all the required tile layers.
    foreach (QString layerName, BuildingMap::requiredLayerNames()) {
        bool match = false;
        foreach (LayerInfo layerInfo, mLayers) {
            if (layerInfo.mType == LayerInfo::Tile && layerInfo.mName == layerName) {
                match = true;
                break;
            }
        }
        if (!match) {
            mError = tr("TMXConfig.txt is missing a required tile layer: %1")
                    .arg(layerName);
            return false;
        }
    }

#if 0
    if (missingTilesets.size()) {
        ListOfStringsDialog dialog(tr("The following tileset files were not found."),
                                   missingTilesets,
                                   BuildingEditorWindow::instance());
        dialog.setWindowTitle(tr("Missing Tilesets"));
        dialog.exec();
    }
#endif

    return true;
}

bool BuildingTMX::writeTxt()
{
    SimpleFile simpleFile;

    QDir tilesDir(Preferences::instance()->tilesDirectory());
#if 0
    SimpleFileBlock tilesetBlock;
    tilesetBlock.name = QLatin1String("tilesets");
    foreach (Tiled::Tileset *tileset, BuildingTilesMgr::instance()->tilesets()) {
        QString relativePath = tilesDir.relativeFilePath(tileset->imageSource());
        relativePath.truncate(relativePath.length() - 4); // remove .png
        tilesetBlock.values += SimpleFileKeyValue(QLatin1String("tileset"), relativePath);
    }
    simpleFile.blocks += tilesetBlock;
#endif
    SimpleFileBlock layersBlock;
    layersBlock.name = QLatin1String("layers");
    foreach (LayerInfo layerInfo, mLayers) {
        QString key;
        switch (layerInfo.mType) {
        case LayerInfo::Tile: key = QLatin1String("tile"); break;
        case LayerInfo::Object: key = QLatin1String("object"); break;
        }
        layersBlock.values += SimpleFileKeyValue(key, layerInfo.mName);
    }
    simpleFile.blocks += layersBlock;

    simpleFile.setVersion(VERSION_LATEST);
    simpleFile.replaceValue("revision", QString::number(++mRevision));
    simpleFile.replaceValue("source_revision", QString::number(mSourceRevision));
    if (!simpleFile.write(txtPath())) {
        mError = simpleFile.errorString();
        return false;
    }
    return true;
}

Tiled::Tileset *BuildingTMX::loadTileset(const QString &source)
{
    QFileInfo info(source);

    Tileset *ts = new Tileset(info.completeBaseName(), 64, 128);

    TilesetImageCache *cache = TilesetManager::instance()->imageCache();
    Tileset *cached = cache->findMatch(ts, source);
    if (!cached || !ts->loadFromCache(cached)) {
        const QImage tilesetImage = QImage(source);
        if (ts->loadFromImage(tilesetImage, source))
            cache->addTileset(ts);
        else {
            delete ts;
            mError = tr("Error loading tileset image:\n'%1'").arg(source);
            return 0;
        }
    }
    return ts;
}

bool BuildingTMX::upgradeTxt()
{
    QString userPath = txtPath();

    SimpleFile userFile;
    if (!userFile.read(userPath)) {
        mError = userFile.errorString();
        return false;
    }

    int userVersion = userFile.version(); // may be zero for unversioned file
    if (userVersion == VERSION_LATEST)
        return true;

    if (userVersion > VERSION_LATEST) {
        mError = tr("%1 is from a newer version of TileZed").arg(txtName());
        return false;
    }

    // Not the latest version -> upgrade it.

    QString sourcePath = QCoreApplication::applicationDirPath() + QLatin1Char('/')
            + txtName();

    SimpleFile sourceFile;
    if (!sourceFile.read(sourcePath)) {
        mError = sourceFile.errorString();
        return false;
    }
    Q_ASSERT(sourceFile.version() == VERSION_LATEST);

    // UPGRADE HERE
    if (userVersion == VERSION0) {
        int index = userFile.findBlock(QLatin1String("tilesets"));
        if (index >= 0) {
            SimpleFileBlock tilesetsBlock = userFile.blocks[index];
            foreach (SimpleFileKeyValue kv, tilesetsBlock.values) {
                QString tilesetName = QFileInfo(kv.value).completeBaseName();
                if (TileMetaInfoMgr::instance()->tileset(tilesetName) == 0) {
                    Tileset *ts = new Tileset(tilesetName, 64, 128);
                    // Since the tileset image height/width wasn't saved, create
                    // a tileset with only a single tile.
                    ts->loadFromImage(TilesetManager::instance()->missingTile()->image().toImage(),
                                      kv.value + QLatin1String(".png"));
                    ts->setMissing(true);
                    TileMetaInfoMgr::instance()->addTileset(ts);
                }
            }
            userFile.blocks.removeAt(index);
            TileMetaInfoMgr::instance()->writeTxt();
        }
    }

    userFile.setVersion(VERSION_LATEST);
    if (!userFile.write(userPath)) {
        mError = userFile.errorString();
        return false;
    }
    return true;
}

bool BuildingTMX::mergeTxt()
{
    QString userPath = txtPath();

    SimpleFile userFile;
    if (!userFile.read(userPath)) {
        mError = userFile.errorString();
        return false;
    }
    Q_ASSERT(userFile.version() == VERSION_LATEST);

    QString sourcePath = QCoreApplication::applicationDirPath() + QLatin1Char('/')
            + txtName();

    SimpleFile sourceFile;
    if (!sourceFile.read(sourcePath)) {
        mError = sourceFile.errorString();
        return false;
    }
    Q_ASSERT(sourceFile.version() == VERSION_LATEST);

    int userSourceRevision = userFile.value("source_revision").toInt();
    int sourceRevision = sourceFile.value("revision").toInt();
    if (sourceRevision == userSourceRevision)
        return true;

    // MERGE HERE

    int tilesetBlock = -1;
    int layersBlock = -1;
    QMap<QString,SimpleFileKeyValue> userTilesetMap;
    QMap<QString,int> userLayersMap;
    int blockIndex = 0;
    foreach (SimpleFileBlock b, userFile.blocks) {
        if (b.name == QLatin1String("tilesets")) {
            foreach (SimpleFileKeyValue kv, b.values) {
                userTilesetMap[kv.value] = kv;
            }
            tilesetBlock = blockIndex;
        } else if (b.name == QLatin1String("layers"))  {
            int layerIndex = 0;
            foreach (SimpleFileKeyValue kv, b.values)
                userLayersMap[kv.value] = layerIndex++;
            layersBlock = blockIndex;
        }
        ++blockIndex;
    }

    foreach (SimpleFileBlock b, sourceFile.blocks) {
        if (b.name == QLatin1String("tilesets")) {
            foreach (SimpleFileKeyValue kv, b.values) {
                if (!userTilesetMap.contains(kv.value)) {
                    userFile.blocks[tilesetBlock].values += kv;
                    qDebug() << "TMXConfig.txt merge: added tileset" << kv.value;
                }
            }
        } else if (b.name == QLatin1String("layers"))  {
            int insertIndex = 0;
            foreach (SimpleFileKeyValue kv, b.values) {
                if (userLayersMap.contains(kv.value)) {
                    insertIndex = userLayersMap[kv.value] + 1;
                } else {
                    userFile.blocks[layersBlock].values.insert(insertIndex, kv);
                    userLayersMap[kv.value] = insertIndex;
                    qDebug() << "TMXConfig.txt merge: added layer" << kv.value << "at" << insertIndex;
                    insertIndex++;
                }
            }
        }
    }

    userFile.replaceValue("revision", QString::number(sourceRevision + 1));
    userFile.replaceValue("source_revision", QString::number(sourceRevision));

    userFile.setVersion(VERSION_LATEST);
    if (!userFile.write(userPath)) {
        mError = userFile.errorString();
        return false;
    }
    return true;
}
