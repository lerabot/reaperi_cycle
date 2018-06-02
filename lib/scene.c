#include <kos.h>
#include "game_object.h"
#include "scene.h"
#include "tilemap.h"
#include "../global_var.h"
#include "../utils.h"
#include "debug_screen.h"

gameObject spritesheet;

/*
void renderScene(scene *s){
  glPushMatrix();
  glTranslated((int)displayPos[0], (int)displayPos[1], displayPos[2]);
  if (s != NULL)
  {
    if (s->floorTex != -1)
      drawMap(&s->obj[s->floorTex].t, s->mapSize[0]/2, s->mapSize[1]/2);

    for (int i = 0; i < s->objNum; i++){
      drawObject(&s->obj[i]);
    }
  }
  glPopMatrix();
}
*/

void loadMapData(scene *self, char* filename) {
  loadLuaFile(t_data, findFile("/script/loadMap.lua"));

  spritesheet = createObject("/rd/spritesheet.png", -1000, -1000, 1);

  //get general map info - SIZE / OBJNUM / name
  lua_getglobal(t_data, "loadXML");
  lua_pushstring(t_data, filename);
  lua_pcall(t_data, 1, 1, 0);
  char *buf = lua_tostring(t_data, -1);
  setParam(1, buf);

  //get the data
  lua_settop(t_data, 0);
  lua_getglobal(t_data, "getMapInfo");
  lua_pcall(t_data, 0, 3, 0); //x_map, y_map, obj_num
  self->mapSize[0] = lua_tonumber(t_data, 1);
  self->mapSize[1] = lua_tonumber(t_data, 2);
  self->objNum = lua_tonumber(t_data, 3);
  lua_settop(t_data, 0);

  //loading the json spritesheet data
  lua_getglobal(t_data, "loadJSON");
  lua_pushstring(t_data, "/rd/spritesheet.json");
  lua_pcall(t_data, 1, 1, 0);
  lua_settop(t_data, 0);


  self->obj = malloc(sizeof(gameObject) * self->objNum);
  for (int i = 0; i < self->objNum; i++) { //LUA OFFSET!!!!
    lua_getglobal(t_data, "createObject");
    lua_pushnumber(t_data, i+1);
    lua_pcall(t_data, 1, 10, 0);
    self->obj[i] = createObject("", 0, 0, 1);
    self->obj[i].t = spritesheet.t;
    self->obj[i].x =        lua_tonumber(t_data, 1);
    self->obj[i].y =        lua_tonumber(t_data, 2);
    self->obj[i].z =        1;
    //self->obj[i].t.w =      lua_tonumber(t_data, 3);
    //self->obj[i].t.h =      lua_tonumber(t_data, 4);
    self->obj[i].t.u =      lua_tonumber(t_data, 5);
    self->obj[i].t.v =      lua_tonumber(t_data, 6);
    self->obj[i].t.uSize =  lua_tonumber(t_data, 7);
    self->obj[i].t.vSize =  lua_tonumber(t_data, 8);
    self->obj[i].t.xScale = lua_tonumber(t_data, 9);
    self->obj[i].desc =     lua_tostring(t_data,10);
    lua_settop(t_data, 0);
  }
}

void setMapInfo(scene *s, int x, int y, int xStart, int yStart){
  s->mapSize[0] = x;
  s->mapSize[1] = y;
  setPosition(xStart, yStart);
}

void update_Scene(scene *self) {
  self->updateScene(self);
}

void renderScene(scene *self){
  glPushMatrix();
  glTranslated((int)displayPos[0], (int)displayPos[1], displayPos[2]);
  if (self != NULL)
  {
    if (self->floorTex != -1)
      drawMap(&self->obj[self->floorTex].t, self->mapSize[0]/2, self->mapSize[1]/2);

    for (int i = 0; i < self->objNum; i++){
      drawObject(&self->obj[i]);
    }

    self->renderScene(self);

  }
  glPopMatrix();
}