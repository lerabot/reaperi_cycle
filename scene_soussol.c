#include <kos.h>
#include <stdlib.h>
#include <string.h>
#include "scene_soussol.h"
#include "header.h"

#define TORCHE_NUM 7

int tableau[3] = {99, 100, 101};
int torche[3] = {99, 100, 101};
int tableau_state[3] = {0, 0, 0};

int symbole = 0;

gameObject sprite;

void loadSoussol(scene* self) {
  mount_romdisk("/asset/rd_soussol.img.gz", "/rd");
  //load map via JSON+XML
  loadMapData(self, "/rd/map_soussol.svg");

  //self->obj[0] = createObject("/rd/soussol_floor.png", -1000, -1000, 1);
  generateFloor(self, 0);


  //assing obj ID to items
  for (int i = 0; i < self->objNum; i++) {
    if(strcmp(self->obj[i].name, "symbole_oil.png"))
      symbole = i;
    //if(strcmp(self->obj[i].name, "lantern.png"))

  }



  //music--
  //self->bgm = "/cd/music/soussol.ogg";
  //sndoggvorbis_start(self->bgm, 1);

  game_state = EXPLORATION;

  self->updateScene   = updateSoussol;
  self->freeScene     = freeSoussol;
  self->renderScene   = renderSoussol;
}

void updateEnigme(scene *self) {
  //char *buf = "";
  //snprintf(buf, 16, "x-%d y-%d", (int)p1.obj.x, (int)p1.obj.y);
  //setParam(3, buf);

  //add torche to items
  //if(clicked(&torche[0], CONT_A))
    //addItem(&torche[0], "/cd/asset/item/torche.png");

  /*
  if(p1.currentItem->emitLight > 0){
    for(int i = 0; i < TORCHE_NUM; i++) {
      if(over(&torche[i])) {
        torche[i].emitLight = p1.currentItem->emitLight;
      }
    }
  }
  */

  //run script for the 3 tableau
  for (int i = 0; i < 3; i++) {
    //when clicked
    if(clicked(&self->obj[tableau[i]], CONT_A)){
      addItem(&self->obj[tableau[i]], "/cd/asset/item/tableau.png");
      setDialog("", "/rd/tableau_1.png");
      tableau_state[i] = 1;
      //setString(i, "Tableau SET!");
    }
    //fade item
    if(tableau_state[i] == 1)
      setAlpha(&self->obj[tableau[i]], self->obj[tableau[i]].t.a - 0.01);
  }

}

void updateLight(scene *self) {
  /*
  //clear the lights
  for (int i = 0; i < self->objNum; i++)
    setLight(&self->obj[i].t, 0);

  for (int i = 0; i < TORCHE_NUM; i++) {
    if(torche[i].emitLight < 0.1) {
      setLight(&torche[i].t, 0);
    }
    else {
      if(frameCount % 3 == 0)
        setAnim(&torche[i].t, (rand() % 6) + 1);
    }
    //else
      //setLight(&torche[i].t, 0.9);
  }

  //check if the current item emit light;
  if(p1.currentItem->emitLight != 0) {
    for (int i = 0; i < self->objNum; i++) {
      executeLight(p1.currentItem, &self->obj[i]);
      if (i > 0 && i < TORCHE_NUM)
        executeLight(p1.currentItem, &torche[i]);
    }
  }

  //run throught all the lights
  for (int j = 0; j < TORCHE_NUM; j++) {
    drawObject(&torche[j]);

    //add some lil noise
    if(frameCount % ((rand() % 8) + 3) == 0)
      noise[j] = (rand() % 5) / 20.0;

    //run through all the object.
    if(torche[j].active == 1) {
      for (int i = 0; i < self->objNum; i++) {
        executeLight(&torche[j], &self->obj[i]);
      }
    }
  }
  */
}

void updateSoussol(scene *self){
  for(int i = 0; i < self->objNum; i++) {
    if(clicked(&self->obj[i], CONT_A))
      if(strlen(self->obj[i].desc) > 1) {
        setDialog(self->obj[i].desc, "");
        setString(3, "Dialog on item!");
      }
  }

  //TEMPLE
  if(over(&self->obj[102])){
    writeFont("Vers le temple", p1.obj.x + 16, p1.obj.y - 16);
    if(buttonPressed(CONT_A)) {
      freeSoussol(self);
      loadTemple(tempScene);
      setPosition(302, 404);
    }
  }
}

void renderSoussol(scene *self){
  glPushMatrix();
  glTranslated((int)displayPos[0], (int)displayPos[1], displayPos[2]);
  if (self != NULL)
  {
    if (self->floorTex != -1)
      drawMap(&self->obj[self->floorTex].t, self->mapSize[0]/2, self->mapSize[1]/2);

    for (int i = 0; i < self->objNum; i++){
      drawObject(&self->obj[i]);
    }

    //updateLight(self);
    //updateEnigme(self);
  }
  glPopMatrix();
}

void freeSoussol(scene *self){

  //glDeleteTextures(1, &torche[1].t.id);
  //glDeleteTextures(1, &torche[0].t.id);

  int t[11] = {0, 1, 2, 7, 10, 11, 12, 56, 98, 99, 102};
  for (int i = 0; i < 11; i++){
      glDeleteTextures(1, &self->obj[t[i]].t.id);
  }

  free(torche);
  free(self->obj);

  sndoggvorbis_stop();
  fs_romdisk_unmount("/rd");
}
