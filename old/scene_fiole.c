#include <kos.h>
#include <kos/string.h>
#include <stdio.h>
#include "scene.h"
#include "game_object.h"
#include "scene_fiole.h"
#include "global_var.h"
#include "controller.h"
#include "glfont.h"
#include <arch/types.h>

#define GLOW 0
#define FIOLE 1
#define FIOLE_ALPHA 2
#define FGAUCHE 3
#define FDROITE 4
#define ACTIVATOR 5
#define TOP_BUTTON 6

#define SAT 0
#define EVE 1
#define DIO 2

int bg_index = 0;
int fiole_index[] = {4, 2, 6};
char status = 0;

void loadFiole(scene *s){
  s->name = "Fiole";
  s->status = "NEW";

  mount_romdisk("rd_fiole.img.gz", "/rom");
  //EXTRA TEX///////////////
  s->texNum = 3;
  s->tex = malloc(sizeof(texture) * s->texNum);
  png_to_gl_texture(&s->tex[0], "/rom/BG_sat.png");
  png_to_gl_texture(&s->tex[1], "/rom/BG_eve.png");
  png_to_gl_texture(&s->tex[2], "/rom/BG_dio.png");

  //BG//////////
  s->bg = malloc(sizeof(gameObject));
  s->bg[0] = createObject("", 320, 240, 1);

  //OBJECT//////////////
  //respecter l'ordre de dessin
  s->objNum = 9;
  s->obj = malloc(sizeof(gameObject) * s->objNum);
  s->obj[GLOW]  = createObject("/rom/fiole_anim_low.png", 315, 265, 1);
  setUVSprite(&s->obj[GLOW].t, 0,0, 0.25, 1);
  setScale(&s->obj[GLOW].t, 2);

  s->obj[FIOLE] = createObject("/rom/Fioles.png", 315, 265, 1);
  setUVSprite(&s->obj[FIOLE].t, 0, 0, 0.25, 0.5);

  s->obj[FIOLE_ALPHA] = createObject("", 315, 265, 1);
  s->obj[FIOLE_ALPHA].t = s->obj[FIOLE].t;
  setUVSprite(&s->obj[FIOLE_ALPHA].t, 0, 0, 0.25, 0.5);

  s->obj[FDROITE] = createObject("/rom/fleche_anim.png", 512+64, 240, 1); //fleche gauche
  setUVSprite(&s->obj[FDROITE].t, 0,0, 0.25, 1);

  s->obj[FGAUCHE] = createObject("", 64, 240, 1);
  s->obj[FGAUCHE].t = s->obj[FDROITE].t;
  setUVSprite(&s->obj[FGAUCHE].t, 0,0, 0.25, 1);
  flipU(&s->obj[FGAUCHE].t);

  s->obj[ACTIVATOR] = createObject("/rom/activator.png", 323, 99, 1); //fleche gauche
  setUVSprite(&s->obj[ACTIVATOR].t, 0,0, 0.5, 1);

  s->obj[TOP_BUTTON] = createObject("/rom/bouton.png", 320, 440, 0); //fleche gauche
  setUVSprite(&s->obj[TOP_BUTTON].t, 0, 1, 0.25, 0.5);
  setAnim(&s->obj[TOP_BUTTON].t, 4);
  s->obj[TOP_BUTTON].currentFrame = 4;

  s->obj[7] = createObject("/rom/overglow_saturne.png", 95+64, 370, 0); //fleche gauche
  setUVSprite(&s->obj[7].t, 2, 0, 0.25, 1);
  s->obj[8] = createObject("/rom/dragon.png", 64+430, 395, 0);

  //text
  s->texNum = loadText(&s->text, "/rom/indice.txt");

  //sound
  s->snd = malloc(sizeof(sfxhnd_t) * 1);
  s->snd[0] = snd_sfx_load("cd/sounds/chainmail1.wav");
  mp3_start("/pc/fiole/fractal.mp3", 0);

  s->updateScene = updateFiole;
}

void updateFiole(cont_state_t *state, scene *self){
  indexSwitcher(self);
  updateBouton(self);
  updateGlow(self);
  updateIndice(self);

  if (clicked(&self->obj[ACTIVATOR], CONT_A))
  {
    activator(self);
    snd_sfx_play(self->snd[0], 200, 128);
    setAnim(&self->obj[ACTIVATOR].t, 1);
  }
  else
    setAnim(&self->obj[ACTIVATOR].t, 0);

  if(buttonPressed(CONT_X))
  {
    freeFiole(self);
    loadFiole(self);
  }
}

void indexSwitcher(scene *self){
  ////////////////////////
  //BG
  if (clicked(&self->obj[FGAUCHE], CONT_A)){
    snd_sfx_play(self->snd[0], 200, 70);
    bg_index++;
  }


  if (clicked(&self->obj[FDROITE], CONT_A)){
    snd_sfx_play(self->snd[0], 200, 180);
    bg_index--;
  }

  if (bg_index > 2)
    bg_index = 0;
  if (bg_index < 0)
    bg_index = 2;

  self->bg->t = self->tex[bg_index];
  ///////////////////////
  //FIOLE

  self->obj[FIOLE_ALPHA].currentFrame = fiole_index[bg_index];

  if (clicked(&self->obj[FIOLE], CONT_A))
  {
    self->obj[FIOLE_ALPHA].currentFrame++;
    self->obj[FIOLE_ALPHA].t.a = 0;
  }

  if (self->obj[FIOLE_ALPHA].currentFrame > 6)
    self->obj[FIOLE_ALPHA].currentFrame = 0;

  if(self->obj[FIOLE_ALPHA].t.a < 1.0)
    self->obj[FIOLE_ALPHA].t.a += 0.1;
  else
  {
    setAnim(&self->obj[FIOLE].t, self->obj[FIOLE_ALPHA].currentFrame);
    self->obj[FIOLE_ALPHA].t.a = 0;

  }

  fiole_index[bg_index] = self->obj[FIOLE_ALPHA].currentFrame;
  setAnim(&self->obj[FIOLE_ALPHA].t, self->obj[FIOLE_ALPHA].currentFrame);

}

