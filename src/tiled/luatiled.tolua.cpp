/*
** Lua binding: tiled
*/

#include "tolua.h"

#ifndef __cplusplus
#include <stdlib.h>
#endif
#ifdef __cplusplus
 extern "C" int tolua_bnd_takeownership (lua_State* L); // from tolua_map.c
#else
 int tolua_bnd_takeownership (lua_State* L); /* from tolua_map.c */
#endif
#include <string.h>

/* Exported function */
TOLUA_API int  tolua_tiled_open (lua_State* tolua_S);
LUALIB_API int  luaopen_tiled (lua_State* tolua_S);

#include "luatiled.h"
#include "luatiletool.h"
#include "tile.h"
#include "tilelayer.h"
#include "tileset.h"
using namespace Tiled;
using namespace Tiled::Lua;

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_LuaColor (lua_State* tolua_S)
{
 LuaColor* self = (LuaColor*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
	delete self;
	return 0;
}

static int tolua_collect_LuaRegion (lua_State* tolua_S)
{
 LuaRegion* self = (LuaRegion*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
	delete self;
	return 0;
}

static int tolua_collect_QString (lua_State* tolua_S)
{
 QString* self = (QString*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
	delete self;
	return 0;
}

static int tolua_collect_QRect (lua_State* tolua_S)
{
 QRect* self = (QRect*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
	delete self;
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"QString");
 tolua_usertype(tolua_S,"LuaObjectGroup");
 tolua_usertype(tolua_S,"LuaPerlin");
 tolua_usertype(tolua_S,"LuaMapNoBlend");
 tolua_usertype(tolua_S,"LuaBmpBlend");
 tolua_usertype(tolua_S,"Tileset");
 tolua_usertype(tolua_S,"LuaTileLayer");
 tolua_usertype(tolua_S,"LuaLayer");
 tolua_usertype(tolua_S,"LuaRegion");
 tolua_usertype(tolua_S,"LuaMapBmp");
 tolua_usertype(tolua_S,"LuaMapObject");
 tolua_usertype(tolua_S,"LuaTileTool");
 tolua_usertype(tolua_S,"LuaMap");
 tolua_usertype(tolua_S,"MapBmp");
 tolua_usertype(tolua_S,"LuaColor");
 tolua_usertype(tolua_S,"LuaBmpRule");
 tolua_usertype(tolua_S,"Tile");
 tolua_usertype(tolua_S,"QRect");
 tolua_usertype(tolua_S,"LuaBmpAlias");
}

/* method: new of class  QRect */
static int tolua_tiled_Rect_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"QRect",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,5,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,6,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  int w = ((int)  tolua_tonumber(tolua_S,4,0));
  int h = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   QRect* tolua_ret = (QRect*)  new QRect(x,y,w,h);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"QRect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: x of class  QRect */
static int tolua_tiled_Rect_x00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QRect",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  QRect* self = (QRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'x'",NULL);
#endif
  {
   int tolua_ret = (int)  self->x();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'x'.",&tolua_err);
 return 0;
#endif
}

/* method: y of class  QRect */
static int tolua_tiled_Rect_y00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QRect",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  QRect* self = (QRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'y'",NULL);
#endif
  {
   int tolua_ret = (int)  self->y();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'y'.",&tolua_err);
 return 0;
#endif
}

/* method: width of class  QRect */
static int tolua_tiled_Rect_width00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QRect",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  QRect* self = (QRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'width'",NULL);
#endif
  {
   int tolua_ret = (int)  self->width();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'width'.",&tolua_err);
 return 0;
#endif
}

/* method: height of class  QRect */
static int tolua_tiled_Rect_height00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QRect",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  QRect* self = (QRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'height'",NULL);
#endif
  {
   int tolua_ret = (int)  self->height();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'height'.",&tolua_err);
 return 0;
#endif
}

/* method: left of class  QRect */
static int tolua_tiled_Rect_left00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QRect",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  QRect* self = (QRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'left'",NULL);
#endif
  {
   int tolua_ret = (int)  self->left();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'left'.",&tolua_err);
 return 0;
#endif
}

/* method: right of class  QRect */
static int tolua_tiled_Rect_right00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QRect",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  QRect* self = (QRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'right'",NULL);
#endif
  {
   int tolua_ret = (int)  self->right();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'right'.",&tolua_err);
 return 0;
#endif
}

/* method: top of class  QRect */
static int tolua_tiled_Rect_top00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QRect",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  QRect* self = (QRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'top'",NULL);
#endif
  {
   int tolua_ret = (int)  self->top();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'top'.",&tolua_err);
 return 0;
#endif
}

/* method: bottom of class  QRect */
static int tolua_tiled_Rect_bottom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QRect",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  QRect* self = (QRect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'bottom'",NULL);
#endif
  {
   int tolua_ret = (int)  self->bottom();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'bottom'.",&tolua_err);
 return 0;
#endif
}

/* method: translate of class  QRect */
static int tolua_tiled_Rect_translate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QRect",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,4,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  QRect* self = (QRect*)  tolua_tousertype(tolua_S,1,0);
  int dx = ((int)  tolua_tonumber(tolua_S,2,0));
  int dy = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'translate'",NULL);
#endif
  {
   self->translate(dx,dy);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'translate'.",&tolua_err);
 return 0;
#endif
}

/* method: translated of class  QRect */
static int tolua_tiled_Rect_translated00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QRect",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,4,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  QRect* self = (QRect*)  tolua_tousertype(tolua_S,1,0);
  int dx = ((int)  tolua_tonumber(tolua_S,2,0));
  int dy = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'translated'",NULL);
#endif
  {
   QRect tolua_ret =  self->translated(dx,dy);
   {
#ifdef __cplusplus
    void* tolua_obj = new QRect(tolua_ret);
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_QRect),"QRect");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(QRect));
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"QRect");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'translated'.",&tolua_err);
 return 0;
#endif
}

/* method: intersects of class  QRect */
static int tolua_tiled_Rect_intersects00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"QRect",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"QRect",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  QRect* self = (QRect*)  tolua_tousertype(tolua_S,1,0);
  QRect* other = ((QRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'intersects'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->intersects(*other);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'intersects'.",&tolua_err);
 return 0;
#endif
}

/* method: new of class  LuaRegion */
static int tolua_tiled_Region_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaRegion",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  {
   LuaRegion* tolua_ret = (LuaRegion*)  new LuaRegion();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaRegion");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: boundingRect of class  LuaRegion */
static int tolua_tiled_Region_boundingRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaRegion",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaRegion* self = (LuaRegion*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'boundingRect'",NULL);
#endif
  {
   QRect tolua_ret =  self->boundingRect();
   {
#ifdef __cplusplus
    void* tolua_obj = new QRect(tolua_ret);
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_QRect),"QRect");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(QRect));
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"QRect");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'boundingRect'.",&tolua_err);
 return 0;
#endif
}

/* method: rects of class  LuaRegion */
static int tolua_tiled_Region_rects00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaRegion",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaRegion* self = (LuaRegion*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rects'",NULL);
#endif
  {
   QVector<QRect> tolua_ret = (QVector<QRect>)  self->rects();
   lua_newtable(tolua_S);
   for (int i = 0; i < tolua_ret.size(); i++) {
    void* tolua_obj = new QRect(tolua_ret[i]);
    void* v = tolua_clone(tolua_S,tolua_obj,tolua_collect_QRect);
    tolua_pushfieldusertype(tolua_S,2,i+1,v,"QRect");
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rects'.",&tolua_err);
 return 0;
#endif
}

/* method: isEmpty of class  LuaRegion */
static int tolua_tiled_Region_isEmpty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaRegion",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaRegion* self = (LuaRegion*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isEmpty'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isEmpty();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isEmpty'.",&tolua_err);
 return 0;
#endif
}

/* method: rectCount of class  LuaRegion */
static int tolua_tiled_Region_rectCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaRegion",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaRegion* self = (LuaRegion*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rectCount'",NULL);
#endif
  {
   int tolua_ret = (int)  self->rectCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rectCount'.",&tolua_err);
 return 0;
#endif
}

/* method: unite of class  LuaRegion */
static int tolua_tiled_Region_unite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaRegion",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,5,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,6,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaRegion* self = (LuaRegion*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  int w = ((int)  tolua_tonumber(tolua_S,4,0));
  int h = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unite'",NULL);
#endif
  {
   self->unite(x,y,w,h);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unite'.",&tolua_err);
 return 0;
#endif
}

/* method: unite of class  LuaRegion */
static int tolua_tiled_Region_unite01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaRegion",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"QRect",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaRegion* self = (LuaRegion*)  tolua_tousertype(tolua_S,1,0);
  QRect* rect = ((QRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unite'",NULL);
#endif
  {
   self->unite(*rect);
  }
 }
 return 0;
tolua_lerror:
 return tolua_tiled_Region_unite00(tolua_S);
}

/* method: unite of class  LuaRegion */
static int tolua_tiled_Region_unite02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaRegion",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"LuaRegion",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaRegion* self = (LuaRegion*)  tolua_tousertype(tolua_S,1,0);
  LuaRegion* r = ((LuaRegion*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unite'",NULL);
#endif
  {
   self->unite(*r);
  }
 }
 return 0;
tolua_lerror:
 return tolua_tiled_Region_unite01(tolua_S);
}

/* method: intersect of class  LuaRegion */
static int tolua_tiled_Region_intersect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaRegion",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,5,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,6,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaRegion* self = (LuaRegion*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  int w = ((int)  tolua_tonumber(tolua_S,4,0));
  int h = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'intersect'",NULL);
#endif
  {
   self->intersect(x,y,w,h);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'intersect'.",&tolua_err);
 return 0;
#endif
}

/* method: intersect of class  LuaRegion */
static int tolua_tiled_Region_intersect01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaRegion",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"QRect",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaRegion* self = (LuaRegion*)  tolua_tousertype(tolua_S,1,0);
  QRect* rect = ((QRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'intersect'",NULL);
#endif
  {
   self->intersect(*rect);
  }
 }
 return 0;
tolua_lerror:
 return tolua_tiled_Region_intersect00(tolua_S);
}

