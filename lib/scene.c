#include <kos.h>
#include "game_object.h"
#include "scene.h"
#include "tilemap.h"
#include "../header.h"
#include "../global_var.h"
#include "../utils.h"
#include "gl_font.h"
#include "debug_screen.h"

gameObject spritesheet;

void initScene(scene *self) {
  self->name = "";
  self->bgm = "";
  self->floorTex = -1;
  self->activeNum = self->objNum = 0;
  self->renderScene = NULL;
  self->updateScene = NULL;
  self->freeScene = NULL;

  setMapInfo(self, 640, 480, 320, 240);
}

int loadMapData(scene *self, char* filename) {
  initScene(self);
  file_t file;

  if ((file = fs_open("/rd/spritesheet.dtex", O_RDONLY)) != -1){
    printf("Opening DTEX version\n");
    setParam(4, "Opened DTEX");
    fs_close(file);
    spritesheet = createObjectDTEX("/rd/spritesheet.dtex", -1000, -1000, 1);
  } else {
    printf("Opening PNG version\n");
    setParam(4, "Opened PNG");
    spritesheet = createObject("/rd/spritesheet.png", -1000, -1000, 1);
  }
  char *path = "";
  int r = 0;
  path = filename;
  //get general map info - SIZE / OBJNUM / name
  lua_getglobal(t_data, "loadXML");
  lua_pushstring(t_data, filename);
  lua_pcall(t_data, 1, 1, 0);
  r = lua_tonumber(t_data, 1);
  lua_settop(t_data, 0);
  /*
  if(r == 0) {
    printf(".SVG not loaded\n");
    setParam(2, ".SVG not loaded");
    return(0);
  }
  */

  //get the data
  lua_getglobal(t_data, "getMapInfo");
  lua_pcall(t_data, 0, 3, 0); //x_map, y_map, obj_num
  self->mapSize[0] = (int)lua_tonumber(t_data, 1);
  self->mapSize[1] = (int)lua_tonumber(t_data, 2);
  self->objNum = lua_tonumber(t_data, 3);
  lua_settop(t_data, 0);


  //loading the json spritesheet data
  lua_getglobal(t_data, "loadJSON");
  lua_pushstring(t_data, "/rd/spritesheet.json");
  lua_pcall(t_data, 1, 1, 0);
  r = lua_tonumber(t_data, 1);
  lua_settop(t_data, 0);
  if(r == 0) {
    printf(".JSON not loaded\n");
    setParam(2, ".JSON not loaded");
    return(0);
  }
  setParam(2, ".SVG & .JSON loaded");


  float depth = 0;
  self->obj = malloc(sizeof(gameObject) * self->objNum);
  self->activeNum = 0;
  for (int i = 0; i < self->objNum; i++) {
    lua_getglobal(t_data, "createObject");
    lua_pushnumber(t_data, i+1); // +1 = lua offset
    lua_pcall(t_data, 1, 10, 0);
    self->obj[i] =          createObject("", 0, 0, 1);
    self->obj[i].t =        spritesheet.t;
    self->obj[i].x =        lua_tonumber(t_data, 1);
    self->obj[i].y =        lua_tonumber(t_data, 2);
    self->obj[i].z =        depth -= 0.5;
    self->obj[i].t.u =      lua_tonumber(t_data, 3);
    self->obj[i].t.v =      lua_tonumber(t_data, 4);
    self->obj[i].t.uSize =  lua_tonumber(t_data, 5);
    self->obj[i].t.vSize =  lua_tonumber(t_data, 6);
    self->obj[i].t.xScale = lua_tonumber(t_data, 7);
    self->obj[i].desc =     lua_tostring(t_data, 8);
    self->obj[i].name =     lua_tostring(t_data, 9);
    self->obj[i].npcID =    lua_tostring(t_data, 10);

    if (strlen(self->obj[i].npcID) > 2)
      self->activeNum++;

    lua_settop(t_data, 0);
  }
  printf("Scene.c > Loaded %i gameObject\n", self->objNum);

  //assinging  obj > activeObj
  self->activeObj = malloc(sizeof(gameObject*) * self->activeNum);
  int j = 0;
  for (int i = 0; i < self->objNum; i++) {
    if (strlen(self->obj[i].npcID) > 2) {
      self->activeObj[j++] = &self->obj[i];
    }
  }
  printf("Scene.c > Loaded %i activeObject\n", self->activeNum);

  char *file_rd = "/rd/sprite.json";
  file_t f = fs_open(file_rd, O_RDONLY);
  printf("Scene.c > Handles opened %i\n", f);
  if(f != -1) {
    fs_close(f);
  }
  return(1);
}

void setMapInfo(scene *s, int x, int y, int xStart, int yStart){
  s->mapSize[0] = x;
  s->mapSize[1] = y;
  setPosition(xStart, yStart);
}

void updateScene(scene *self) {

  char  png[32];
  if (self->activeNum > 0 && game_state == EXPLORATION) {
    for(int i = 0; i < self->activeNum; i++) {
      //CLICKED//////////////////////////////////////
      if(clicked(self->activeObj[i], CONT_A)) {
        sprintf(png, "/rd/%s.png", self->activeObj[i]->npcID);
        activateNPC(self->activeObj[i]->npcID, png);
        break;
      }
    }
  }
  self->updateScene(self);
}

gameObject* findObject(scene *self, char* npcID) {
  for(int i = 0; i < self->activeNum; i++) {
    if(strcmp(self->activeObj[i]->npcID, npcID) == 0)
      return(self->activeObj[i]);
  }
  return(NULL);
}

void renderScene(scene *self){
  int renderDistance = 750;
  glLoadIdentity();
  glPushMatrix();
  glTranslated(displayPos[0], displayPos[1], displayPos[2]);
  if (self != NULL)
  {
    if(render_map == 1) {
      if (self->floorTex != -1)
        drawMap(&self->obj[self->floorTex].t, self->mapSize[0]/2, self->mapSize[1]/2);
      drawShadow();
      for (int i = 0; i < self->objNum; i++){
        if(distance(p1.obj.x, p1.obj.y, self->obj[i].x, self->obj[i].y) < renderDistance)
          drawObject(&self->obj[i]);
      }
    }
    self->renderScene(self);
  }
  glPopMatrix();
}

void freeSpritesheet() {
  glDeleteTextures(1, &spritesheet.t.id);
}

void checkFile(char* filename) {
  char file_rd[100];
  char file_pc[100];

  sprintf(file_rd, "/rd/%s", filename);
  file_t f = fs_open(file_rd, O_RDONLY);
  printf("Opening %s : result %i\n", file_rd, f);
  if(f != -1) {
    fs_close(f);
  }

  sprintf(file_pc, "/pc/asset/map_hideout/%s", filename);
  f = fs_open(file_pc, O_RDONLY);
  printf("Opening %s : result %i\n", file_pc, f);
  if(f != -1) {
    fs_close(f);
  }

  lua_getglobal(t_data, "checkFile");
  lua_pushstring(t_data, file_rd);
  lua_pcall(t_data, 1, 0, 0);
  lua_settop(t_data, 0);

  lua_getglobal(t_data, "checkFile");
  lua_pushstring(t_data, file_pc);
  lua_pcall(t_data, 1, 0, 0);
  lua_settop(t_data, 0);
}
