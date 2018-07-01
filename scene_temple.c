#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "scene_temple.h"
#include "scene_soussol.h"
#include "lib/lua_binds.h"
#include "lib/dreamroqlib.h"

char *_golem_portrait = "/rd/golem_portrait.png";
char *_marchand_portrait = "/rd/marchand_v1_dith.png";

gameObject *marchand;
gameObject *golem;

int intro = 0;
int to_soussol = 0;

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

  //loadLuaFile(L, "/rd/temple.lua");

  ////////////////////////////////////////////////
  for (int i = 0 ; i < self->objNum; i++) {
    if (strcmp(self->obj[i].name, "stair_close.png") == 0)
      to_soussol = i;
  }


  //music
  //self->bgm = "/cd/music/soussol.ogg";
  //sndoggvorbis_start(self->bgm, 1);

  game_state = EXPLORATION;
  p1.currentMap = MAP_TEMPLE;

  LUA_loadDialog("/rd/temple_dialog.json");
  LUA_addQuest(0);

  self->freeScene = freeTemple;
  self->updateScene = updateTemple;
  self->renderScene = renderTemple;;
}

void updateTemple(scene *self){
  //char* buf;
  char *buf = "";
  snprintf(buf, 16, "x-%d y-%d", (int)p1.obj.x, (int)p1.obj.y);
  setParam(5, buf);

  if(intro == 0){
    playROQvideo("/cd/video/fiole_squared.roq");
    activateNPC("magicienne", "");
    intro = 1;
  }

  if(clicked(marchand, CONT_A)) {
    activateNPC("marchand", _marchand_portrait);
  }

  if(clicked(golem, CONT_A)) {
    activateNPC("golem", _golem_portrait);
  }

  if(clicked(&self->obj[to_soussol], CONT_A)) {
    if(p1.questID == QUEST_INTRO) {
      activateNPC("magicienne", "");
      LUA_addQuest(QUEST_SCROLL);
    }
    else {
      freeTemple(self);
      loadSoussol(tempScene);
      setPosition(320, 240);
    }
  }
}

void renderTemple(scene *self) {
  drawObject(marchand);
  drawObject(golem);
}

void freeTemple(scene *self){
  freeSpritesheet();
  glDeleteTextures(1, &marchand->t.id);
  glDeleteTextures(1, &golem->t.id);

  free(marchand);
  free(golem);
  free(self->obj);

  //sndoggvorbis_stop();
  fs_romdisk_unmount("/rd");
}
