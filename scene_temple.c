#include <kos.h>                                                                                                                        
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "scene_temple.h"
#include "scene_soussol.h"
#include "asset/map_temple/mapdata.c"

char *_golem_portrait = "/rd/golem_portrait.png";
char *_marchand_portrait = "/rd/marchand_v1_dith.png";

gameObject *marchand;
gameObject *golem;

void loadTemple(scene* self) {
  mount_romdisk("asset/rd_temple.img.gz", "/rd");
  loadTempleData(self);
  generateFloor(self, 0);
  setPosition(945, 1000);

  marchand = malloc(sizeof(gameObject));
  *marchand = createObject("/rd/marchand_mini.png", 1617, 991, 1);
  golem = malloc(sizeof(gameObject));
  *golem = createObject("/rd/golem_ingame.png", 945, 1780, 1);

  //loadLuaFile(L, "/rd/temple.lua");
  //loadLuaFile(t_data, "/rd/jsontest.lua");

  //music
  self->bgm = "/cd/music/soussol.ogg";
  sndoggvorbis_start(self->bgm, 1);

  self->freeScene = freeTemple;
}

void updateTemple(cont_state_t *state, scene *self){
  char* buf;

  setColor(1, 0, 0);
  drawObject(marchand);
  drawObject(golem);
  resetColor();

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


  //WARP 2 SOUS-SOL
  if(over(&self->obj[9])){
    writeFont("To the basement", p1.obj.x + 16, p1.obj.y - 16);
    if(buttonPressed(CONT_A)) {
      freeTemple(self);
      loadSoussol(tempScene);
    }
  }

  //WARP 2 DESERT
  if(over(&self->obj[1])){
    writeFont("To the desert", p1.obj.x + 16, p1.obj.y - 16);
    if(buttonPressed(CONT_A)) {
      freeTemple(self);
      loadDesert(tempScene);
    }
  }

  //WARP 2 JARDIN
  if(over(&self->obj[2])){
    writeFont("To the garden", p1.obj.x + 16, p1.obj.y - 16);
    if(buttonPressed(CONT_A)) {
      freeTemple(self);
      loadJardin(tempScene);
    }
  }

  //to menu
  if (buttonPressed(CONT_X)) {
    freeTemple(self);
    loadMenu(tempScene);
  }
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

  sndoggvorbis_stop();
  fs_romdisk_unmount("/rd");
}
