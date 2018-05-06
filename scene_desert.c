#include <kos.h>
#include "header.h"
#include "scene_desert.h"
#include "asset/map_desert/mapdata.c"

void loadDesert(scene *self){
  mount_romdisk("asset/rd_desert.img.gz", "/rd");

  loadDesertData(self);
  generateFloor(self, 0);

  //music
  self->bgm = "/pc/music/desert.mp3";
  mp3_start(self->bgm, 1);

  self->updateScene = updateDesert;
}

void updateDesert(cont_state_t *state, scene *self){

  //TEMPLE
  if(over(&self->obj[2])){
    writeFont("Vers le temple", p1.obj.x + 16, p1.obj.y - 16);
    if(buttonPressed(CONT_A)) {
      freeDesert(self);
      loadTemple(tempScene);
      setPosition(490, 1724);
    }
  }


  //to menu
  if (buttonPressed(CONT_X)) {
    freeDesert(self);
    loadMenu(tempScene);
  }
}

void freeDesert(scene *self){
  int texID[10] = { 0, 1, 2, 3, 4, 5, 6, 8, 9, 11};

  for (int i = 0; i < 10; i++)
      glDeleteTextures(1, &self->obj[texID[i]].t.id);

  free(self->obj);
  mp3_stop();
  fs_romdisk_unmount("/rd");
}