/* method: intersect of class  LuaRegion */
static int tolua_tiled_Region_intersect02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaRegion",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"LuaRegion",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaRegion* self = (LuaRegion*)  tolua_tousertype(tolua_S,1,0);
  LuaRegion* r = ((LuaRegion*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'intersect'",NULL);
#endif
  {
   self->intersect(*r);
  }
 }
 return 0;
tolua_lerror:
 return tolua_tiled_Region_intersect01(tolua_S);
}

/* method: operator+ of class  LuaRegion */
static int tolua_tiled_Region_operator_add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaRegion",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"QRect",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaRegion* self = (LuaRegion*)  tolua_tousertype(tolua_S,1,0);
  QRect* rect = ((QRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'",NULL);
#endif
  {
   LuaRegion tolua_ret =  self->operator+(*rect);
   {
#ifdef __cplusplus
    void* tolua_obj = new LuaRegion(tolua_ret);
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_LuaRegion),"LuaRegion");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaRegion));
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"LuaRegion");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}

/* method: intersected of class  LuaRegion */
static int tolua_tiled_Region_intersected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaRegion",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"QRect",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaRegion* self = (LuaRegion*)  tolua_tousertype(tolua_S,1,0);
  QRect* rect = ((QRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'intersected'",NULL);
#endif
  {
   LuaRegion tolua_ret =  self->intersected(*rect);
   {
#ifdef __cplusplus
    void* tolua_obj = new LuaRegion(tolua_ret);
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_LuaRegion),"LuaRegion");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaRegion));
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"LuaRegion");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'intersected'.",&tolua_err);
 return 0;
#endif
}

/* method: operator+ of class  LuaRegion */
static int tolua_tiled_Region_operator_add01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaRegion",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"LuaRegion",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaRegion* self = (LuaRegion*)  tolua_tousertype(tolua_S,1,0);
  LuaRegion* r = ((LuaRegion*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'",NULL);
#endif
  {
   LuaRegion tolua_ret =  self->operator+(*r);
   {
#ifdef __cplusplus
    void* tolua_obj = new LuaRegion(tolua_ret);
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_LuaRegion),"LuaRegion");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaRegion));
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"LuaRegion");
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_tiled_Region_operator_add00(tolua_S);
}

/* method: operator- of class  LuaRegion */
static int tolua_tiled_Region_operator_sub00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaRegion",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"LuaRegion",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaRegion* self = (LuaRegion*)  tolua_tousertype(tolua_S,1,0);
  LuaRegion* r = ((LuaRegion*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator-'",NULL);
#endif
  {
   LuaRegion tolua_ret =  self->operator-(*r);
   {
#ifdef __cplusplus
    void* tolua_obj = new LuaRegion(tolua_ret);
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_LuaRegion),"LuaRegion");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaRegion));
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"LuaRegion");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.sub'.",&tolua_err);
 return 0;
#endif
}

/* method: intersected of class  LuaRegion */
static int tolua_tiled_Region_intersected01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaRegion",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"LuaRegion",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaRegion* self = (LuaRegion*)  tolua_tousertype(tolua_S,1,0);
  LuaRegion* r = ((LuaRegion*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'intersected'",NULL);
#endif
  {
   LuaRegion tolua_ret =  self->intersected(*r);
   {
#ifdef __cplusplus
    void* tolua_obj = new LuaRegion(tolua_ret);
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_LuaRegion),"LuaRegion");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaRegion));
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"LuaRegion");
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_tiled_Region_intersected00(tolua_S);
}

/* method: intersected of class  LuaRegion */
static int tolua_tiled_Region_intersected02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaRegion",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"LuaRegion",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaRegion* self = (LuaRegion*)  tolua_tousertype(tolua_S,1,0);
  LuaRegion* r = ((LuaRegion*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'intersected'",NULL);
#endif
  {
   LuaRegion tolua_ret =  self->intersected(*r);
   {
#ifdef __cplusplus
    void* tolua_obj = new LuaRegion(tolua_ret);
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_LuaRegion),"LuaRegion");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaRegion));
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"LuaRegion");
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_tiled_Region_intersected01(tolua_S);
}

/* method: translated of class  LuaRegion */
static int tolua_tiled_Region_translated00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaRegion",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,4,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaRegion* self = (LuaRegion*)  tolua_tousertype(tolua_S,1,0);
  int dx = ((int)  tolua_tonumber(tolua_S,2,0));
  int dy = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'translated'",NULL);
#endif
  {
   LuaRegion tolua_ret =  self->translated(dx,dy);
   {
#ifdef __cplusplus
    void* tolua_obj = new LuaRegion(tolua_ret);
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_LuaRegion),"LuaRegion");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaRegion));
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"LuaRegion");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'translated'.",&tolua_err);
 return 0;
#endif
}

/* method: tileset of class  Tile */
static int tolua_tiled_Tile_tileset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Tile",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  Tile* self = (Tile*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tileset'",NULL);
#endif
  {
   Tileset* tolua_ret = (Tileset*)  self->tileset();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tileset");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tileset'.",&tolua_err);
 return 0;
#endif
}

/* method: id of class  Tile */
static int tolua_tiled_Tile_id00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Tile",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  Tile* self = (Tile*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'id'",NULL);
#endif
  {
   int tolua_ret = (int)  self->id();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'id'.",&tolua_err);
 return 0;
#endif
}

/* method: name of class  Tileset */
static int tolua_tiled_Tileset_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Tileset",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  Tileset* self = (Tileset*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'name'",NULL);
#endif
  {
   QString tolua_ret =  self->name();
   lua_pushstring(tolua_S, Lua::cstring(tolua_ret));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'name'.",&tolua_err);
 return 0;
#endif
}

/* method: asTileLayer of class  LuaLayer */
static int tolua_tiled_Layer_asTileLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaLayer",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaLayer* self = (LuaLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'asTileLayer'",NULL);
#endif
  {
   LuaTileLayer* tolua_ret = (LuaTileLayer*)  self->asTileLayer();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaTileLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'asTileLayer'.",&tolua_err);
 return 0;
#endif
}

/* method: asObjectGroup of class  LuaLayer */
static int tolua_tiled_Layer_asObjectGroup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaLayer",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaLayer* self = (LuaLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'asObjectGroup'",NULL);
#endif
  {
   LuaObjectGroup* tolua_ret = (LuaObjectGroup*)  self->asObjectGroup();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaObjectGroup");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'asObjectGroup'.",&tolua_err);
 return 0;
#endif
}

/* method: name of class  LuaLayer */
static int tolua_tiled_Layer_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaLayer",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaLayer* self = (LuaLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'name'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->name();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'name'.",&tolua_err);
 return 0;
#endif
}

/* method: type of class  LuaLayer */
static int tolua_tiled_Layer_type00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaLayer",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaLayer* self = (LuaLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'type'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->type();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'type'.",&tolua_err);
 return 0;
#endif
}

/* method: new of class  LuaTileLayer */
static int tolua_tiled_TileLayer_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaTileLayer",0,&tolua_err) || 
     !tolua_isstring(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,5,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,6,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,7,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  int x = ((int)  tolua_tonumber(tolua_S,3,0));
  int y = ((int)  tolua_tonumber(tolua_S,4,0));
  int width = ((int)  tolua_tonumber(tolua_S,5,0));
  int height = ((int)  tolua_tonumber(tolua_S,6,0));
  {
   LuaTileLayer* tolua_ret = (LuaTileLayer*)  new LuaTileLayer(name,x,y,width,height);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaTileLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: level of class  LuaTileLayer */
static int tolua_tiled_TileLayer_level00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileLayer",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaTileLayer* self = (LuaTileLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'level'",NULL);
#endif
  {
   int tolua_ret = (int)  self->level();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'level'.",&tolua_err);
 return 0;
#endif
}

/* method: setTile of class  LuaTileLayer */
static int tolua_tiled_TileLayer_setTile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileLayer",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isusertype(tolua_S,4,"Tile",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,5,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaTileLayer* self = (LuaTileLayer*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  Tile* tile = ((Tile*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTile'",NULL);
#endif
  {
   self->setTile(x,y,tile);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTile'.",&tolua_err);
 return 0;
#endif
}

/* method: tileAt of class  LuaTileLayer */
static int tolua_tiled_TileLayer_tileAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileLayer",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,4,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaTileLayer* self = (LuaTileLayer*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tileAt'",NULL);
#endif
  {
   Tile* tolua_ret = (Tile*)  self->tileAt(x,y);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tile");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tileAt'.",&tolua_err);
 return 0;
#endif
}

/* method: clearTile of class  LuaTileLayer */
static int tolua_tiled_TileLayer_clearTile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileLayer",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,4,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaTileLayer* self = (LuaTileLayer*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearTile'",NULL);
#endif
  {
   self->clearTile(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearTile'.",&tolua_err);
 return 0;
#endif
}

/* method: erase of class  LuaTileLayer */
static int tolua_tiled_TileLayer_erase00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileLayer",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,5,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,6,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaTileLayer* self = (LuaTileLayer*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  int width = ((int)  tolua_tonumber(tolua_S,4,0));
  int height = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'erase'",NULL);
#endif
  {
   self->erase(x,y,width,height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'erase'.",&tolua_err);
 return 0;
#endif
}

/* method: erase of class  LuaTileLayer */
static int tolua_tiled_TileLayer_erase01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileLayer",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"QRect",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaTileLayer* self = (LuaTileLayer*)  tolua_tousertype(tolua_S,1,0);
  QRect* r = ((QRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'erase'",NULL);
#endif
  {
   self->erase(*r);
  }
 }
 return 0;
tolua_lerror:
 return tolua_tiled_TileLayer_erase00(tolua_S);
}

/* method: erase of class  LuaTileLayer */
static int tolua_tiled_TileLayer_erase02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileLayer",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"LuaRegion",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaTileLayer* self = (LuaTileLayer*)  tolua_tousertype(tolua_S,1,0);
  LuaRegion* rgn = ((LuaRegion*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'erase'",NULL);
#endif
  {
   self->erase(*rgn);
  }
 }
 return 0;
tolua_lerror:
 return tolua_tiled_TileLayer_erase01(tolua_S);
}

/* method: erase of class  LuaTileLayer */
static int tolua_tiled_TileLayer_erase03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileLayer",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaTileLayer* self = (LuaTileLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'erase'",NULL);
#endif
  {
   self->erase();
  }
 }
 return 0;
