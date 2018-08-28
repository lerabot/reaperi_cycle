#ifndef __SCENE_H__
#define __SCENE_H__

#include <kos.h>
#include "game_object.h"

typedef struct _scene
{
  char        *name;
  char        *status; //new, started, completed, ???

  //visual
  int         objNum, texNum, activeNum; //count for tex and obj
  gameObject  *bg;
  gameObject  *obj;
  gameObject  **activeObj;
  int         *tex;
  int         floorTex;
  int         mapSize[2];
  int         startPoint[2];

  //sounds
  char        *bgm;
  sfxhnd_t    *snd; // sfx

  void (* renderScene)(struct _scene *self);
  void (* updateScene)(struct _scene *self);
  void (* freeScene)(struct _scene *self);

} scene;

void  loadMapData(scene *self, char* filename);
void  setMapInfo(scene *s, int x, int y, int xStart, int yStart);
void  renderScene(scene *self);
void  updateScene(scene *self);
void  updateActiveObj(scene *self);
void  freeSpritesheet();

#endif
