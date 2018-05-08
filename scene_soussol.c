#include <kos.h>
#include <stdlib.h>
#include "scene_soussol.h"
#include "header.h"

#include "asset/map_soussol/mapdata.c"
#define TORCHE_NUM 7

int tableau[3] = {99, 100, 101};
int tableau_state[3] = {0, 0, 0};
gameObject *torche;
float noise[TORCHE_NUM];

gameObject sprite;

void testJsonMap(scene *self) {
  //loadLuaFile(t_data, "/rd/json.lua");
  loadLuaFile(t_data, "/rd/loadMap.lua");

  setMapInfo(self, 1000, 1000, 320, 240);
  sprite = createObject("/rd/spitesheet_info.png", -1000, -1000, 1);

  //get general map info - SIZE / OBJNUM / name
  lua_getglobal(t_data, "loadXML");
  lua_pushstring(t_data, "/rd/map_soussol_v3.svg");
  lua_pcall(t_data, 1, 1, 0);
  char *buf = lua_tostring(t_data, -1);
  setParam(3, buf);

  //get the data
  lua_settop(t_data, 0);
  lua_getglobal(t_data, "getMapInfo");
  lua_pcall(t_data, 0, 3, 0); //x_map, y_map, obj_num
  self->mapSize[0] = lua_tonumber(t_data, 1);
  self->mapSize[1] = lua_tonumber(t_data, 2);
  self->objNum = lua_tonumber(t_data, 3);
  lua_settop(t_data, 0);

  //loading the json spritesheet data
  lua_getglobal(t_data, "loadJSON");
  lua_pushstring(t_data, "/rd/spitesheet_info.json");
  lua_pcall(t_data, 1, 1, 0);
  lua_settop(t_data, 0);

  int flipped = 0;
  self->obj = malloc(sizeof(gameObject) * self->objNum);
  for (int i = 0; i < self->objNum; i++) {
    lua_getglobal(t_data, "createObject");
    lua_pushnumber(t_data, i);
    lua_pcall(t_data, 1, 9, 0);
    self->obj[i] = createObject("", 0, 0, 1);
    self->obj[i].t = sprite.t;
    self->obj[i].x =        lua_tonumber(t_data, 1);
    self->obj[i].y =        lua_tonumber(t_data, 2);
    //self->obj[i].t.w =      lua_tonumber(t_data, 3);
    //self->obj[i].t.h =      lua_tonumber(t_data, 4);
    self->obj[i].t.u =      lua_tonumber(t_data, 5);
    self->obj[i].t.v =      lua_tonumber(t_data, 6);
    self->obj[i].t.uSize =  lua_tonumber(t_data, 7);
    self->obj[i].t.vSize =  lua_tonumber(t_data, 8);
    self->obj[i].t.xScale = lua_tonumber(t_data, 9);
    if (lua_tonumber(t_data, 9) < 0)
      flipped++;
    lua_settop(t_data, 0);
  }
  setInt(0, flipped);
}

void loadSoussol(scene* self) {
  mount_romdisk("asset/rd_soussol.img.gz", "/rd");
  //loadSoussolData(self);

  //load map via JSON+XML
  testJsonMap(self);

  //for (int i = 0; i < self->objNum; i++)
    //self->obj[i].t.light = 0;
  generateFloor(self, 0);

  torche = malloc(sizeof(gameObject) * TORCHE_NUM);
  torche[0] = createObject("/rd/flare.png", 450, 400, 1);
  torche[0].emitLight = 0.7;

  torche[1] = createObject("/rd/lantern_anim.png", 603, 562, 1);
  setUV(&torche[1].t, 0.125, 1);
  setAnim(&torche[1].t, 0);
  torche[1].emitLight = 0;
  setLight(&torche[1].t, 2);
  torche[2] = torche[1]; moveObject(&torche[2], 430, 1043);
  torche[3] = torche[1]; moveObject(&torche[3], 961, 1180);
  torche[4] = torche[1]; moveObject(&torche[4], 1500, 1358);
  torche[5] = torche[1]; moveObject(&torche[5], 1183, 1815);
  torche[6] = torche[1]; moveObject(&torche[6], 444, 1571);

  for(int i = 0; i < TORCHE_NUM; i++)
    noise[i] = 0;

  //music--
  //self->bgm = "/cd/music/soussol.ogg";
  //sndoggvorbis_start(self->bgm, 1);


  self->updateScene = updateSoussol;
  self->freeScene = freeSoussol;
}



void updateEnigme(scene *self) {
  //char *buf = "";
  //snprintf(buf, 16, "x-%d y-%d", (int)p1.obj.x, (int)p1.obj.y);
  //setParam(3, buf);

  //add torche to items
  if(clicked(&torche[0], CONT_A))
    addItem(&torche[0], "/cd/asset/item/torche.png");

  if(p1.currentItem->emitLight > 0){
    for(int i = 0; i < TORCHE_NUM; i++) {
      if(over(&torche[i])) {
        torche[i].emitLight = p1.currentItem->emitLight;
      }
    }
  }
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

//void light(gameObject *lightSource)

void updateLight(scene *self) {
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
}

void updateSoussol(cont_state_t *state, scene *self){
  //updateLight(self);
  updateEnigme(self);

  drawObject(&sprite);

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

void freeSoussol(scene *self){

  glDeleteTextures(1, &torche[1].t.id);
  glDeleteTextures(1, &torche[0].t.id);

  int t[11] = {0, 1, 2, 7, 10, 11, 12, 56, 98, 99, 102};
  for (int i = 0; i < 11; i++){
      glDeleteTextures(1, &self->obj[t[i]].t.id);
  }

  free(torche);
  free(self->obj);

  sndoggvorbis_stop();
  fs_romdisk_unmount("/rd");
}