tolua_lerror:
 return tolua_tiled_TileLayer_erase02(tolua_S);
}

/* method: fill of class  LuaTileLayer */
static int tolua_tiled_TileLayer_fill00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileLayer",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,5,0,&tolua_err) || 
     !tolua_isusertype(tolua_S,6,"Tile",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,7,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaTileLayer* self = (LuaTileLayer*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  int width = ((int)  tolua_tonumber(tolua_S,4,0));
  int height = ((int)  tolua_tonumber(tolua_S,5,0));
  Tile* tile = ((Tile*)  tolua_tousertype(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fill'",NULL);
#endif
  {
   self->fill(x,y,width,height,tile);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'fill'.",&tolua_err);
 return 0;
#endif
}

/* method: fill of class  LuaTileLayer */
static int tolua_tiled_TileLayer_fill01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileLayer",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"QRect",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,3,"Tile",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,4,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaTileLayer* self = (LuaTileLayer*)  tolua_tousertype(tolua_S,1,0);
  QRect* r = ((QRect*)  tolua_tousertype(tolua_S,2,0));
  Tile* tile = ((Tile*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fill'",NULL);
#endif
  {
   self->fill(*r,tile);
  }
 }
 return 0;
tolua_lerror:
 return tolua_tiled_TileLayer_fill00(tolua_S);
}

/* method: fill of class  LuaTileLayer */
static int tolua_tiled_TileLayer_fill02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileLayer",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"LuaRegion",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,3,"Tile",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,4,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaTileLayer* self = (LuaTileLayer*)  tolua_tousertype(tolua_S,1,0);
  LuaRegion* rgn = ((LuaRegion*)  tolua_tousertype(tolua_S,2,0));
  Tile* tile = ((Tile*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fill'",NULL);
#endif
  {
   self->fill(*rgn,tile);
  }
 }
 return 0;
tolua_lerror:
 return tolua_tiled_TileLayer_fill01(tolua_S);
}

/* method: fill of class  LuaTileLayer */
static int tolua_tiled_TileLayer_fill03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileLayer",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"Tile",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaTileLayer* self = (LuaTileLayer*)  tolua_tousertype(tolua_S,1,0);
  Tile* tile = ((Tile*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fill'",NULL);
#endif
  {
   self->fill(tile);
  }
 }
 return 0;
tolua_lerror:
 return tolua_tiled_TileLayer_fill02(tolua_S);
}

/* method: replaceTile of class  LuaTileLayer */
static int tolua_tiled_TileLayer_replaceTile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileLayer",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"Tile",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,3,"Tile",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,4,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaTileLayer* self = (LuaTileLayer*)  tolua_tousertype(tolua_S,1,0);
  Tile* oldTile = ((Tile*)  tolua_tousertype(tolua_S,2,0));
  Tile* newTile = ((Tile*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'replaceTile'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->replaceTile(oldTile,newTile);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'replaceTile'.",&tolua_err);
 return 0;
#endif
}

/* method: new of class  LuaMapObject */
static int tolua_tiled_MapObject_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaMapObject",0,&tolua_err) || 
     !tolua_isstring(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,5,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,6,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,7,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  int x = ((int)  tolua_tonumber(tolua_S,3,0));
  int y = ((int)  tolua_tonumber(tolua_S,4,0));
  int width = ((int)  tolua_tonumber(tolua_S,5,0));
  int height = ((int)  tolua_tonumber(tolua_S,6,0));
  {
   LuaMapObject* tolua_ret = (LuaMapObject*)  new LuaMapObject(name,x,y,width,height);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaMapObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: name of class  LuaMapObject */
static int tolua_tiled_MapObject_name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMapObject",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMapObject* self = (LuaMapObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'name'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->name();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'name'.",&tolua_err);
 return 0;
#endif
}

/* method: type of class  LuaMapObject */
static int tolua_tiled_MapObject_type00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMapObject",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMapObject* self = (LuaMapObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'type'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->type();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'type'.",&tolua_err);
 return 0;
#endif
}

/* method: bounds of class  LuaMapObject */
static int tolua_tiled_MapObject_bounds00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMapObject",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMapObject* self = (LuaMapObject*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'bounds'",NULL);
#endif
  {
   QRect tolua_ret =  self->bounds();
   {
#ifdef __cplusplus
    void* tolua_obj = new QRect(tolua_ret);
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_QRect),"QRect");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(QRect));
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"QRect");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'bounds'.",&tolua_err);
 return 0;
#endif
}

/* method: new of class  LuaObjectGroup */
static int tolua_tiled_ObjectGroup_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaObjectGroup",0,&tolua_err) || 
     !tolua_isstring(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,5,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,6,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,7,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  int x = ((int)  tolua_tonumber(tolua_S,3,0));
  int y = ((int)  tolua_tonumber(tolua_S,4,0));
  int width = ((int)  tolua_tonumber(tolua_S,5,0));
  int height = ((int)  tolua_tonumber(tolua_S,6,0));
  {
   LuaObjectGroup* tolua_ret = (LuaObjectGroup*)  new LuaObjectGroup(name,x,y,width,height);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaObjectGroup");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: setColor of class  LuaObjectGroup */
static int tolua_tiled_ObjectGroup_setColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaObjectGroup",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"LuaColor",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaObjectGroup* self = (LuaObjectGroup*)  tolua_tousertype(tolua_S,1,0);
  LuaColor* color = ((LuaColor*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setColor'",NULL);
#endif
  {
   self->setColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setColor'.",&tolua_err);
 return 0;
#endif
}

/* method: color of class  LuaObjectGroup */
static int tolua_tiled_ObjectGroup_color00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaObjectGroup",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaObjectGroup* self = (LuaObjectGroup*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'color'",NULL);
#endif
  {
   LuaColor tolua_ret =  self->color();
   {
#ifdef __cplusplus
    void* tolua_obj = new LuaColor(tolua_ret);
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_LuaColor),"LuaColor");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaColor));
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"LuaColor");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'color'.",&tolua_err);
 return 0;
#endif
}

/* method: addObject of class  LuaObjectGroup */
static int tolua_tiled_ObjectGroup_addObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaObjectGroup",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"LuaMapObject",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaObjectGroup* self = (LuaObjectGroup*)  tolua_tousertype(tolua_S,1,0);
  LuaMapObject* object = ((LuaMapObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addObject'",NULL);
#endif
  {
   self->addObject(object);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addObject'.",&tolua_err);
 return 0;
#endif
}

/* method: objects of class  LuaObjectGroup */
static int tolua_tiled_ObjectGroup_objects00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaObjectGroup",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaObjectGroup* self = (LuaObjectGroup*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'objects'",NULL);
#endif
  {
   QList<LuaMapObject*> tolua_ret = (QList<LuaMapObject*>)  self->objects();
   lua_newtable(tolua_S);
   for (int i = 0; i < tolua_ret.size(); i++) {
    tolua_pushfieldusertype(tolua_S,2,i+1,tolua_ret[i],"LuaMapObject");
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'objects'.",&tolua_err);
 return 0;
#endif
}

/* method: new of class  LuaColor */
static int tolua_tiled_Color_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaColor",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  {
   LuaColor* tolua_ret = (LuaColor*)  new LuaColor();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaColor");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: new of class  LuaColor */
static int tolua_tiled_Color_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaColor",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,5,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  int r = ((int)  tolua_tonumber(tolua_S,2,0));
  int g = ((int)  tolua_tonumber(tolua_S,3,0));
  int b = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   LuaColor* tolua_ret = (LuaColor*)  new LuaColor(r,g,b);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaColor");
  }
 }
 return 1;
tolua_lerror:
 return tolua_tiled_Color_new00(tolua_S);
}

/* get function: r of class  LuaColor */
static int tolua_get_LuaColor_LuaColor_r(lua_State* tolua_S)
{
  LuaColor* self = (LuaColor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'r'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->r);
 return 1;
}

