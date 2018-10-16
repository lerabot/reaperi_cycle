#include "header.h"
#include "scene_template.h"

void loadTemplate(scene* self) {
  loadMapData(self, "/rd/map_template.svg");
  mount_romdisk("asset/rd_template.img.gz", "/rd");
  generateFloor(self, -1);

  self->updateScene   = updateTemplate;
  self->freeScene     = freeTemplate;
  self->renderScene   = renderTemplate;
}

void updateTemplate(scene *self){
}

void renderTemplate(scene *self){
}

void freeTemplate(scene *self){
}
