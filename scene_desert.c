#include <kos.h>
#include <oggvorbis/sndoggvorbis.h>

#include "lib/gl_font.h"
#include "header.h"
#include "global_var.h"
#include "scene_desert.h"

void loadDesert(scene *self){
  mount_romdisk("asset/rd_desert.img.gz", "/rd");
  loadMapData(self, "/rd/map_desert.svg");
  setPosition(700, 600);

  self->obj[0] = createObject("/rd/desert_floor.png", -1000, -1000, 1);
  //setScale(&self->obj[0].t, 2);
  generateFloor(self, 0);

  LUA_loadDialog("/rd/hideout_dialog.json");
  LUA_addQuest(0);

  sndoggvorbis_start("/cd/asset/music/desert_n.ogg", 0);
  sndoggvorbis_volume(0);

  game_state = EXPLORATION;
  p1.currentMap = MAP_DESERT;
  //music

  self->renderScene = renderDesert;
  self->updateScene = updateDesert;
  self->freeScene = freeDesert;
}

void soundDistance(scene *self) {
  float range = 1000.0;
  float f_vol = 0; //final volume

  for(int i = 0; i < self->activeNum; i++)
  {
    int d = distance(p1.obj.x, p1.obj.y, self->activeObj[i]->x, self->activeObj[i]->y);
    if(d < range) {
      float volume = ((-d + range) / range) * 255;
      if(volume > f_vol)
        f_vol = volume;
    }
  }
  sndoggvorbis_volume(f_vol);
  setFloat(3, f_vol);
  setParam(4, getPositionString());
}

void renderDesert(scene *self) {

}

void updateDesert(scene *self){
  soundDistance(self);
  /*
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
  */
}

void freeDesert(scene *self){
  int texID[10] = { 0, 1, 2, 3, 4, 5, 6, 8, 9, 11};

  for (int i = 0; i < 10; i++)
      glDeleteTextures(1, &self->obj[texID[i]].t.id);

  free(self->obj);
  mp3_stop();
  fs_romdisk_unmount("/rd");
}
