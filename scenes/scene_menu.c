#include <kos.h>
#include <stdlib.h>
#include <string.h>
#include "../header.h"
#include "scene_menu.h"
#include "../global_var.h"

char *map[4] = {"Temple", "Sous-sol", "Jardin", "Desert"};
int   mapSelect = 0;
int   _frame = 1;

void loadMenu(scene* self) {
  ////MAP DATA////
  mount_romdisk("asset/rd_menu.img.gz", "/rd");
  setMapInfo(self, 640, 480, 320, 240);
  hideController();

  self->objNum = 2;
  self->obj = malloc(sizeof(gameObject) * self->objNum);
  self->obj[0] = createObject("/rd/flag_anim.png", 540, 260, 1);
  self->obj[1] = createObject("/rd/logo.png", 320, 240,1);
  setUV(&self->obj[0].t, 0.25, 0.25);
  self->obj[0].frames = 16;
  setAnim(&self->obj[0].t, 3);
  //flipU(&self->obj[0].t);
  //setScale(&self->obj[0].t, 1);
  generateFloor(self, -1);

  //music
  self->bgm = "/cd/asset/music/title.ogg";
  sndoggvorbis_start(self->bgm, 1);
  sndoggvorbis_volume(255);

  game_state = EXPLORATION;

  self->renderScene = renderMenuScreen;
  self->updateScene = updateMenu;
  self->freeScene   = freeMenu;
}

void renderMenuScreen(scene *s){
}

void updateMenu(scene *self){
  char buf[32];

  nextFrame(&self->obj[0], 5);

  if (buttonPressed(CONT_DPAD_DOWN) && mapSelect < 3)
    mapSelect++;
  if (buttonPressed(CONT_DPAD_UP) && mapSelect > 0)
    mapSelect--;


  if (buttonPressed(CONT_A)) {
    freeMenu(self);
    showController();
    switch(mapSelect) {
        case 0:
          loadTemple(tempScene);
          break;
        case 1:
          loadSoussol(tempScene);
          break;
        case 2:
          loadJardin(tempScene);
          break;
        case 3:
          loadDesert(tempScene);
          break;
    }
  }

  snprintf(buf, 32, "Travel to the %s", map[mapSelect]);
  writeFont(buf, 320 - (13 * 8), 120);
  writeFont("v0.2", 320 - (2 * 8), 100);
}

void freeMenu(scene *self){
  //mp3_stop();
  glDeleteTextures(1, &self->obj[0].t.id);
  glDeleteTextures(1, &self->obj[1].t.id);

  free(self->obj);
  fs_romdisk_unmount("/rd");
}