/* set function: r of class  LuaColor */
static int tolua_set_LuaColor_LuaColor_r(lua_State* tolua_S)
{
  LuaColor* self = (LuaColor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'r'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->r = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: g of class  LuaColor */
static int tolua_get_LuaColor_LuaColor_g(lua_State* tolua_S)
{
  LuaColor* self = (LuaColor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'g'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->g);
 return 1;
}

/* set function: g of class  LuaColor */
static int tolua_set_LuaColor_LuaColor_g(lua_State* tolua_S)
{
  LuaColor* self = (LuaColor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'g'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->g = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: b of class  LuaColor */
static int tolua_get_LuaColor_LuaColor_b(lua_State* tolua_S)
{
  LuaColor* self = (LuaColor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'b'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->b);
 return 1;
}

/* set function: b of class  LuaColor */
static int tolua_set_LuaColor_LuaColor_b(lua_State* tolua_S)
{
  LuaColor* self = (LuaColor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'b'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->b = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: pixel of class  LuaColor */
static int tolua_get_LuaColor_LuaColor_unsigned_pixel(lua_State* tolua_S)
{
  LuaColor* self = (LuaColor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pixel'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->pixel);
 return 1;
}

/* set function: pixel of class  LuaColor */
static int tolua_set_LuaColor_LuaColor_unsigned_pixel(lua_State* tolua_S)
{
  LuaColor* self = (LuaColor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pixel'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pixel = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* function: Lua_rgb */
static int tolua_tiled_rgb00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,4,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  int r = ((int)  tolua_tonumber(tolua_S,1,0));
  int g = ((int)  tolua_tonumber(tolua_S,2,0));
  int b = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   LuaColor tolua_ret =  Lua_rgb(r,g,b);
   {
#ifdef __cplusplus
    void* tolua_obj = new LuaColor(tolua_ret);
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_LuaColor),"LuaColor");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaColor));
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"LuaColor");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rgb'.",&tolua_err);
 return 0;
#endif
}

/* method: setPixel of class  LuaMapBmp */
static int tolua_tiled_LuaMapBmp_setPixel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMapBmp",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isusertype(tolua_S,4,"LuaColor",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,5,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMapBmp* self = (LuaMapBmp*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  LuaColor* c = ((LuaColor*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPixel'",NULL);
#endif
  {
   self->setPixel(x,y,*c);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPixel'.",&tolua_err);
 return 0;
#endif
}

/* method: pixel of class  LuaMapBmp */
static int tolua_tiled_LuaMapBmp_pixel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMapBmp",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,4,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMapBmp* self = (LuaMapBmp*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pixel'",NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->pixel(x,y);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pixel'.",&tolua_err);
 return 0;
#endif
}

/* method: erase of class  LuaMapBmp */
static int tolua_tiled_LuaMapBmp_erase00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMapBmp",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,5,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,6,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMapBmp* self = (LuaMapBmp*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  int width = ((int)  tolua_tonumber(tolua_S,4,0));
  int height = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'erase'",NULL);
#endif
  {
   self->erase(x,y,width,height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'erase'.",&tolua_err);
 return 0;
#endif
}

/* method: erase of class  LuaMapBmp */
static int tolua_tiled_LuaMapBmp_erase01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMapBmp",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"QRect",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaMapBmp* self = (LuaMapBmp*)  tolua_tousertype(tolua_S,1,0);
  QRect* r = ((QRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'erase'",NULL);
#endif
  {
   self->erase(*r);
  }
 }
 return 0;
tolua_lerror:
 return tolua_tiled_LuaMapBmp_erase00(tolua_S);
}

/* method: erase of class  LuaMapBmp */
static int tolua_tiled_LuaMapBmp_erase02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMapBmp",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"LuaRegion",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaMapBmp* self = (LuaMapBmp*)  tolua_tousertype(tolua_S,1,0);
  LuaRegion* rgn = ((LuaRegion*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'erase'",NULL);
#endif
  {
   self->erase(*rgn);
  }
 }
 return 0;
tolua_lerror:
 return tolua_tiled_LuaMapBmp_erase01(tolua_S);
}

/* method: erase of class  LuaMapBmp */
static int tolua_tiled_LuaMapBmp_erase03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMapBmp",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaMapBmp* self = (LuaMapBmp*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'erase'",NULL);
#endif
  {
   self->erase();
  }
 }
 return 0;
tolua_lerror:
 return tolua_tiled_LuaMapBmp_erase02(tolua_S);
}

/* method: fill of class  LuaMapBmp */
static int tolua_tiled_LuaMapBmp_fill00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMapBmp",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,5,0,&tolua_err) || 
     !tolua_isusertype(tolua_S,6,"LuaColor",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,7,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMapBmp* self = (LuaMapBmp*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  int width = ((int)  tolua_tonumber(tolua_S,4,0));
  int height = ((int)  tolua_tonumber(tolua_S,5,0));
  LuaColor* c = ((LuaColor*)  tolua_tousertype(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fill'",NULL);
#endif
  {
   self->fill(x,y,width,height,*c);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'fill'.",&tolua_err);
 return 0;
#endif
}

/* method: fill of class  LuaMapBmp */
static int tolua_tiled_LuaMapBmp_fill01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMapBmp",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"QRect",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,3,"LuaColor",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,4,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaMapBmp* self = (LuaMapBmp*)  tolua_tousertype(tolua_S,1,0);
  QRect* r = ((QRect*)  tolua_tousertype(tolua_S,2,0));
  LuaColor* c = ((LuaColor*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fill'",NULL);
#endif
  {
   self->fill(*r,*c);
  }
 }
 return 0;
tolua_lerror:
 return tolua_tiled_LuaMapBmp_fill00(tolua_S);
}

/* method: fill of class  LuaMapBmp */
static int tolua_tiled_LuaMapBmp_fill02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMapBmp",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"LuaRegion",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,3,"LuaColor",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,4,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaMapBmp* self = (LuaMapBmp*)  tolua_tousertype(tolua_S,1,0);
  LuaRegion* rgn = ((LuaRegion*)  tolua_tousertype(tolua_S,2,0));
  LuaColor* c = ((LuaColor*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fill'",NULL);
#endif
  {
   self->fill(*rgn,*c);
  }
 }
 return 0;
tolua_lerror:
 return tolua_tiled_LuaMapBmp_fill01(tolua_S);
}

/* method: fill of class  LuaMapBmp */
static int tolua_tiled_LuaMapBmp_fill03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMapBmp",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"LuaColor",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaMapBmp* self = (LuaMapBmp*)  tolua_tousertype(tolua_S,1,0);
  LuaColor* c = ((LuaColor*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'fill'",NULL);
#endif
  {
   self->fill(*c);
  }
 }
 return 0;
tolua_lerror:
 return tolua_tiled_LuaMapBmp_fill02(tolua_S);
}

/* method: replace of class  LuaMapBmp */
static int tolua_tiled_LuaMapBmp_replace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMapBmp",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"LuaColor",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,3,"LuaColor",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,4,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMapBmp* self = (LuaMapBmp*)  tolua_tousertype(tolua_S,1,0);
  LuaColor* oldColor = ((LuaColor*)  tolua_tousertype(tolua_S,2,0));
  LuaColor* newColor = ((LuaColor*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'replace'",NULL);
#endif
  {
   self->replace(*oldColor,*newColor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'replace'.",&tolua_err);
 return 0;
#endif
}

/* method: rand of class  LuaMapBmp */
static int tolua_tiled_LuaMapBmp_rand00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMapBmp",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,4,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMapBmp* self = (LuaMapBmp*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rand'",NULL);
#endif
  {
   int tolua_ret = (int)  self->rand(x,y);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rand'.",&tolua_err);
 return 0;
#endif
}

/* method: tiles of class  LuaBmpAlias */
static int tolua_tiled_BmpAlias_tiles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaBmpAlias",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaBmpAlias* self = (LuaBmpAlias*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tiles'",NULL);
#endif
  {
   QList<QString> tolua_ret = (QList<QString>)  self->tiles();
   lua_newtable(tolua_S);
   for (int i = 0; i < tolua_ret.size(); i++) {
    const char *v = cstring(tolua_ret[i]);
    tolua_pushfieldstring(tolua_S,2,i+1,v);
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tiles'.",&tolua_err);
 return 0;
#endif
}

/* method: label of class  LuaBmpRule */
static int tolua_tiled_BmpRule_label00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaBmpRule",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaBmpRule* self = (LuaBmpRule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'label'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->label();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'label'.",&tolua_err);
 return 0;
#endif
}

/* method: bmpIndex of class  LuaBmpRule */
static int tolua_tiled_BmpRule_bmpIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaBmpRule",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaBmpRule* self = (LuaBmpRule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'bmpIndex'",NULL);
#endif
  {
   int tolua_ret = (int)  self->bmpIndex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'bmpIndex'.",&tolua_err);
 return 0;
#endif
}

/* method: color of class  LuaBmpRule */
static int tolua_tiled_BmpRule_color00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaBmpRule",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaBmpRule* self = (LuaBmpRule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'color'",NULL);
#endif
  {
   LuaColor tolua_ret =  self->color();
   {
#ifdef __cplusplus
    void* tolua_obj = new LuaColor(tolua_ret);
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_LuaColor),"LuaColor");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaColor));
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"LuaColor");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'color'.",&tolua_err);
 return 0;
#endif
}

/* method: tiles of class  LuaBmpRule */
static int tolua_tiled_BmpRule_tiles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaBmpRule",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaBmpRule* self = (LuaBmpRule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tiles'",NULL);
#endif
  {
   QList<QString> tolua_ret = (QList<QString>)  self->tiles();
   lua_newtable(tolua_S);
   for (int i = 0; i < tolua_ret.size(); i++) {
    const char *v = cstring(tolua_ret[i]);
    tolua_pushfieldstring(tolua_S,2,i+1,v);
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tiles'.",&tolua_err);
 return 0;
#endif
}

/* method: layer of class  LuaBmpRule */
static int tolua_tiled_BmpRule_layer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaBmpRule",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaBmpRule* self = (LuaBmpRule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'layer'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->layer();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'layer'.",&tolua_err);
 return 0;
#endif
}

/* method: condition of class  LuaBmpRule */
static int tolua_tiled_BmpRule_condition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaBmpRule",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaBmpRule* self = (LuaBmpRule*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'condition'",NULL);
#endif
  {
   LuaColor tolua_ret =  self->condition();
   {
#ifdef __cplusplus
    void* tolua_obj = new LuaColor(tolua_ret);
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_LuaColor),"LuaColor");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaColor));
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"LuaColor");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'condition'.",&tolua_err);
 return 0;
#endif
}

/* method: layer of class  LuaBmpBlend */
static int tolua_tiled_BmpBlend_layer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaBmpBlend",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaBmpBlend* self = (LuaBmpBlend*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'layer'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->layer();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'layer'.",&tolua_err);
 return 0;
#endif
}

/* method: mainTile of class  LuaBmpBlend */
static int tolua_tiled_BmpBlend_mainTile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaBmpBlend",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaBmpBlend* self = (LuaBmpBlend*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'mainTile'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->mainTile();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'mainTile'.",&tolua_err);
 return 0;
#endif
}

/* method: blendTile of class  LuaBmpBlend */
static int tolua_tiled_BmpBlend_blendTile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaBmpBlend",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaBmpBlend* self = (LuaBmpBlend*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'blendTile'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->blendTile();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'blendTile'.",&tolua_err);
 return 0;
#endif
}

/* method: direction of class  LuaBmpBlend */
static int tolua_tiled_BmpBlend_direction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaBmpBlend",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaBmpBlend* self = (LuaBmpBlend*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'direction'",NULL);
#endif
  {
   LuaBmpBlend::Direction tolua_ret = (LuaBmpBlend::Direction)  self->direction();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'direction'.",&tolua_err);
 return 0;
#endif
}

