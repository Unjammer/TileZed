$#include "luatiled.h"
$#include "luatiletool.h"
$#include "tile.h"
$#include "tilelayer.h"
$#include "tileset.h"

$using namespace Tiled;
$using namespace Tiled::Lua;

class QRect @ Rect
{
    QRect(int x, int y, int w, int h);

    int x();
    int y();
    int width();
    int height();

    int left();
    int right();
    int top();
    int bottom();

    void translate(int dx, int dy);
    QRect translated(int dx, int dy);

    bool intersects(QRect& other);
};

class LuaRegion @ Region
{
    LuaRegion();

    QRect boundingRect();

    vector<QRect> rects();

    bool isEmpty();

    int rectCount();

    void unite(int x, int y, int w, int h);
    void unite(QRect& rect);
    void unite(LuaRegion& r);

    void intersect(int x, int y, int w, int h);
    void intersect(QRect& rect);
    void intersect(LuaRegion& r);

    LuaRegion operator+(QRect& rect);
    LuaRegion intersected(QRect& rect);

    LuaRegion operator+(LuaRegion& r);
    LuaRegion operator-(LuaRegion& r);
    LuaRegion intersected(LuaRegion& r);
    LuaRegion intersected(LuaRegion& r);

    LuaRegion translated(int dx, int dy);
};

class Tile
{
    Tileset* tileset();
    int id();
};

class Tileset
{
    QString name();
};

class LuaLayer @ Layer
{
    LuaTileLayer * asTileLayer();
    LuaObjectGroup* asObjectGroup();

    const char* name();
    const char* type();
};

class LuaTileLayer @ TileLayer : public LuaLayer
{
    LuaTileLayer(const char* name, int x, int y, int width, int height);

    int level();

    void setTile(int x, int y, Tile* tile);
    Tile* tileAt(int x, int y);
    void clearTile(int x, int y);

    void erase(int x, int y, int width, int height);
    void erase(QRect& r);
    void erase(LuaRegion& rgn);
    void erase();

    void fill(int x, int y, int width, int height, Tile* tile);
    void fill(QRect& r, Tile* tile);
    void fill(LuaRegion& rgn, Tile* tile);
    void fill(Tile* tile);

    bool replaceTile(Tile* oldTile, Tile* newTile);
};

class LuaMapObject @ MapObject
{
    LuaMapObject(const char* name, const char* type, int x, int y, int width, int height);

    const char* name();
    const char* type();

    QRect bounds();
};

class LuaObjectGroup @ ObjectGroup : public LuaLayer
{
    LuaObjectGroup(const char* name, int x, int y, int width, int height);

    void setColor(LuaColor& color);
    LuaColor color();

    void addObject(LuaMapObject* object);
    list<LuaMapObject*> objects();
};

class LuaColor @ Color
{
    LuaColor();
    LuaColor(int r, int g, int b);
    int r;
    int g;
    int b;
    unsigned int pixel;
};

LuaColor Lua_rgb @ rgb(int r, int g, int b);

class LuaMapBmp& MapBmp
{
    void setPixel(int x, int y, LuaColor & c);
    unsigned int pixel(int x, int y);

    void erase(int x, int y, int width, int height);
    void erase(QRect& r);
    void erase(LuaRegion& rgn);
    void erase();

    void fill(int x, int y, int width, int height, LuaColor& c);
    void fill(QRect& r, LuaColor& c);
    void fill(LuaRegion& rgn, LuaColor& c);
    void fill(LuaColor& c);

    void replace(LuaColor& oldColor, LuaColor& newColor);

    int rand(int x, int y);
};

class LuaBmpAlias @ BmpAlias
{
    list<QString> tiles();
};

class LuaBmpRule @ BmpRule
{
    const char* label();
    int bmpIndex();
    LuaColor color();
    list<QString> tiles();
    const char* layer();
    LuaColor condition();
};

class LuaBmpBlend @ BmpBlend
{
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

    const char* layer();
    const char* mainTile();
    const char* blendTile();
    Direction direction();
    list<QString> exclude();
};

class LuaMapNoBlend @ MapNoBlend
{
public:
    void set(int x, int y, bool noblend);
    void set(LuaRegion& rgn, bool noblend);
    bool get(int x, int y);
};

class LuaMap @ Map
{
    enum Orientation {
    Unknown,
    Orthogonal,
    Isometric,
    LevelIsometric,
    Staggered
    };

    LuaMap(Orientation orient, int width, int height, int tileWidth = 64, int tileHeight = 32);

    Orientation orientation();

    int width();
    int height();

    int maxLevel();

    void addLayer(LuaLayer* layer);
    void insertLayer(int index, LuaLayer* layer);
    void removeLayer(int index);
    int layerCount();
    LuaLayer* layerAt(int index);
    LuaLayer* layer(const char* name);
    LuaTileLayer* tileLayer(const char* name);

    LuaTileLayer* newTileLayer(const char* name);

    void addTileset(Tileset* tileset);
    int tilesetCount();
    Tileset* tileset(const char* name);
    Tileset* tilesetAt(int index);
    Tile* tile(const char* name);
    Tile* tile(const char* tilesetName, int id);
    Tile* noneTile();

    void setTileSelection(LuaRegion& rgn);
    LuaRegion tileSelection();

    void replaceTilesByName(const char* names);

    LuaMapBmp& bmp(int index);

    LuaBmpAlias* alias(const char* name);

    int ruleCount();
    LuaBmpRule* ruleAt(int index);
    list<LuaBmpRule*> rules();
    LuaBmpRule* rule(const char* name);

    list<LuaBmpBlend*> blends();
    bool isBlendTile(Tile* tile);
    list<QString> blendLayers();

    LuaMapNoBlend* noBlend(const char* layerName);

    void reloadRules();
    void reloadBlends();

    bool write(const char* path);

    int cellX();
    int cellY();
};

class LuaTileTool @ TileTool
{
    enum CursorType {
        None,
        CurbTool,
        EdgeTool
    };
    void setCursorType(CursorType type);
    LuaTileLayer* currentLayer() const;
    void applyChanges(const char* undoText);
    int angle(float x1, float y1, float x2, float y2);
    void clearToolTiles();
    void setToolTile(const char* layer, int x, int y, Tile* tile);
    void setToolTile(const char* layer, LuaRegion& rgn, Tile* tile);
    void clearToolNoBlends();
    void setToolNoBlend(const char* layer, LuaRegion& rgn, bool noBlend);
    void clearDistanceIndicators();
    void indicateDistance(int x1, int y1, int x2, int y2);
    bool dragged();
};

class LuaPerlin @ Perlin
{
    LuaPerlin();
    double perlin(double x, double y, double z);
};
