#include <kos.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "debug_screen.h"
#include "gl_font.h"
#include "../global_var.h"
#include "gl_png.h"
#include "gl_pvr_texture.h"
#include "game_object.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

gameObject createObject(char *path, float x, float y, int visible){
  gameObject temp;

  png_to_gl_texture(&temp.t, path);
  temp.x = x;
  temp.y = y;
  temp.z = 0;
  temp.visible = visible;
  temp.t.a = visible;
  temp.size = 1;
  temp.frames = 1;
  temp.cFrame = 0;
  temp.active = 1;
  temp.emitLight = 0;
  temp.name = "";
  temp.desc = "";
  temp.npcID = "";
  temp.portraitID = "";
  return(temp);
}

gameObject createObjectDTEX(char *path, float x, float y, int visible){
  gameObject temp;

  dtex_to_gl_texture(&temp.t, path);
  temp.x = x;
  temp.y = y;
  temp.z = 0;
  temp.visible = visible;
  temp.t.a = visible;
  temp.size = 1;
  temp.frames = 1;
  temp.cFrame = 0;
  temp.active = 1;
  temp.emitLight = 0;
  temp.name = "";
  temp.desc = "";
  temp.npcID = "";
  temp.portraitID = "";
  return(temp);
}

int createObjectLUA(lua_State *L) {

  //return
}

int setScript(gameObject *object, lua_State *L, char *path) {
  if(luaL_loadfile(L, path) || lua_pcall(L, 0, 0, 0)) {
    setParam(2, "Lua Loading Failed");
    return 1;
  }
  else {
    object->script = path;
    setParam(2, object->script);
    return 0;
  }
}

int activate(gameObject *object, lua_State *L){
  if(luaL_dofile(L, object->script)) {
    setParam(2, "Lua Execution Failed");
    return 1;
  }
  else {
    //setParam(5, lua_tostring(L, -1));
    return 0;
  }
}

int mouseOver(gameObject *cursor, gameObject *target){
  float xSize = target->t.size[0];
  float ySize = target->t.size[1];

  if (  (cursor->x > target->x-xSize/2) &&
        (cursor->x < target->x+xSize/2) &&
        (cursor->y > target->y-ySize/2) &&
        (cursor->y < target->y+ySize/2))
        {
          return(1);
        }
  else
    return(0);
}

void setTexSize(gameObject *object, int size){
  object->size = size;
}

void setVisible(gameObject *object, int visible){
  object->visible = visible;
}

void setAlpha(gameObject *object, float alpha){
  if (alpha > 1)
    object->t.a = 1;
  else if (alpha < 0)
    object->t.a = 0;
  else
    object->t.a = alpha;
}

void executeLight(gameObject *object, gameObject *target){
  float noise = 0;
  int   dist = 350;

  if(frameCount % ((rand() % 8) + 3) == 0)
    noise = (rand() % 5) / 20.0;

  if(object->active == 1 && object->emitLight > 0) {
    float _l = 0;
    float _d = sqrt((object->x - target->x) * (object->x - target->x) + (object->y - target->y) * (object->y - target->y));
    if (_d < dist) {
      _l = ((- _d / dist) + 1 ) * (noise + object->emitLight);
      _l += target->t.light;
      setLight(&target->t, _l);
    }
    else {
      _l = (- _d / dist) ;
    }

  }
}

void nextFrame(gameObject *object, int delay){
  if(frameCount % delay == 0) {
    if (object->cFrame < object->frames)
      object->cFrame++;
    else
      object->cFrame = 0;
  }
  setAnim(&object->t, object->cFrame);
}

void moveObject(gameObject *object, float x, float y){
  object->x = x;
  object->y = y;
}

void drawObject(gameObject *object){
  draw_textured_quad(&object->t, object->x, object->y, object->z);
}

void setTexture(gameObject *object, texture *t){
  object->t = *t;
}
