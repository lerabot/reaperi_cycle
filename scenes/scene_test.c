#include <kos.h>
#include <stdlib.h>
#include "../header.h"
#include "scene_test.h"

#include "dreamroqlib.h"

void loadTestData(scene* self);

texture _t;
gameObject portrait;

void loadTest(scene* self) {
  mount_romdisk("/asset/rd_test.img.gz", "/rd");
  loadMapData(self, "/rd/map_guild2.svg");

  generateFloor(self, 0);
  setPosition(320, 240);

  LUA_addQuest(0);

  game_state = EXPLORATION;
  self->renderScene = renderTest;
  self->updateScene = updateTest;
  self->freeScene = freeTest;

  //dreamroq_play("/rd/test_512_square.roq", ROQ_RGB565, 1, &cbs)
}

void renderTest(scene *self){

}

void updateTest(scene *self){

}

void freeTest(scene *self){

  for (int i = 0; i < self->objNum; i++){
    if(&self->obj[i].t.id != 0)
      glDeleteTextures(1, &self->obj[i].t.id);
  }

  free(self->obj);
}