/* method: exclude of class  LuaBmpBlend */
static int tolua_tiled_BmpBlend_exclude00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaBmpBlend",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaBmpBlend* self = (LuaBmpBlend*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'exclude'",NULL);
#endif
  {
   QList<QString> tolua_ret = (QList<QString>)  self->exclude();
   lua_newtable(tolua_S);
   for (int i = 0; i < tolua_ret.size(); i++) {
    const char *v = cstring(tolua_ret[i]);
    tolua_pushfieldstring(tolua_S,2,i+1,v);
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'exclude'.",&tolua_err);
 return 0;
#endif
}

/* method: set of class  LuaMapNoBlend */
static int tolua_tiled_MapNoBlend_set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMapNoBlend",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isboolean(tolua_S,4,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,5,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMapNoBlend* self = (LuaMapNoBlend*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  bool noblend = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'set'",NULL);
#endif
  {
   self->set(x,y,noblend);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'set'.",&tolua_err);
 return 0;
#endif
}

/* method: set of class  LuaMapNoBlend */
static int tolua_tiled_MapNoBlend_set01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMapNoBlend",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"LuaRegion",0,&tolua_err) || 
     !tolua_isboolean(tolua_S,3,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,4,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaMapNoBlend* self = (LuaMapNoBlend*)  tolua_tousertype(tolua_S,1,0);
  LuaRegion* rgn = ((LuaRegion*)  tolua_tousertype(tolua_S,2,0));
  bool noblend = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'set'",NULL);
#endif
  {
   self->set(*rgn,noblend);
  }
 }
 return 0;
tolua_lerror:
 return tolua_tiled_MapNoBlend_set00(tolua_S);
}

/* method: get of class  LuaMapNoBlend */
static int tolua_tiled_MapNoBlend_get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMapNoBlend",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,4,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMapNoBlend* self = (LuaMapNoBlend*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'get'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->get(x,y);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'get'.",&tolua_err);
 return 0;
#endif
}

