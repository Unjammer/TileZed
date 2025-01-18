/*
 * Copyright 2013, Tim Baker <treectrl@users.sf.net>
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

#ifndef LUATILED_H
#define LUATILED_H

#include <QColor>
#include <QList>
#include <QMap>
#include <QRegion>
#include <QRgb>

extern "C" {
struct lua_State;
}

namespace Tiled {
class BmpAlias;
class BmpBlend;
class BmpRule;
class Layer;
class Map;
class MapBmp;
class MapNoBlend;
class MapObject;
class ObjectGroup;
class Tile;
class TileLayer;
class Tileset;

namespace Lua {

class LuaMap;
class LuaObjectGroup;
class LuaTileLayer;

class TileName
{
public:
    QString mTilesetName;
    int mTileID;

    TileName(const char *tileName);
    TileName(const QString &tileName);

    bool isValid() { return !mTilesetName.isEmpty(); }
    QString tileset() { return mTilesetName; }
    int id() { return mTileID; }
};

class LuaColor
{
public:
    LuaColor() :
        r(0), g(0), b(0), pixel(qRgb(0, 0, 0))
    {}
    LuaColor(int r, int g, int b) :
        r(r), g(g), b(b), pixel(qRgb(r, g, b))
    {}
    LuaColor(QRgb pixel) :
        r(qRed(pixel)),
        g(qGreen(pixel)),
        b(qBlue(pixel)),
        pixel(pixel)
    {}

    int r;
    int g;
    int b;
    QRgb pixel;
};

// Only reason for this class is because tolua doesn't handle operator+= etc.
// unite() and intersect() aren't QRegion methods.
class LuaRegion : public QRegion
{
public:

    LuaRegion() : QRegion() {}
    LuaRegion(const QRegion &rgn) : QRegion(rgn) {}

    QVector<QRect> rects() const
    {
        return QVector<QRect>(begin(), end());
    }

    void unite(int x, int y, int w, int h) { *this += QRect(x, y, w, h); }
    void unite(QRect &rect) { *this += rect; }
    void unite(LuaRegion &rgn) { *this += rgn; }

    void intersect(int x, int y, int w, int h) { *this &= QRect(x, y, w, h); }
    void intersect(QRect &rect) { *this &= rect; }
    void intersect(LuaRegion &rgn) { *this &= rgn; }
};

class LuaLayer
{
public:
    LuaLayer();
    LuaLayer(Layer *orig);
    virtual ~LuaLayer();

    const char *name() const;
    const char *nameWithPrefix() const;
    const QString nameWithPrefixQString() const;

    int level() const { return mLevel; }

    virtual LuaTileLayer *asTileLayer() { return 0; }
    virtual LuaObjectGroup *asObjectGroup() { return 0; }

    virtual const char *type() const { return "unknown"; }

    void initClone();
    virtual void cloned();

    Layer *mClone;
    Layer *mOrig;
    QString mName;
    int mLevel;
};

class LuaTileLayer : public LuaLayer
{
public:
    LuaTileLayer(TileLayer *orig);
    LuaTileLayer(const char *name, int x, int y, int width, int height);
    ~LuaTileLayer();

    LuaTileLayer *asTileLayer() { return this; }
    const char *type() const { return "tile"; }

    void cloned();
    int level();
    void setTile(int x, int y, Tile *tile);
    Tile *tileAt(int x, int y);

    void clearTile(int x, int y);

    void erase(int x, int y, int width, int height);
    void erase(const QRect &r);
    void erase(const LuaRegion &rgn);
    void erase();

    void fill(int x, int y, int width, int height, Tile *tile);
    void fill(const QRect &r, Tile *tile);
    void fill(const LuaRegion &rgn, Tile *tile);
    void fill(Tile *tile);

    bool replaceTile(Tile *oldTile, Tile *newTile);
    bool replaceTiles(QList<Tile*> &tiles);

    TileLayer *mCloneTileLayer;
    QRegion mAltered;
    LuaMap *mMap;
};


class LuaMapObject
{
public:
    LuaMapObject(MapObject *orig);
    LuaMapObject(const char *name, const char *type, int x, int y, int width, int height);

    const char *name();
    const char *type();

    QRect bounds();

    MapObject *mClone;
    MapObject *mOrig;
};

class LuaObjectGroup : public LuaLayer
{
public:
    LuaObjectGroup(ObjectGroup *orig);
    LuaObjectGroup(const char *name, int x, int y, int width, int height);
    ~LuaObjectGroup();

    virtual LuaObjectGroup *asObjectGroup() { return this; }

    void cloned();

    void setColor(LuaColor &color);
    LuaColor color();

    void addObject(LuaMapObject *object);
    void insertObject(int index, LuaMapObject* object);
    QList<LuaMapObject*> objects();

    ObjectGroup *mCloneObjectGroup;
    ObjectGroup *mOrig;
    QList<LuaMapObject*> mObjects;
    QList<LuaMapObject*> mRemovedObjects;
    QMap<QString, LuaMapObject*> mObjectsByName;
    QColor mColor;
};

class LuaMapBmp
{
public:
    LuaMapBmp(MapBmp &bmp);

    bool contains(int x, int y);

    void setPixel(int x, int y, const LuaColor &c);
    unsigned int pixel(int x, int y);

    void erase(int x, int y, int width, int height);
    void erase(const QRect &r);
    void erase(const LuaRegion &rgn);
    void erase();

    void fill(int x, int y, int width, int height, const LuaColor &c);
    void fill(const QRect &r, const LuaColor &c);
    void fill(const LuaRegion &rgn, const LuaColor &c);
    void fill(const LuaColor &c);

    void replace(const LuaColor &oldColor, const LuaColor &newColor);

    unsigned int rand(int x, int y);

    MapBmp &mBmp;
    QRegion mAltered;
};

class LuaBmpAlias
{
public:
    LuaBmpAlias(BmpAlias *alias) :
        mAlias(alias)
    {}

    QStringList tiles();

    BmpAlias *mAlias;
};

class LuaBmpRule
{
public:
    LuaBmpRule() :
        mRule(0)
    {}
    LuaBmpRule(BmpRule *rule) :
        mRule(rule)
    {}

    const char *label();
    int bmpIndex();
    LuaColor color();
    QStringList tiles();
    const char *layer();
    LuaColor condition();

    BmpRule *mRule;
};

class LuaBmpBlend
{
public:
    LuaBmpBlend(BmpBlend *blend) :
        mBlend(blend)
    {}

    enum Direction {
        Unknown,
        N,
        S,
        E,
        W,
        NW,
        NE,
        SW,
        SE
    };

    const char *layer();
    const char *mainTile();
    const char *blendTile();
    Direction direction();
    QStringList exclude();

    BmpBlend *mBlend;
};

class LuaMapNoBlend
{
public:
    LuaMapNoBlend(MapNoBlend *clone);
    ~LuaMapNoBlend();

    void set(int x, int y, bool noblend);
    void set(const LuaRegion &rgn, bool noblend);
    bool get(int x, int y);

    MapNoBlend *mClone;
    QRegion mAltered;
};

class LuaMap
{
public:
    enum Orientation {
        Unknown,
        Orthogonal,
        Isometric,
        LevelIsometric,
        Staggered
    };

    LuaMap(Map *orig);
    LuaMap(Map *orig, int cellX, int cellY);
    LuaMap(Orientation orient, int width, int height, int tileWidth, int tileHeight);
    ~LuaMap();

    Orientation orientation();

    void setTileSelection(const LuaRegion &selection)
    { mSelection = selection; }

    LuaRegion tileSelection()
    { return mSelection; }

    int width() const;
    int height() const;

    int maxLevel();

    int layerCount() const;
    LuaLayer *layerAt(int index) const;
    LuaLayer *layer(const char *name);
    LuaTileLayer *tileLayer(const char *name);

    LuaObjectGroup *objectLayer(const char *name);

    LuaTileLayer *newTileLayer(const char *name);
    LuaObjectGroup *newObjectLayer(const char *name);

    void addLayer(LuaLayer *layer);
    void insertLayer(int index, LuaLayer *layer);
    void removeLayer(int index);

    Tile *tile(const char *name);
    Tile *tile(const char *tilesetName, int tileID);
    static Tile *noneTile();

    void addTileset(Tileset *tileset);
    int tilesetCount();
    Tileset *_tileset(const QString &name);
    Tileset *tileset(const char *name);
    Tileset *tilesetAt(int index);

    void replaceTilesByName(const char *names);

    LuaMapBmp &bmp(int index);

    void reloadRules();
    void reloadBlends();

    QList<LuaBmpAlias*> aliases();
    LuaBmpAlias *alias(const char *name);

    int ruleCount();
    QList<LuaBmpRule*> rules();
    LuaBmpRule *ruleAt(int index);
    LuaBmpRule *rule(const char *name);

    QList<LuaBmpBlend*> blends();
    bool isBlendTile(Tile *tile);
    QList<QString> blendLayers();

    LuaMapNoBlend *noBlend(const char *layerName);

    bool write(const char *path);

    int cellX() { return mCellX; }
    int cellY() { return mCellY; }

    Map *mClone;
    Map *mOrig;
    QMap<QString,Tileset*> mTilesetByName;
    QList<Tileset*> mNewTilesets;
    QList<LuaLayer*> mLayers;
    QList<LuaLayer*> mRemovedLayers;
    QMap<QString,LuaLayer*> mLayerByName;
    LuaRegion mSelection;
    LuaMapBmp mBmpMain;
    LuaMapBmp mBmpVeg;

    QList<LuaBmpAlias*> mAliases;
    QMap<QString,LuaBmpAlias*> mAliasByName;

    QList<LuaBmpRule*> mRules;
    QMap<QString,LuaBmpRule*> mRuleByName;

    QList<LuaBmpBlend*> mBlends;

    QMap<QString,LuaMapNoBlend*> mNoBlends;

    bool mRulesChanged;
    bool mBlendsChanged;

    int mCellX;
    int mCellY;
};

class LuaScript
{
public:
    LuaScript(Map *map);
    LuaScript(Map *map, int cellX, int cellY);
    ~LuaScript();

    lua_State *init();
    bool dofile(const QString &f, QString &output);

    lua_State *L;
    LuaMap mMap;
};

class LuaPerlin
{
public:
    int repeat;
    static const int permutation[];
    int *p;

    LuaPerlin();
    double perlin(double x, double y, double z);
    int inc(int num);
    double grad(int hash, double x, double y, double z);
    double fade(double t);
    double lerp(double a, double b, double x);
};

extern LuaColor Lua_rgb(int r, int g, int b);
extern const char *cstring(const QString &qstring);

} // namespace Lua
} // namespace Tiled

extern "C" {
extern int traceback(lua_State *L);
}

#endif // LUATILED_H
