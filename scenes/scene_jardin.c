#include <kos.h>
#include <stdlib.h>
#include "../header.h"
#include "scene_jardin.h"

void loadJardin(scene* self) {
  mount_romdisk("asset/rd_jardin.img.gz", "/rd");

  //loadJardinData(self);
  generateFloor(self, 0);

  //music
  //self->bgm = "/pc/music/jardin.mp3";
  //mp3_start(self->bgm, 1);

  self->updateScene = updateJardin;
  self->freeScene = freeJardin;
}

void updateJardin(scene *self){

  //TEMPLE
  if(over(&self->obj[3])){
    writeFont("Vers le temple", p1.obj.x + 16, p1.obj.y - 16);
    if(buttonPressed(CONT_A)) {
      freeJardin(self);
      loadTemple(tempScene);
      setPosition(1397, 1741);
    }
  }

  if (buttonPressed(CONT_X)) {
    freeJardin(self);
    loadMenu(tempScene);
  }
}

void freeJardin(scene *self){
  //DON'T FORGET THE FLOOR!
  int t[12] = { 0, 1, 2, 3, 4, 5, 6, 11, 48, 66, 67, 105};
  for (int i = 0; i < 12; i++){
      glDeleteTextures(1, &self->obj[t[i]].t.id);
  }
  free(self->obj);
  //mp3_stop();
  fs_romdisk_unmount("/rd");
}
