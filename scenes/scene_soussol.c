#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "lua_binds.h"
#include "scene_soussol.h"
#include "scene.h"
#include "../global_var.h"
#include "../header.h"

#define TORCHE_NUM 11
#define TABLEAU_NUM 3

texture torche_tex;
texture flame;
gameObject *torche[TORCHE_NUM];
int torche_active[TORCHE_NUM] = {0};

gameObject *tab[TABLEAU_NUM];
int tableau_state[TABLEAU_NUM] = {0};

gameObject *descObj[20];
int desc_num = 0;

gameObject *npcObj[5];
int npc_num = 0;

int symbole = 0;

GLfloat l1_pos[] = {320.0, 240.0, 5.0, 1.0};
GLfloat l1_diff[] = {0.6, 0.5, 0.33, 0.1};
GLfloat l1_amb[] = {0.05, 0.05, 0.05, 0.1};

void loadSoussol(scene* self) {
  mount_romdisk("/asset/rd_soussol.img", "/rd");
  //load map via JSON+XML
  loadMapData(self, "/rd/map_soussol.svg");
  //generateFloor(self, -1);


  self->obj[0] = createObject("/rd/floor.png", -1000, -1000, 1);
  setScale(&self->obj[0].t, 2);
  generateFloor(self, 0);

  png_to_gl_texture(&torche_tex, "/rd/lantern_anim.png");
  setUV(&torche_tex, 0.125, 1);
  setAnim(&torche_tex, 0);

  png_to_gl_texture(&flame, "/rd/fire.png");
  setUV(&flame, 0.25, 1);
  setScale(&flame, 0.5);
  setAnim(&flame, 0);
  flame.a = 0;


  int l = 0;
  int t = 0;
  //assing obj ID to items
  for (int i = 0; i < self->objNum; i++) {
    if (strcmp(self->obj[i].name, "tableau_2.png") == 0)
      tab[t++] = &self->obj[i];
    if (strcmp(self->obj[i].name, "lantern.png") == 0) {
      torche[l++] = &self->obj[i];
      self->obj[i].t = torche_tex;
    }
    if (strcmp(self->obj[i].name, "barrel_2.png") == 0) {
      torche[l++] = &self->obj[i];
    }
    if (strlen(self->obj[i].desc) > 2) {
      descObj[desc_num++] = &self->obj[i];
    }
    if (strlen(self->obj[i].npcID) > 2) {
      npcObj[npc_num++] = &self->obj[i];
    }
  }

  //light related
  glDisable(GL_LIGHT0);
  glLightfv(GL_LIGHT1, GL_AMBIENT,  l1_amb);
  glLightfv(GL_LIGHT1, GL_DIFFUSE,  l1_diff);
  glLightfv(GL_LIGHT1, GL_POSITION, l1_pos);
  glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, 3.0);
  glEnable(GL_LIGHT1);


  //music--
  char *music_path = "";
  music_path = findFile("/asset/music/soussol.ogg");
  sndoggvorbis_start(music_path, 1);
  sndoggvorbis_volume(255);

  p1.currentMap = MAP_SOUSSOL;

  LUA_loadDialog("/rd/soussol_dialog.json");
  LUA_addQuest(2);

  //game_state = EXPLORATION;
  self->updateScene   = updateSoussol;
  self->freeScene     = freeSoussol;
  self->renderScene   = renderSoussol;
}

void updateEnigme(scene *self) {

  // torches
  for(int i = 0; i < TORCHE_NUM; i++) {
    if(over(torche[i])) {
      torche_active[i] = 1;
      torche[i]->t.a = 1.0f;
    }
  }

  //run script for the 3 tableau
  for (int i = 0; i < 3; i++) {
    //when clicked
    if(clicked(tab[i], CONT_A)){
      addItem(tab[i], "/cd/asset/item/tableau.png");
      //setDialog("", "/cd/asset/portrait/tableau_1_512.png");
      tableau_state[i] = 1;
    }
    //fade item
    if(tableau_state[i] == 1)
      setAlpha(tab[i], tab[i]->t.a - 0.01);
  }

}

void updateSoussol(scene *self){
  updateEnigme(self);
  //updateDesc(self);

  GLfloat pos[] = {p1.obj.x, p1.obj.y, 100, 1.0f};

  glLoadIdentity();
  glPushMatrix();
  glTranslated((int)displayPos[0], (int)displayPos[1], (int)displayPos[2]);
  glEnable(GL_LIGHTING);
  glLightfv(GL_LIGHT1, GL_POSITION, pos);
  glPopMatrix();

  /*
  for(int i = 0; i < 4; i++) {
    if(torche_active[i] == 1) {
      GLfloat pos[] = {torche[i]->x, torche[i]->y, 75.0f, 1.0f};
      glEnable(GL_LIGHT1  + i);
      glLightfv(GL_LIGHT1 + i, GL_POSITION, pos);
      //glLightfv(GL_LIGHT1 + i, GL_AMBIENT, l1_amb);
      glLightfv(GL_LIGHT1 + i, GL_DIFFUSE, l1_diff);
    }
  }
  */


  /*
  //TEMPLE
  if(over(&self->obj[102])){
    writeFont("Vers le temple", p1.obj.x + 16, p1.obj.y - 16);
    if(buttonPressed(CONT_A)) {
      freeSoussol(self);
      loadTemple(tempScene);
      setPosition(302, 404);
    }
  }
  */
}

void renderSoussol(scene *self){

  srand(time(NULL));

  //torches
  for(int i = 0; i < TORCHE_NUM; i++) {
    if(torche_active[i] == 1) {
      if (strcmp(torche[i]->name, "lantern.png") == 0)
        setAnim(&torche[i]->t, (frameCount % 6) + 1);
      else {
        setAnim(&flame, (frameCount % 3));
        draw_textured_quad(&flame, torche[i]->x, torche[i]->y + 30, torche[i]->z + 1);
      }
    }
  }
}

void freeSoussol(scene *self){

  freeSpritesheet();
  glDeleteTextures(1, &torche_tex.id);
  glDeleteTextures(1, &flame.id);

  //free(torche);
  //free(tab);
  //free(descObj);
  free(self->obj);

  //sndoggvorbis_stop();
  fs_romdisk_unmount("/rd");
}
