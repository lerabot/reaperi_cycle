#include <kos.h>
#include <kos/string.h>
#include <stdio.h>
#include "scene.h"
#include "game_object.h"
#include "scene_intro.h"
#include "global_var.h"
#include "controller.h"
#include "scene_fiole.h"

#define BG 0
#define PHENIX 1
#define TEXT 2

#define TEXTS_NUM 2

int keyframes[] = {150, 250, 700, 800, 850, 950, 1050, 1300, 1600, 1650};
int key2[] = {150, 250, 700, 800, 850, 950, 1050, 1300, 1600, 1650};
int currentText = 0;

void loadIntro(scene *s){
  s->name = "Intro";

  mount_romdisk("rd_intro.img.gz", "/rom");
  //BG
  s->texNum = 4;
  s->tex = malloc(sizeof(texture) * s->texNum);
  png_to_gl_texture(s->tex, "/rom/intro_bg1.png");
  png_to_gl_texture(s->tex+1, "/rom/intro_bg2.png");
  png_to_gl_texture(s->tex+2, "/rom/intro_1.png");
  png_to_gl_texture(s->tex+3, "/rom/intro_2.png");

  //OBJ
  s->objNum = 3;
  s->obj = malloc(sizeof(gameObject) * s->objNum);
  s->obj[BG] = createObject("", 320, 240, 0);
  s->obj[BG].t = s->tex[0];
  s->obj[BG].t.a = 0;

  s->obj[PHENIX] = createObject("/rom/pheonix.png", 320, 240, 0);
  setUVSprite(&s->obj[PHENIX].t, 0, 0, 0.25, 1);

  s->obj[TEXT] = createObject("", 320, 240, 0);
  s->obj[TEXT].t = s->tex[2];
  s->obj[TEXT].t.a = 0;

  setAlpha(&cursor.obj, 0);
  s->updateScene = newIntro;
}

void newIntro(cont_state_t *state, scene *self){
  if (frameCount % 6 == 0)
  {
    //fade bg
    if(frameCount < keyframes[0] && frameCount < keyframes[1] && self->obj[BG].t.a < 1)
      self->obj[BG].t.a += 0.02;

    //fade text 1
    if(frameCount > keyframes[1] && frameCount < keyframes[2] && self->obj[TEXT].t.a < 1)
      self->obj[TEXT].t.a += 0.05;

    //fade oiseau
    if(frameCount > keyframes[2] && frameCount < keyframes[3] && self->obj[PHENIX].t.a < 1)
      self->obj[PHENIX].t.a += 0.1;

    //killbg / oiseau gold
    if(frameCount > keyframes[3] && frameCount < keyframes[4])
    {
      self->obj[BG].t.a = 0;
      setAnim(&self->obj[PHENIX].t, 2);
      self->obj[TEXT].t.a = 0;
    }

    //switch oiseau
    if(frameCount > keyframes[4] && frameCount < keyframes[5] && self->obj[PHENIX].t.a > 0.1)
    {
      self->obj[PHENIX].t.a -= 0.05;
      self->obj[BG].t = self->tex[1];
      self->obj[BG].t.a = 0;
    }

    //fade second BG
    if(frameCount > keyframes[5] && frameCount < keyframes[6] && self->obj[BG].t.a < 1)
    {
      self->obj[PHENIX].t.a = 0;
      self->obj[BG].t.a += 0.05;
      self->obj[TEXT].t = self->tex[3];
      self->obj[TEXT].t.a = 0;
    }

    //fade in le text
    if(frameCount > keyframes[6] && frameCount < keyframes[7] && self->obj[TEXT].t.a < 1)
      self->obj[TEXT].t.a += 0.05;

    //fade out both item
    if(frameCount > keyframes[7] && frameCount < keyframes[8])
      {
        self->obj[BG].t.a -= 0.02;
        self->obj[TEXT].t.a -= 0.02;
      }

    //laod next scene
    if(frameCount > keyframes[8] && frameCount < keyframes[9])
      {
        self->obj[BG].t.a = 0;
        freeIntro(self);
        //frameCount = 500;
        loadFiole(self); // CHECK LE FREEING BUDDY
        cursor.obj.t.a = 1;
      }

  }

}

void freeIntro(scene *self){
  glDeleteTextures(1, &self->tex[0].id);
  glDeleteTextures(1, &self->tex[1].id);
  glDeleteTextures(1, &self->tex[2].id);
  glDeleteTextures(1, &self->tex[3].id);

  //glDeleteTextures(1, &self->obj[BG].t.id); //NO TEXTURE
  glDeleteTextures(1, &self->obj[PHENIX].t.id);
  //glDeleteTextures(1, &self->obj[TEXT].t.id); // NO TEXTURE
  fs_romdisk_unmount("/rom");

  setParam(1, "Total memory:");
  setInt(1, pvr_mem_available());
}
