#include <kos.h>
#include <stdlib.h>
#include "header.h"
#include "scene_template.h"

void loadTemplate(scene* self) {
  mount_romdisk("asset/rd_template.img.gz", "/rd");
  generateFloor(self, -1);

  self->updateScene   = updateTemplate;
  self->freeScene     = freeTemplate;
  self->renderScene   = renderTemplate;
}

void updateTemplate(scene *self){
}

void renderTemplate(scene *self){
  glPushMatrix();
  glTranslated((int)displayPos[0], (int)displayPos[1], displayPos[2]);
  if (self != NULL)
  {
    if (self->floorTex != -1)
      drawMap(&self->obj[self->floorTex].t, self->mapSize[0]/2, self->mapSize[1]/2);

    for (int i = 0; i < self->objNum; i++){
      drawObject(&self->obj[i]);
    }
  }
  glPopMatrix();
}

void freeTemplate(scene *self){

  for (int i = 0; i < self->objNum; i++){
    if(&self->obj[i].t.id != 0)
      glDeleteTextures(1, &self->obj[i].t.id);
  }

  free(self->obj);
}