void updateGlow(scene *self){
  if (over(&self->obj[FIOLE]) && self->obj[GLOW].currentFrame < 3)
  {
    if(frameCount % 2 == 0)
      self->obj[GLOW].currentFrame++;
  }

  if(!over(&self->obj[FIOLE]) && self->obj[GLOW].currentFrame > 0){
    if(frameCount % 2 == 0)
      self->obj[GLOW].currentFrame--;
  }

  setAnim(&self->obj[GLOW].t, self->obj[GLOW].currentFrame);
}

void updateBouton(scene *self){

  //TOP BUTTON UPDATE
  if(status == 1 && self->obj[TOP_BUTTON].t.a < 0.99)
    self->obj[TOP_BUTTON].t.a += 0.005;

  if(clicked(&self->obj[TOP_BUTTON], CONT_A) && status == 1){
    freeFiole(self);
    temple_status = 1;
    loadTemple(self);
  }

  //FLECHE GAUCHE
  if (over(&self->obj[TOP_BUTTON]) && self->obj[TOP_BUTTON].currentFrame < 7)
  {
    if(frameCount % 2 == 0)
      self->obj[TOP_BUTTON].currentFrame++;
  }
  if(!over(&self->obj[TOP_BUTTON]) && self->obj[TOP_BUTTON].currentFrame > 4){
    if(frameCount % 2 == 0)
      self->obj[TOP_BUTTON].currentFrame--;
  }

  //FLECHE GAUCHE
  if (over(&self->obj[FGAUCHE]) && self->obj[FGAUCHE].currentFrame < 3)
  {
    if(frameCount % 2 == 0)
      self->obj[FGAUCHE].currentFrame++;
  }
  if(!over(&self->obj[FGAUCHE]) && self->obj[FGAUCHE].currentFrame > 0){
    if(frameCount % 2 == 0)
      self->obj[FGAUCHE].currentFrame--;
  }

  //FLECHE DROITE
  if (over(&self->obj[FDROITE]) && self->obj[FDROITE].currentFrame < 3)
  {
    if(frameCount % 2 == 0)
      self->obj[FDROITE].currentFrame++;
  }
  if(!over(&self->obj[FDROITE]) && self->obj[FDROITE].currentFrame > 0){
    if(frameCount % 2 == 0)
      self->obj[FDROITE].currentFrame--;
  }

  setAnim(&self->obj[TOP_BUTTON].t, self->obj[TOP_BUTTON].currentFrame);
  setAnim(&self->obj[FGAUCHE].t, self->obj[FGAUCHE].currentFrame);
  setAnim(&self->obj[FDROITE].t, self->obj[FDROITE].currentFrame);
}

void activator(scene *self){
  char _t = 0;
  char i = fiole_index[0];
  char j = fiole_index[1];
  char k = fiole_index[2];

  //MASCULIN
  if(i == 2 || i == 1)
    _t |= 1<<0;
  //FEMININ
  if(j == 5 || j == 0)
    _t |= 1<<1;
  //ANDROGINE
  if(k == 4 || k == 3)
    _t |= 1<<2;

  if (_t == 7)
    status = 1;

}

void updateIndice(scene *self){
  char* indice;

  //Dio + Oiseau
  if(fiole_index[DIO] == 4 && bg_index == DIO)
    indice = self->text[0];
  //else if(fiole_index[DIO] == 4 && bg_index == DIO) //peu claire
    //indice = self->text[1];
  else if(fiole_index[SAT] == 5 && bg_index == SAT)
    indice = self->text[2];
  else if(fiole_index[DIO] == 0 && bg_index == DIO)
    indice = self->text[3];
  else if(fiole_index[EVE] == 2 && bg_index == EVE)
    indice = self->text[4];
  else if(fiole_index[SAT] == 3 && bg_index == SAT)
    indice = self->text[5];
  else {
    resetText();
    indice = "";
  }

  writeFontDelay(indice, 32, 64, 4);

  if(fiole_index[SAT] == 5 && bg_index == SAT)
    setAlpha(&self->obj[7], 1);
  else
    setAlpha(&self->obj[7], 0);

  if(fiole_index[DIO] == 0 && bg_index == SAT)
    setAlpha(&self->obj[8], 1);
  else
    setAlpha(&self->obj[8], 0);
}

void freeFiole(scene *self){
  glDeleteTextures(1, &self->tex[0].id);
  glDeleteTextures(1, &self->tex[1].id);
  glDeleteTextures(1, &self->tex[2].id);
  //free(self->tex);

  glDeleteTextures(1, &self->obj[GLOW].t.id);
  glDeleteTextures(1, &self->obj[FIOLE].t.id);
  glDeleteTextures(1, &self->obj[FDROITE].t.id);
  glDeleteTextures(1, &self->obj[ACTIVATOR].t.id);
  glDeleteTextures(1, &self->obj[TOP_BUTTON].t.id);
  //free(self->obj);
  fs_romdisk_unmount("/rom");

  setParam(1, "Total memory:");
  setInt(1, pvr_mem_available());
}
