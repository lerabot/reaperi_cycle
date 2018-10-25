#include <kos.h>
#include "gl_font.h"
#include "../header.h"
#include "../global_var.h"
#include "scene.h"
#include "scene_desert.h"

sfxhnd_t  desert_sfx[4];

void loadDesert(scene *self){
  mount_romdisk("asset/rd_desert.img", "/rd");
  loadMapData(self, "/rd/map_desert.svg");

  self->obj[0] = createObject("/rd/floor.png", -1000, -1000, 1);
  //setScale(&self->obj[0].t, 2);
  generateFloor(self, 0);

  LUA_loadDialog("/rd/hideout_dialog.json");
  //LUA_addQuest(0);

  //music
  char *music_path = "";
  //music_path = findFile("/asset/music/soussol.ogg");
  //sndoggvorbis_start("/cd/asset/music/soussol.ogg", 1);
  //sndoggvorbis_volume(255);
  
  desert_sfx[0] = snd_sfx_load("cd/asset/SFX/desert/choir_1.wav");
  desert_sfx[1] = snd_sfx_load("cd/asset/SFX/desert/choir_2.wav");
  desert_sfx[2] = snd_sfx_load("cd/asset/SFX/desert/orgue_3.wav");
  desert_sfx[3] = snd_sfx_load("cd/asset/SFX/desert/orgue_4.wav");
  /*
  desert_sfx[4] = snd_sfx_load("pc/asset/SFX/desert/orgue_10.wav");
  desert_sfx[5] = snd_sfx_load("pc/asset/SFX/desert/orgue_11.wav");
  desert_sfx[6] = snd_sfx_load("cd/asset/SFX/desert/orgue_12.wav");
  desert_sfx[7] = snd_sfx_load("cd/asset/SFX/desert/orgue_4.wav");
  desert_sfx[8] = snd_sfx_load("cd/asset/SFX/desert/orgue_5.wav");
  desert_sfx[9] = snd_sfx_load("cd/asset/SFX/desert/orgue_6.wav");
  desert_sfx[10] = snd_sfx_load("cd/asset/SFX/desert/orgue_7.wav");
  desert_sfx[11] = snd_sfx_load("cd/asset/SFX/desert/orgue_8.wav");
  desert_sfx[12] = snd_sfx_load("cd/asset/SFX/desert/orgue_9.wav");
  desert_sfx[13] = snd_sfx_load("cd/asset/SFX/desert/orgue_1.wav");
  desert_sfx[14] = snd_sfx_load("cd/asset/SFX/desert/orgue_2.wav");
  desert_sfx[15] = snd_sfx_load("cd/asset/SFX/desert/orgue_2.wav");
  //desert_sfx[16] = snd_sfx_load("cd/asset/SFX/desert/orgue_13.wav");
  //desert_sfx[17] = snd_sfx_load("cd/asset/SFX/desert/bass_1.wav");
  //snd_sfx_play(desert_sfx, 128, 128);
  */

  game_state = EXPLORATION;
  p1.currentMap = MAP_DESERT;

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
  //sndoggvorbis_volume(f_vol);
  setFloat(3, f_vol);
  setParam(4, getPositionString());
}

int nDelay = 1000;
void wierdMusic(scene *self) {
  if (frameCount % nDelay == 0) {
    int r = getRand(4);
    int v = getRand(40) + 160;
    setInt(2, r);
    //snd_sfx_stop_all
    setInt(3, snd_sfx_play(desert_sfx[r], v, 128));
    nDelay = 125 + getRand(50);
  }
  //snd_sfx_play(desert_sfx, 128, 128);
}

void renderDesert(scene *self) {
}

void updateDesert(scene *self){
  //soundDistance(self);
  wierdMusic(self);
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
}