/* method: new of class  LuaMap */
static int tolua_tiled_Map_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,5,1,&tolua_err) || 
     !tolua_isnumber(tolua_S,6,1,&tolua_err) || 
     !tolua_isnoobj(tolua_S,7,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap::Orientation orient = ((LuaMap::Orientation) (int)  tolua_tonumber(tolua_S,2,0));
  int width = ((int)  tolua_tonumber(tolua_S,3,0));
  int height = ((int)  tolua_tonumber(tolua_S,4,0));
  int tileWidth = ((int)  tolua_tonumber(tolua_S,5,64));
  int tileHeight = ((int)  tolua_tonumber(tolua_S,6,32));
  {
   LuaMap* tolua_ret = (LuaMap*)  new LuaMap(orient,width,height,tileWidth,tileHeight);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaMap");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: orientation of class  LuaMap */
static int tolua_tiled_Map_orientation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'orientation'",NULL);
#endif
  {
   LuaMap::Orientation tolua_ret = (LuaMap::Orientation)  self->orientation();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'orientation'.",&tolua_err);
 return 0;
#endif
}

/* method: width of class  LuaMap */
static int tolua_tiled_Map_width00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'width'",NULL);
#endif
  {
   int tolua_ret = (int)  self->width();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'width'.",&tolua_err);
 return 0;
#endif
}

/* method: height of class  LuaMap */
static int tolua_tiled_Map_height00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'height'",NULL);
#endif
  {
   int tolua_ret = (int)  self->height();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'height'.",&tolua_err);
 return 0;
#endif
}

/* method: maxLevel of class  LuaMap */
static int tolua_tiled_Map_maxLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'maxLevel'",NULL);
#endif
  {
   int tolua_ret = (int)  self->maxLevel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'maxLevel'.",&tolua_err);
 return 0;
#endif
}

/* method: addLayer of class  LuaMap */
static int tolua_tiled_Map_addLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"LuaLayer",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  LuaLayer* layer = ((LuaLayer*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addLayer'",NULL);
#endif
  {
   self->addLayer(layer);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addLayer'.",&tolua_err);
 return 0;
#endif
}

/* method: insertLayer of class  LuaMap */
static int tolua_tiled_Map_insertLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isusertype(tolua_S,3,"LuaLayer",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,4,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  LuaLayer* layer = ((LuaLayer*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'insertLayer'",NULL);
#endif
  {
   self->insertLayer(index,layer);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'insertLayer'.",&tolua_err);
 return 0;
#endif
}

/* method: removeLayer of class  LuaMap */
static int tolua_tiled_Map_removeLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeLayer'",NULL);
#endif
  {
   self->removeLayer(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeLayer'.",&tolua_err);
 return 0;
#endif
}

/* method: layerCount of class  LuaMap */
static int tolua_tiled_Map_layerCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'layerCount'",NULL);
#endif
  {
   int tolua_ret = (int)  self->layerCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'layerCount'.",&tolua_err);
 return 0;
#endif
}

/* method: layerAt of class  LuaMap */
static int tolua_tiled_Map_layerAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'layerAt'",NULL);
#endif
  {
   LuaLayer* tolua_ret = (LuaLayer*)  self->layerAt(index);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'layerAt'.",&tolua_err);
 return 0;
#endif
}

/* method: layer of class  LuaMap */
static int tolua_tiled_Map_layer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isstring(tolua_S,2,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'layer'",NULL);
#endif
  {
   LuaLayer* tolua_ret = (LuaLayer*)  self->layer(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'layer'.",&tolua_err);
 return 0;
#endif
}

/* method: tileLayer of class  LuaMap */
static int tolua_tiled_Map_tileLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isstring(tolua_S,2,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tileLayer'",NULL);
#endif
  {
   LuaTileLayer* tolua_ret = (LuaTileLayer*)  self->tileLayer(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaTileLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tileLayer'.",&tolua_err);
 return 0;
#endif
}

/* method: newTileLayer of class  LuaMap */
static int tolua_tiled_Map_newTileLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isstring(tolua_S,2,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'newTileLayer'",NULL);
#endif
  {
   LuaTileLayer* tolua_ret = (LuaTileLayer*)  self->newTileLayer(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaTileLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'newTileLayer'.",&tolua_err);
 return 0;
#endif
}

/* method: newObjectLayer of class  LuaMap */
static int tolua_tiled_Map_newObjectLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isstring(tolua_S,2,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'newObjectLayer'",NULL);
#endif
  {
   LuaObjectGroup* tolua_ret = (LuaObjectGroup*)  self->newObjectLayer(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaObjectGroup");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'newObjectLayer'.",&tolua_err);
 return 0;
#endif
}

/* method: addTileset of class  LuaMap */
static int tolua_tiled_Map_addTileset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"Tileset",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  Tileset* tileset = ((Tileset*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addTileset'",NULL);
#endif
  {
   self->addTileset(tileset);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addTileset'.",&tolua_err);
 return 0;
#endif
}

/* method: tilesetCount of class  LuaMap */
static int tolua_tiled_Map_tilesetCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tilesetCount'",NULL);
#endif
  {
   int tolua_ret = (int)  self->tilesetCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tilesetCount'.",&tolua_err);
 return 0;
#endif
}

/* method: tileset of class  LuaMap */
static int tolua_tiled_Map_tileset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isstring(tolua_S,2,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tileset'",NULL);
#endif
  {
   Tileset* tolua_ret = (Tileset*)  self->tileset(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tileset");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tileset'.",&tolua_err);
 return 0;
#endif
}

/* method: tilesetAt of class  LuaMap */
static int tolua_tiled_Map_tilesetAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tilesetAt'",NULL);
#endif
  {
   Tileset* tolua_ret = (Tileset*)  self->tilesetAt(index);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tileset");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tilesetAt'.",&tolua_err);
 return 0;
#endif
}

/* method: tile of class  LuaMap */
static int tolua_tiled_Map_tile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isstring(tolua_S,2,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tile'",NULL);
#endif
  {
   Tile* tolua_ret = (Tile*)  self->tile(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tile");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tile'.",&tolua_err);
 return 0;
#endif
}

/* method: tile of class  LuaMap */
static int tolua_tiled_Map_tile01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isstring(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,4,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  const char* tilesetName = ((const char*)  tolua_tostring(tolua_S,2,0));
  int id = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tile'",NULL);
#endif
  {
   Tile* tolua_ret = (Tile*)  self->tile(tilesetName,id);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tile");
  }
 }
 return 1;
tolua_lerror:
 return tolua_tiled_Map_tile00(tolua_S);
}

/* method: noneTile of class  LuaMap */
static int tolua_tiled_Map_noneTile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'noneTile'",NULL);
#endif
  {
   Tile* tolua_ret = (Tile*)  self->noneTile();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"Tile");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'noneTile'.",&tolua_err);
 return 0;
#endif
}

/* method: setTileSelection of class  LuaMap */
static int tolua_tiled_Map_setTileSelection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"LuaRegion",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  LuaRegion* rgn = ((LuaRegion*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTileSelection'",NULL);
#endif
  {
   self->setTileSelection(*rgn);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTileSelection'.",&tolua_err);
 return 0;
#endif
}

/* method: tileSelection of class  LuaMap */
static int tolua_tiled_Map_tileSelection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tileSelection'",NULL);
#endif
  {
   LuaRegion tolua_ret =  self->tileSelection();
   {
#ifdef __cplusplus
    void* tolua_obj = new LuaRegion(tolua_ret);
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_LuaRegion),"LuaRegion");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(LuaRegion));
    tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"LuaRegion");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tileSelection'.",&tolua_err);
 return 0;
#endif
}

/* method: replaceTilesByName of class  LuaMap */
static int tolua_tiled_Map_replaceTilesByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isstring(tolua_S,2,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  const char* names = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'replaceTilesByName'",NULL);
#endif
  {
   self->replaceTilesByName(names);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'replaceTilesByName'.",&tolua_err);
 return 0;
#endif
}

/* method: bmp of class  LuaMap */
static int tolua_tiled_Map_bmp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'bmp'",NULL);
#endif
  {
   LuaMapBmp& tolua_ret = (LuaMapBmp&)  self->bmp(index);
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"LuaMapBmp");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'bmp'.",&tolua_err);
 return 0;
#endif
}

/* method: alias of class  LuaMap */
static int tolua_tiled_Map_alias00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isstring(tolua_S,2,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'alias'",NULL);
#endif
  {
   LuaBmpAlias* tolua_ret = (LuaBmpAlias*)  self->alias(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaBmpAlias");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'alias'.",&tolua_err);
 return 0;
#endif
}

/* method: ruleCount of class  LuaMap */
static int tolua_tiled_Map_ruleCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ruleCount'",NULL);
#endif
  {
   int tolua_ret = (int)  self->ruleCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ruleCount'.",&tolua_err);
 return 0;
#endif
}

/* method: ruleAt of class  LuaMap */
static int tolua_tiled_Map_ruleAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ruleAt'",NULL);
#endif
  {
   LuaBmpRule* tolua_ret = (LuaBmpRule*)  self->ruleAt(index);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaBmpRule");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ruleAt'.",&tolua_err);
 return 0;
#endif
}

/* method: rules of class  LuaMap */
static int tolua_tiled_Map_rules00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rules'",NULL);
#endif
  {
   QList<LuaBmpRule*> tolua_ret = (QList<LuaBmpRule*>)  self->rules();
   lua_newtable(tolua_S);
   for (int i = 0; i < tolua_ret.size(); i++) {
    tolua_pushfieldusertype(tolua_S,2,i+1,tolua_ret[i],"LuaBmpRule");
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rules'.",&tolua_err);
 return 0;
#endif
}

/* method: rule of class  LuaMap */
static int tolua_tiled_Map_rule00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isstring(tolua_S,2,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rule'",NULL);
#endif
  {
   LuaBmpRule* tolua_ret = (LuaBmpRule*)  self->rule(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaBmpRule");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rule'.",&tolua_err);
 return 0;
#endif
}

/* method: blends of class  LuaMap */
static int tolua_tiled_Map_blends00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'blends'",NULL);
#endif
  {
   QList<LuaBmpBlend*> tolua_ret = (QList<LuaBmpBlend*>)  self->blends();
   lua_newtable(tolua_S);
   for (int i = 0; i < tolua_ret.size(); i++) {
    tolua_pushfieldusertype(tolua_S,2,i+1,tolua_ret[i],"LuaBmpBlend");
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'blends'.",&tolua_err);
 return 0;
#endif
}

/* method: isBlendTile of class  LuaMap */
static int tolua_tiled_Map_isBlendTile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,2,"Tile",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  Tile* tile = ((Tile*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isBlendTile'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isBlendTile(tile);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isBlendTile'.",&tolua_err);
 return 0;
#endif
}

/* method: blendLayers of class  LuaMap */
static int tolua_tiled_Map_blendLayers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'blendLayers'",NULL);
#endif
  {
   QList<QString> tolua_ret = (QList<QString>)  self->blendLayers();
   lua_newtable(tolua_S);
   for (int i = 0; i < tolua_ret.size(); i++) {
    const char *v = cstring(tolua_ret[i]);
    tolua_pushfieldstring(tolua_S,2,i+1,v);
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'blendLayers'.",&tolua_err);
 return 0;
#endif
}

/* method: noBlend of class  LuaMap */
static int tolua_tiled_Map_noBlend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isstring(tolua_S,2,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  const char* layerName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'noBlend'",NULL);
#endif
  {
   LuaMapNoBlend* tolua_ret = (LuaMapNoBlend*)  self->noBlend(layerName);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaMapNoBlend");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'noBlend'.",&tolua_err);
 return 0;
#endif
}

/* method: reloadRules of class  LuaMap */
static int tolua_tiled_Map_reloadRules00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reloadRules'",NULL);
#endif
  {
   self->reloadRules();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reloadRules'.",&tolua_err);
 return 0;
#endif
}

/* method: reloadBlends of class  LuaMap */
static int tolua_tiled_Map_reloadBlends00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reloadBlends'",NULL);
#endif
  {
   self->reloadBlends();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reloadBlends'.",&tolua_err);
 return 0;
#endif
}

/* method: write of class  LuaMap */
static int tolua_tiled_Map_write00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isstring(tolua_S,2,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
  const char* path = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'write'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->write(path);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'write'.",&tolua_err);
 return 0;
#endif
}

/* method: cellX of class  LuaMap */
static int tolua_tiled_Map_cellX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'cellX'",NULL);
#endif
  {
   int tolua_ret = (int)  self->cellX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'cellX'.",&tolua_err);
 return 0;
#endif
}

/* method: cellY of class  LuaMap */
static int tolua_tiled_Map_cellY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaMap",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaMap* self = (LuaMap*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'cellY'",NULL);
#endif
  {
   int tolua_ret = (int)  self->cellY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'cellY'.",&tolua_err);
 return 0;
#endif
}

/* method: setCursorType of class  LuaTileTool */
static int tolua_tiled_TileTool_setCursorType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileTool",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaTileTool* self = (LuaTileTool*)  tolua_tousertype(tolua_S,1,0);
  LuaTileTool::CursorType type = ((LuaTileTool::CursorType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCursorType'",NULL);
#endif
  {
   self->setCursorType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCursorType'.",&tolua_err);
 return 0;
#endif
}

/* method: currentLayer of class  LuaTileTool */
static int tolua_tiled_TileTool_currentLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaTileTool",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  const LuaTileTool* self = (const LuaTileTool*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'currentLayer'",NULL);
#endif
  {
   LuaTileLayer* tolua_ret = (LuaTileLayer*)  self->currentLayer();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaTileLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'currentLayer'.",&tolua_err);
 return 0;
#endif
}

/* method: applyChanges of class  LuaTileTool */
static int tolua_tiled_TileTool_applyChanges00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileTool",0,&tolua_err) || 
     !tolua_isstring(tolua_S,2,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,3,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaTileTool* self = (LuaTileTool*)  tolua_tousertype(tolua_S,1,0);
  const char* undoText = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'applyChanges'",NULL);
#endif
  {
   self->applyChanges(undoText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'applyChanges'.",&tolua_err);
 return 0;
#endif
}

/* method: angle of class  LuaTileTool */
static int tolua_tiled_TileTool_angle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileTool",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,5,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,6,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaTileTool* self = (LuaTileTool*)  tolua_tousertype(tolua_S,1,0);
  float x1 = ((float)  tolua_tonumber(tolua_S,2,0));
  float y1 = ((float)  tolua_tonumber(tolua_S,3,0));
  float x2 = ((float)  tolua_tonumber(tolua_S,4,0));
  float y2 = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'angle'",NULL);
#endif
  {
   int tolua_ret = (int)  self->angle(x1,y1,x2,y2);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'angle'.",&tolua_err);
 return 0;
#endif
}

/* method: clearToolTiles of class  LuaTileTool */
static int tolua_tiled_TileTool_clearToolTiles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileTool",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaTileTool* self = (LuaTileTool*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearToolTiles'",NULL);
#endif
  {
   self->clearToolTiles();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearToolTiles'.",&tolua_err);
 return 0;
#endif
}

/* method: setToolTile of class  LuaTileTool */
static int tolua_tiled_TileTool_setToolTile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileTool",0,&tolua_err) || 
     !tolua_isstring(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
     !tolua_isusertype(tolua_S,5,"Tile",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,6,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaTileTool* self = (LuaTileTool*)  tolua_tousertype(tolua_S,1,0);
  const char* layer = ((const char*)  tolua_tostring(tolua_S,2,0));
  int x = ((int)  tolua_tonumber(tolua_S,3,0));
  int y = ((int)  tolua_tonumber(tolua_S,4,0));
  Tile* tile = ((Tile*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setToolTile'",NULL);
#endif
  {
   self->setToolTile(layer,x,y,tile);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setToolTile'.",&tolua_err);
 return 0;
#endif
}

/* method: setToolTile of class  LuaTileTool */
static int tolua_tiled_TileTool_setToolTile01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileTool",0,&tolua_err) || 
     !tolua_isstring(tolua_S,2,0,&tolua_err) || 
     !tolua_isusertype(tolua_S,3,"LuaRegion",0,&tolua_err) || 
     !tolua_isusertype(tolua_S,4,"Tile",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,5,&tolua_err)
    )
  goto tolua_lerror;
 else
 {
  LuaTileTool* self = (LuaTileTool*)  tolua_tousertype(tolua_S,1,0);
  const char* layer = ((const char*)  tolua_tostring(tolua_S,2,0));
  LuaRegion* rgn = ((LuaRegion*)  tolua_tousertype(tolua_S,3,0));
  Tile* tile = ((Tile*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setToolTile'",NULL);
#endif
  {
   self->setToolTile(layer,*rgn,tile);
  }
 }
 return 0;
tolua_lerror:
 return tolua_tiled_TileTool_setToolTile00(tolua_S);
}

/* method: clearToolNoBlends of class  LuaTileTool */
static int tolua_tiled_TileTool_clearToolNoBlends00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileTool",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaTileTool* self = (LuaTileTool*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearToolNoBlends'",NULL);
#endif
  {
   self->clearToolNoBlends();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearToolNoBlends'.",&tolua_err);
 return 0;
#endif
}

/* method: setToolNoBlend of class  LuaTileTool */
static int tolua_tiled_TileTool_setToolNoBlend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileTool",0,&tolua_err) || 
     !tolua_isstring(tolua_S,2,0,&tolua_err) || 
     !tolua_isusertype(tolua_S,3,"LuaRegion",0,&tolua_err) || 
     !tolua_isboolean(tolua_S,4,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,5,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaTileTool* self = (LuaTileTool*)  tolua_tousertype(tolua_S,1,0);
  const char* layer = ((const char*)  tolua_tostring(tolua_S,2,0));
  LuaRegion* rgn = ((LuaRegion*)  tolua_tousertype(tolua_S,3,0));
  bool noBlend = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setToolNoBlend'",NULL);
#endif
  {
   self->setToolNoBlend(layer,*rgn,noBlend);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setToolNoBlend'.",&tolua_err);
 return 0;
#endif
}

/* method: clearDistanceIndicators of class  LuaTileTool */
static int tolua_tiled_TileTool_clearDistanceIndicators00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileTool",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaTileTool* self = (LuaTileTool*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearDistanceIndicators'",NULL);
#endif
  {
   self->clearDistanceIndicators();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearDistanceIndicators'.",&tolua_err);
 return 0;
#endif
}

/* method: indicateDistance of class  LuaTileTool */
static int tolua_tiled_TileTool_indicateDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileTool",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,5,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,6,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaTileTool* self = (LuaTileTool*)  tolua_tousertype(tolua_S,1,0);
  int x1 = ((int)  tolua_tonumber(tolua_S,2,0));
  int y1 = ((int)  tolua_tonumber(tolua_S,3,0));
  int x2 = ((int)  tolua_tonumber(tolua_S,4,0));
  int y2 = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'indicateDistance'",NULL);
#endif
  {
   self->indicateDistance(x1,y1,x2,y2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'indicateDistance'.",&tolua_err);
 return 0;
#endif
}

/* method: dragged of class  LuaTileTool */
static int tolua_tiled_TileTool_dragged00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaTileTool",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaTileTool* self = (LuaTileTool*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dragged'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->dragged();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dragged'.",&tolua_err);
 return 0;
#endif
}

/* method: new of class  LuaPerlin */
static int tolua_tiled_Perlin_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaPerlin",0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  {
   LuaPerlin* tolua_ret = (LuaPerlin*)  new LuaPerlin();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaPerlin");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: perlin of class  LuaPerlin */
static int tolua_tiled_Perlin_perlin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaPerlin",0,&tolua_err) || 
     !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
     !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
     !tolua_isnoobj(tolua_S,5,&tolua_err)
    )
  goto tolua_lerror;
 else
#endif
 {
  LuaPerlin* self = (LuaPerlin*)  tolua_tousertype(tolua_S,1,0);
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
  double z = ((double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'perlin'",NULL);
#endif
  {
   double tolua_ret = (double)  self->perlin(x,y,z);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'perlin'.",&tolua_err);
 return 0;
#endif
}

/* Open lib function */
LUALIB_API int  luaopen_tiled (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"Rect","QRect","",tolua_collect_QRect);
#else
 tolua_cclass(tolua_S,"Rect","QRect","",NULL);
#endif
 tolua_beginmodule(tolua_S,"Rect");
 tolua_function(tolua_S,"new",tolua_tiled_Rect_new00);
 tolua_function(tolua_S,"x",tolua_tiled_Rect_x00);
 tolua_function(tolua_S,"y",tolua_tiled_Rect_y00);
 tolua_function(tolua_S,"width",tolua_tiled_Rect_width00);
 tolua_function(tolua_S,"height",tolua_tiled_Rect_height00);
 tolua_function(tolua_S,"left",tolua_tiled_Rect_left00);
 tolua_function(tolua_S,"right",tolua_tiled_Rect_right00);
 tolua_function(tolua_S,"top",tolua_tiled_Rect_top00);
 tolua_function(tolua_S,"bottom",tolua_tiled_Rect_bottom00);
 tolua_function(tolua_S,"translate",tolua_tiled_Rect_translate00);
 tolua_function(tolua_S,"translated",tolua_tiled_Rect_translated00);
 tolua_function(tolua_S,"intersects",tolua_tiled_Rect_intersects00);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"Region","LuaRegion","",tolua_collect_LuaRegion);
#else
 tolua_cclass(tolua_S,"Region","LuaRegion","",NULL);
#endif
 tolua_beginmodule(tolua_S,"Region");
 tolua_function(tolua_S,"new",tolua_tiled_Region_new00);
 tolua_function(tolua_S,"boundingRect",tolua_tiled_Region_boundingRect00);
 tolua_function(tolua_S,"rects",tolua_tiled_Region_rects00);
 tolua_function(tolua_S,"isEmpty",tolua_tiled_Region_isEmpty00);
 tolua_function(tolua_S,"rectCount",tolua_tiled_Region_rectCount00);
 tolua_function(tolua_S,"unite",tolua_tiled_Region_unite00);
 tolua_function(tolua_S,"unite",tolua_tiled_Region_unite01);
 tolua_function(tolua_S,"unite",tolua_tiled_Region_unite02);
 tolua_function(tolua_S,"intersect",tolua_tiled_Region_intersect00);
 tolua_function(tolua_S,"intersect",tolua_tiled_Region_intersect01);
 tolua_function(tolua_S,"intersect",tolua_tiled_Region_intersect02);
 tolua_function(tolua_S,".add",tolua_tiled_Region_operator_add00);
 tolua_function(tolua_S,"intersected",tolua_tiled_Region_intersected00);
 tolua_function(tolua_S,".add",tolua_tiled_Region_operator_add01);
 tolua_function(tolua_S,".sub",tolua_tiled_Region_operator_sub00);
 tolua_function(tolua_S,"intersected",tolua_tiled_Region_intersected01);
 tolua_function(tolua_S,"intersected",tolua_tiled_Region_intersected02);
 tolua_function(tolua_S,"translated",tolua_tiled_Region_translated00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Tile","Tile","",NULL);
 tolua_beginmodule(tolua_S,"Tile");
 tolua_function(tolua_S,"tileset",tolua_tiled_Tile_tileset00);
 tolua_function(tolua_S,"id",tolua_tiled_Tile_id00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Tileset","Tileset","",NULL);
 tolua_beginmodule(tolua_S,"Tileset");
 tolua_function(tolua_S,"name",tolua_tiled_Tileset_name00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Layer","LuaLayer","",NULL);
 tolua_beginmodule(tolua_S,"Layer");
 tolua_function(tolua_S,"asTileLayer",tolua_tiled_Layer_asTileLayer00);
 tolua_function(tolua_S,"asObjectGroup",tolua_tiled_Layer_asObjectGroup00);
 tolua_function(tolua_S,"name",tolua_tiled_Layer_name00);
 tolua_function(tolua_S,"type",tolua_tiled_Layer_type00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"TileLayer","LuaTileLayer","LuaLayer",NULL);
 tolua_beginmodule(tolua_S,"TileLayer");
 tolua_function(tolua_S,"new",tolua_tiled_TileLayer_new00);
 tolua_function(tolua_S,"level",tolua_tiled_TileLayer_level00);
 tolua_function(tolua_S,"setTile",tolua_tiled_TileLayer_setTile00);
 tolua_function(tolua_S,"tileAt",tolua_tiled_TileLayer_tileAt00);
 tolua_function(tolua_S,"clearTile",tolua_tiled_TileLayer_clearTile00);
 tolua_function(tolua_S,"erase",tolua_tiled_TileLayer_erase00);
 tolua_function(tolua_S,"erase",tolua_tiled_TileLayer_erase01);
 tolua_function(tolua_S,"erase",tolua_tiled_TileLayer_erase02);
 tolua_function(tolua_S,"erase",tolua_tiled_TileLayer_erase03);
 tolua_function(tolua_S,"fill",tolua_tiled_TileLayer_fill00);
 tolua_function(tolua_S,"fill",tolua_tiled_TileLayer_fill01);
 tolua_function(tolua_S,"fill",tolua_tiled_TileLayer_fill02);
 tolua_function(tolua_S,"fill",tolua_tiled_TileLayer_fill03);
 tolua_function(tolua_S,"replaceTile",tolua_tiled_TileLayer_replaceTile00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"MapObject","LuaMapObject","",NULL);
 tolua_beginmodule(tolua_S,"MapObject");
 tolua_function(tolua_S,"new",tolua_tiled_MapObject_new00);
 tolua_function(tolua_S,"name",tolua_tiled_MapObject_name00);
 tolua_function(tolua_S,"type",tolua_tiled_MapObject_type00);
 tolua_function(tolua_S,"bounds",tolua_tiled_MapObject_bounds00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"ObjectGroup","LuaObjectGroup","LuaLayer",NULL);
 tolua_beginmodule(tolua_S,"ObjectGroup");
 tolua_function(tolua_S,"new",tolua_tiled_ObjectGroup_new00);
 tolua_function(tolua_S,"setColor",tolua_tiled_ObjectGroup_setColor00);
 tolua_function(tolua_S,"color",tolua_tiled_ObjectGroup_color00);
 tolua_function(tolua_S,"addObject",tolua_tiled_ObjectGroup_addObject00);
 tolua_function(tolua_S,"objects",tolua_tiled_ObjectGroup_objects00);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"Color","LuaColor","",tolua_collect_LuaColor);
#else
 tolua_cclass(tolua_S,"Color","LuaColor","",NULL);
#endif
 tolua_beginmodule(tolua_S,"Color");
 tolua_function(tolua_S,"new",tolua_tiled_Color_new00);
 tolua_function(tolua_S,"new",tolua_tiled_Color_new01);
 tolua_variable(tolua_S,"r",tolua_get_LuaColor_LuaColor_r,tolua_set_LuaColor_LuaColor_r);
 tolua_variable(tolua_S,"g",tolua_get_LuaColor_LuaColor_g,tolua_set_LuaColor_LuaColor_g);
 tolua_variable(tolua_S,"b",tolua_get_LuaColor_LuaColor_b,tolua_set_LuaColor_LuaColor_b);
 tolua_variable(tolua_S,"pixel",tolua_get_LuaColor_LuaColor_unsigned_pixel,tolua_set_LuaColor_LuaColor_unsigned_pixel);
 tolua_endmodule(tolua_S);
 tolua_function(tolua_S,"rgb",tolua_tiled_rgb00);
 tolua_cclass(tolua_S,"LuaMapBmp","LuaMapBmp","MapBmp",NULL);
 tolua_beginmodule(tolua_S,"LuaMapBmp");
 tolua_function(tolua_S,"setPixel",tolua_tiled_LuaMapBmp_setPixel00);
 tolua_function(tolua_S,"pixel",tolua_tiled_LuaMapBmp_pixel00);
 tolua_function(tolua_S,"erase",tolua_tiled_LuaMapBmp_erase00);
 tolua_function(tolua_S,"erase",tolua_tiled_LuaMapBmp_erase01);
 tolua_function(tolua_S,"erase",tolua_tiled_LuaMapBmp_erase02);
 tolua_function(tolua_S,"erase",tolua_tiled_LuaMapBmp_erase03);
 tolua_function(tolua_S,"fill",tolua_tiled_LuaMapBmp_fill00);
 tolua_function(tolua_S,"fill",tolua_tiled_LuaMapBmp_fill01);
 tolua_function(tolua_S,"fill",tolua_tiled_LuaMapBmp_fill02);
 tolua_function(tolua_S,"fill",tolua_tiled_LuaMapBmp_fill03);
 tolua_function(tolua_S,"replace",tolua_tiled_LuaMapBmp_replace00);
 tolua_function(tolua_S,"rand",tolua_tiled_LuaMapBmp_rand00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"BmpAlias","LuaBmpAlias","",NULL);
 tolua_beginmodule(tolua_S,"BmpAlias");
 tolua_function(tolua_S,"tiles",tolua_tiled_BmpAlias_tiles00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"BmpRule","LuaBmpRule","",NULL);
 tolua_beginmodule(tolua_S,"BmpRule");
 tolua_function(tolua_S,"label",tolua_tiled_BmpRule_label00);
 tolua_function(tolua_S,"bmpIndex",tolua_tiled_BmpRule_bmpIndex00);
 tolua_function(tolua_S,"color",tolua_tiled_BmpRule_color00);
 tolua_function(tolua_S,"tiles",tolua_tiled_BmpRule_tiles00);
 tolua_function(tolua_S,"layer",tolua_tiled_BmpRule_layer00);
 tolua_function(tolua_S,"condition",tolua_tiled_BmpRule_condition00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"BmpBlend","LuaBmpBlend","",NULL);
 tolua_beginmodule(tolua_S,"BmpBlend");
 tolua_constant(tolua_S,"Unknown",LuaBmpBlend::Unknown);
 tolua_constant(tolua_S,"N",LuaBmpBlend::N);
 tolua_constant(tolua_S,"S",LuaBmpBlend::S);
 tolua_constant(tolua_S,"E",LuaBmpBlend::E);
 tolua_constant(tolua_S,"W",LuaBmpBlend::W);
 tolua_constant(tolua_S,"NW",LuaBmpBlend::NW);
 tolua_constant(tolua_S,"NE",LuaBmpBlend::NE);
 tolua_constant(tolua_S,"SW",LuaBmpBlend::SW);
 tolua_constant(tolua_S,"SE",LuaBmpBlend::SE);
 tolua_function(tolua_S,"layer",tolua_tiled_BmpBlend_layer00);
 tolua_function(tolua_S,"mainTile",tolua_tiled_BmpBlend_mainTile00);
 tolua_function(tolua_S,"blendTile",tolua_tiled_BmpBlend_blendTile00);
 tolua_function(tolua_S,"direction",tolua_tiled_BmpBlend_direction00);
 tolua_function(tolua_S,"exclude",tolua_tiled_BmpBlend_exclude00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"MapNoBlend","LuaMapNoBlend","",NULL);
 tolua_beginmodule(tolua_S,"MapNoBlend");
 tolua_function(tolua_S,"set",tolua_tiled_MapNoBlend_set00);
 tolua_function(tolua_S,"set",tolua_tiled_MapNoBlend_set01);
 tolua_function(tolua_S,"get",tolua_tiled_MapNoBlend_get00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Map","LuaMap","",NULL);
 tolua_beginmodule(tolua_S,"Map");
 tolua_constant(tolua_S,"Unknown",LuaMap::Unknown);
 tolua_constant(tolua_S,"Orthogonal",LuaMap::Orthogonal);
 tolua_constant(tolua_S,"Isometric",LuaMap::Isometric);
 tolua_constant(tolua_S,"LevelIsometric",LuaMap::LevelIsometric);
 tolua_constant(tolua_S,"Staggered",LuaMap::Staggered);
 tolua_function(tolua_S,"new",tolua_tiled_Map_new00);
 tolua_function(tolua_S,"orientation",tolua_tiled_Map_orientation00);
 tolua_function(tolua_S,"width",tolua_tiled_Map_width00);
 tolua_function(tolua_S,"height",tolua_tiled_Map_height00);
 tolua_function(tolua_S,"maxLevel",tolua_tiled_Map_maxLevel00);
 tolua_function(tolua_S,"addLayer",tolua_tiled_Map_addLayer00);
 tolua_function(tolua_S,"insertLayer",tolua_tiled_Map_insertLayer00);
 tolua_function(tolua_S,"removeLayer",tolua_tiled_Map_removeLayer00);
 tolua_function(tolua_S,"layerCount",tolua_tiled_Map_layerCount00);
 tolua_function(tolua_S,"layerAt",tolua_tiled_Map_layerAt00);
 tolua_function(tolua_S,"layer",tolua_tiled_Map_layer00);
 tolua_function(tolua_S,"tileLayer",tolua_tiled_Map_tileLayer00);
 tolua_function(tolua_S,"newTileLayer",tolua_tiled_Map_newTileLayer00);
 tolua_function(tolua_S,"newObjectLayer",tolua_tiled_Map_newObjectLayer00);
 tolua_function(tolua_S,"addTileset",tolua_tiled_Map_addTileset00);
 tolua_function(tolua_S,"tilesetCount",tolua_tiled_Map_tilesetCount00);
 tolua_function(tolua_S,"tileset",tolua_tiled_Map_tileset00);
 tolua_function(tolua_S,"tilesetAt",tolua_tiled_Map_tilesetAt00);
 tolua_function(tolua_S,"tile",tolua_tiled_Map_tile00);
 tolua_function(tolua_S,"tile",tolua_tiled_Map_tile01);
 tolua_function(tolua_S,"noneTile",tolua_tiled_Map_noneTile00);
 tolua_function(tolua_S,"setTileSelection",tolua_tiled_Map_setTileSelection00);
 tolua_function(tolua_S,"tileSelection",tolua_tiled_Map_tileSelection00);
 tolua_function(tolua_S,"replaceTilesByName",tolua_tiled_Map_replaceTilesByName00);
 tolua_function(tolua_S,"bmp",tolua_tiled_Map_bmp00);
 tolua_function(tolua_S,"alias",tolua_tiled_Map_alias00);
 tolua_function(tolua_S,"ruleCount",tolua_tiled_Map_ruleCount00);
 tolua_function(tolua_S,"ruleAt",tolua_tiled_Map_ruleAt00);
 tolua_function(tolua_S,"rules",tolua_tiled_Map_rules00);
 tolua_function(tolua_S,"rule",tolua_tiled_Map_rule00);
 tolua_function(tolua_S,"blends",tolua_tiled_Map_blends00);
 tolua_function(tolua_S,"isBlendTile",tolua_tiled_Map_isBlendTile00);
 tolua_function(tolua_S,"blendLayers",tolua_tiled_Map_blendLayers00);
 tolua_function(tolua_S,"noBlend",tolua_tiled_Map_noBlend00);
 tolua_function(tolua_S,"reloadRules",tolua_tiled_Map_reloadRules00);
 tolua_function(tolua_S,"reloadBlends",tolua_tiled_Map_reloadBlends00);
 tolua_function(tolua_S,"write",tolua_tiled_Map_write00);
 tolua_function(tolua_S,"cellX",tolua_tiled_Map_cellX00);
 tolua_function(tolua_S,"cellY",tolua_tiled_Map_cellY00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"TileTool","LuaTileTool","",NULL);
 tolua_beginmodule(tolua_S,"TileTool");
 tolua_constant(tolua_S,"None",LuaTileTool::None);
 tolua_constant(tolua_S,"CurbTool",LuaTileTool::CurbTool);
 tolua_constant(tolua_S,"EdgeTool",LuaTileTool::EdgeTool);
 tolua_function(tolua_S,"setCursorType",tolua_tiled_TileTool_setCursorType00);
 tolua_function(tolua_S,"currentLayer",tolua_tiled_TileTool_currentLayer00);
 tolua_function(tolua_S,"applyChanges",tolua_tiled_TileTool_applyChanges00);
 tolua_function(tolua_S,"angle",tolua_tiled_TileTool_angle00);
 tolua_function(tolua_S,"clearToolTiles",tolua_tiled_TileTool_clearToolTiles00);
 tolua_function(tolua_S,"setToolTile",tolua_tiled_TileTool_setToolTile00);
 tolua_function(tolua_S,"setToolTile",tolua_tiled_TileTool_setToolTile01);
 tolua_function(tolua_S,"clearToolNoBlends",tolua_tiled_TileTool_clearToolNoBlends00);
 tolua_function(tolua_S,"setToolNoBlend",tolua_tiled_TileTool_setToolNoBlend00);
 tolua_function(tolua_S,"clearDistanceIndicators",tolua_tiled_TileTool_clearDistanceIndicators00);
 tolua_function(tolua_S,"indicateDistance",tolua_tiled_TileTool_indicateDistance00);
 tolua_function(tolua_S,"dragged",tolua_tiled_TileTool_dragged00);
 tolua_endmodule(tolua_S);
 tolua_cclass(tolua_S,"Perlin","LuaPerlin","",NULL);
 tolua_beginmodule(tolua_S,"Perlin");
 tolua_function(tolua_S,"new",tolua_tiled_Perlin_new00);
 tolua_function(tolua_S,"perlin",tolua_tiled_Perlin_perlin00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}
/* Open tolua function */
TOLUA_API int tolua_tiled_open (lua_State* tolua_S)
{
  lua_pushcfunction(tolua_S, luaopen_tiled);
  lua_pushstring(tolua_S, "tiled");
  lua_call(tolua_S, 1, 0);
  return 1;
}
