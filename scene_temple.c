#include <kos.h>                                                       
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "scene_temple.h"
#include "scene_soussol.h"


char *_golem_portrait = "/rd/golem_portrait.png";
char *_marchand_portrait = "/rd/marchand_v1_dith.png";

gameObject *marchand;
gameObject *golem;

void loadTemple(scene* self) {
  mount_romdisk("asset/rd_temple.img.gz", "/rd");
  loadMapData(self, "/rd/map_temple_v7.svg");

  self->obj[0] = createObject("/rd/floor.png", -1000, -1000, 1);
  generateFloor(self, 0);
  setPosition(1200, 300);

  marchand = malloc(sizeof(gameObject));
  *marchand = createObject("/rd/marchand_mini.png", 935, 548, 1);
  golem = malloc(sizeof(gameObject));
  *golem = createObject("/rd/golem_ingame.png", 625, 2130, 1);
  flipU(&golem->t);

  loadLuaFile(L, "/rd/temple.lua");

  //music
  //self->bgm = "/cd/music/soussol.ogg";
  //sndoggvorbis_start(self->bgm, 1);

  game_state = EXPLORATION;

  self->freeScene = freeTemple;
  self->updateScene = updateTemple;
  self->renderScene = renderTemple;
}

void updateTemple(scene *self){
  //char* buf;
  char *buf = "";
  snprintf(buf, 16, "x-%d y-%d", (int)p1.obj.x, (int)p1.obj.y);
  setParam(3, buf);

  if(clicked(marchand, CONT_A)) {
    lua_getglobal(L, "setDialog");
    lua_pushstring(L, "marchand");
    lua_pushstring(L, "coin");
    lua_pcall(L, 2, 0, 0);
    lua_settop(L, 0);
    lua_getglobal(L, "getDialog");
    lua_pcall(L, 0, 1, 0);
    buf = lua_tostring(L, -1);
    lua_pop(L,1);
    setDialog(buf, _marchand_portrait);
  }

  if(clicked(golem, CONT_A)) {
    lua_getglobal(L, "setDialog");
    lua_pushstring(L, "golem");
    lua_pcall(L, 1, 0, 0);
    lua_settop(L, 0);
    lua_getglobal(L, "getDialog");
    lua_pcall(L, 0, 1, 0);
    buf = lua_tostring(L, -1);
    lua_pop(L,1);
    setDialog(buf, _golem_portrait);
  }
}

void renderTemple(scene *self) {
    drawObject(marchand);
    drawObject(golem);
}

void freeTemple(scene *self){
  int texID[12] = {0, 1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 18};

  for (int i = 0; i < 12; i++)
    glDeleteTextures(1, &self->obj[texID[i]].t.id);

  glDeleteTextures(1, &marchand->t.id);
  glDeleteTextures(1, &golem->t.id);

  free(marchand);
  free(golem);
  free(self->obj);

  //sndoggvorbis_stop();
  fs_romdisk_unmount("/rd");
}
