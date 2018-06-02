#include <kos.h>
#include <stdlib.h>
#include "header.h"
#include "scene_test.h"

#include "lib/dreamroqlib.h"
#include "asset/map_test/mapdata.c"

void loadTestData(scene* self);

texture _t;
gameObject portrait;
roq_callbacks_t cbs;

void loadTest(scene* self) {
  mount_romdisk("/asset/rd_test.img.gz", "/rd");
  loadMapData(self, "/rd/map_guild2.svg");

  generateFloor(self, -1);
  setPosition(320, 240);

  game_state = EXPLORATION;
  self->renderScene = renderTest;
  self->updateScene = updateTest;
  self->freeScene = freeTest;
}

void renderTest(scene *self){
  glPushMatrix();
  glTranslated((int)displayPos[0], (int)displayPos[1], displayPos[2]);
  if (self != NULL)
  {
    if (self->floorTex != -1)
      drawMap(&self->obj[self->floorTex].t, self->mapSize[0]/2, self->mapSize[1]/2);

    for (int i = 0; i < self->objNum; i++){
      drawObject(&self->obj[i]);
    }

    //drawObject(&sprite_t);
    //updateLight(self);
    //updateEnigme(self);
  }
  glPopMatrix();
}

void updateTest(scene *self){
  /*
  drawObject(&portrait);

  char *buf = "";
  snprintf(buf, 16, "x-%d y-%d", (int)p1.obj.x, (int)p1.obj.y);
  setParam(5, buf);

  //if(dreamroq_play("/rd/test_512_square.roq", ROQ_RGB565, 1, &cbs))
    //setParam(2, "Can't open ROQ file.");

  */
}

void freeTest(scene *self){

  for (int i = 0; i < self->objNum; i++){
    if(&self->obj[i].t.id != 0)
      glDeleteTextures(1, &self->obj[i].t.id);
  }

  free(self->obj);
}
