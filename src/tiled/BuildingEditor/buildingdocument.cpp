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

#include "buildingdocument.h"

#include "building.h"
#include "buildingeditorwindow.h"
#include "buildingfloor.h"
#include "buildingobjects.h"
#include "buildingtemplates.h"

#include <QUndoStack>

using namespace BuildingEditor;

BuildingDocument::BuildingDocument(Building *building, const QString &fileName) :
    QObject(),
    mBuilding(building),
    mUndoStack(new QUndoStack(this))
{
}

void BuildingDocument::setCurrentFloor(BuildingFloor *floor)
{
    mCurrentFloor = floor;
    emit currentFloorChanged();
}

void BuildingDocument::setSelectedObjects(const QSet<BaseMapObject *> &selection)
{
    mSelectedObjects = selection;
    emit selectedObjectsChanged();
}

Room *BuildingDocument::changeRoomAtPosition(BuildingFloor *floor, const QPoint &pos, Room *room)
{
    Room *old = floor->GetRoomAt(pos);
    floor->SetRoomAt(pos, room);
    emit roomAtPositionChanged(floor, pos);
    return old;
}

QString BuildingDocument::changeEWall(const QString &tileName)
{
    QString old = mBuilding->exteriorWall();
    mBuilding->setExteriorWall(tileName);
    emit roomDefinitionChanged();
    return old;
}

QString BuildingDocument::changeWallForRoom(Room *room, const QString &tileName)
{
    QString old = room->Wall;
    room->Wall = tileName;
    emit roomDefinitionChanged();
    return old;
}

QString BuildingDocument::changeFloorForRoom(Room *room, const QString &tileName)
{
    QString old = room->Floor;
    room->Floor = tileName;
    emit roomDefinitionChanged();
    return old;
}

void BuildingDocument::insertFloor(int index, BuildingFloor *floor)
{
    building()->insertFloor(index, floor);
    emit floorAdded(floor);
}

void BuildingDocument::insertObject(BuildingFloor *floor, int index, BaseMapObject *object)
{
    Q_ASSERT(object->floor() == floor);
    floor->insertObject(index, object);
    emit objectAdded(object);
}

BaseMapObject *BuildingDocument::removeObject(BuildingFloor *floor, int index)
{
    BaseMapObject *object = floor->object(index);

    if (mSelectedObjects.contains(object)) {
        mSelectedObjects.remove(object);
        emit selectedObjectsChanged();
    }

    emit objectAboutToBeRemoved(object);
    floor->removeObject(index);
    emit objectRemoved(floor, index);
    return object;
}

QPoint BuildingDocument::moveObject(BaseMapObject *object, const QPoint &pos)
{
    QPoint old = object->pos();
    object->setPos(pos);
    emit objectMoved(object);
    return old;
}

BuildingTile *BuildingDocument::changeDoorTile(Door *door, BuildingTile *tile,
                                               bool isFrame)
{
    BuildingTile *old = door->mTile;
    isFrame ? door->mFrameTile = tile : door->mTile = tile;
    emit objectTileChanged(door);
    return old;
}

BuildingTile *BuildingDocument::changeObjectTile(BaseMapObject *object, BuildingTile *tile)
{
    BuildingTile *old = object->mTile;
    object->mTile = tile;
    emit objectTileChanged(object);
    return old;
}

void BuildingDocument::insertRoom(int index, Room *room)
{
    mBuilding->insertRoom(index, room);
    emit roomAdded(room);
}

Room *BuildingDocument::removeRoom(int index)
{
    Room *room = building()->room(index);
    emit roomAboutToBeRemoved(room);
    building()->removeRoom(index);
    emit roomRemoved(room);
    return room;
}

int BuildingDocument::reorderRoom(int index, Room *room)
{
    int oldIndex = building()->rooms().indexOf(room);
    building()->removeRoom(oldIndex);
    building()->insertRoom(index, room);
    emit roomsReordered();
    return oldIndex;
}

Room *BuildingDocument::changeRoom(Room *room, const Room *data)
{
    Room *old = new Room(room);
    room->copy(data);
    emit roomChanged(room);
    delete data;
    return old;
}

QVector<QVector<Room*> > BuildingDocument::swapFloorGrid(BuildingFloor *floor,
                                                         const QVector<QVector<Room*> > &grid)
{
    QVector<QVector<Room*> > old = floor->grid();
    floor->setGrid(grid);
    emit floorEdited(floor);
    return old;
}
