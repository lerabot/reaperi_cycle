#include "../header.h"
#include "../global_var.h"
#include "scene_illusion.h"
#include "scene.h"

void loadIllusion(scene* self) {
  mount_romdisk("/asset/rd_illusion.img.gz", "/rd_map");
  loadMapData(self, "/rd_map/map_illusion.svg");
  generateFloor(self, -1);

  setInt(2, self->objNum);

  game_state = EXPLORATION;

  self->updateScene   = updateIllusion;
  self->freeScene     = freeIllusion;
  self->renderScene   = renderIllusion;
}

void updateIllusion(scene *self){
}

void renderIllusion(scene *self){
}

void freeIllusion(scene *self){
}
