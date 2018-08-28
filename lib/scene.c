  #include <kos.h>
#include "game_object.h"
#include "scene.h"
#include "tilemap.h"
#include "../global_var.h"
#include "../utils.h"
#include "gl_font.h"
#include "debug_screen.h"

gameObject spritesheet;

void loadMapData(scene *self, char* filename) {
  //spritesheet = createObject("/rd/spritesheet.png", -1000, -1000, 1);
  spritesheet = createObjectDTEX("/rd/spritesheet.tex", -1000, -1000, 1);

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

  int depth = 0;
  self->obj = malloc(sizeof(gameObject) * self->objNum);
  self->activeNum = 0;
  for (int i = 0; i < self->objNum; i++) {
    lua_getglobal(t_data, "createObject");
    lua_pushnumber(t_data, i+1); // +1 = lua offset
    lua_pcall(t_data, 1, 10, 0);
    self->obj[i] = createObject("", 0, 0, 1);
    self->obj[i].t = spritesheet.t;
    self->obj[i].x =        lua_tonumber(t_data, 1);
    self->obj[i].y =        lua_tonumber(t_data, 2);
    self->obj[i].z =        depth += 0.01;
    self->obj[i].t.u =      lua_tonumber(t_data, 3);
    self->obj[i].t.v =      lua_tonumber(t_data, 4);
    self->obj[i].t.uSize =  lua_tonumber(t_data, 5);
    self->obj[i].t.vSize =  lua_tonumber(t_data, 6);
    self->obj[i].t.xScale = lua_tonumber(t_data, 7);
    self->obj[i].desc =     lua_tostring(t_data, 8);
    self->obj[i].name =     lua_tostring(t_data, 9);
    self->obj[i].npcID =    lua_tostring(t_data, 10);

    if (strlen(self->obj[i].npcID) > 2)
      self->activeNum++;

    lua_settop(t_data, 0);
  }

  self->activeObj = malloc(sizeof(gameObject*) * self->activeNum);

  //assinging  obj > activeObj
  int j = 0;
  for (int i = 0; i < self->objNum; i++) {
    if (strlen(self->obj[i].npcID) > 2) {
      self->activeObj[j++] = &self->obj[i];
    }
  }
  setInt(0, self->activeNum);
}

void setMapInfo(scene *s, int x, int y, int xStart, int yStart){
  s->mapSize[0] = x;
  s->mapSize[1] = y;
  setPosition(xStart, yStart);
}

void updateScene(scene *self) {
  self->updateScene(self);

  char* message = "";
  char  png[32];
  if (self->activeNum > 0) {
    for(int i = 0; i < self->activeNum; i++) {
      if(clicked(self->activeObj[i], CONT_A)) {
        sprintf(png, "/rd/%s.png", self->activeObj[i]->npcID);
        activateNPC(self->activeObj[i]->npcID, png);
        //setParam(4, png);
      }
    }
  }
}

void renderScene(scene *self){
  glLoadIdentity();
  glPushMatrix();
  glTranslated((int)displayPos[0], (int)displayPos[1], displayPos[2]);
  if (self != NULL)
  {
    if (self->floorTex != -1)
      drawMap(&self->obj[self->floorTex].t, self->mapSize[0]/2, self->mapSize[1]/2);

    drawShadow();

    for (int i = 0; i < self->objNum; i++){
      if(distance(p1.obj.x, p1.obj.y, self->obj[i].x, self->obj[i].y) < 750)
        drawObject(&self->obj[i]);
    }
    self->renderScene(self);
  }
  glPopMatrix();
}

void freeSpritesheet() {
  glDeleteTextures(1, &spritesheet.t.id);
}
