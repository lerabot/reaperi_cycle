#ifndef __SCENE_H__
#define __SCENE_H__

#include <kos.h>
#include "game_object.h"

typedef struct _scene
{
  char        *name;
  char        *status; //new, started, completed, ???

  //visual
  int         objNum, texNum; //count for tex and obj
  gameObject  *bg;
  gameObject  *obj;
  gameObject  *activeObj;
  int         *tex;
  int         floorTex;
  int         mapSize[2];
  int         startPoint[2];

  //sounds
  char        *bgm;
  sfxhnd_t    *snd; // sfx

  void (* updateGUI)(struct _scene *self);
  void (* updateScene)(cont_state_t *, struct _scene *self);
  void (* freeScene)(struct _scene *self);

} scene;


void  updateLoading();
scene loadLoading();
void  drawScene();
void  setMapInfo(scene *s, int x, int y, int xStart, int yStart);
scene loadScene(scene (*loader)());
void  freeScene2();
void  drawAllTex();

#endif
