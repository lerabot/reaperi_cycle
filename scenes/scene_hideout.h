#ifndef __SCENE_HIDEOUT_H__
#define __SCENE_HIDEOUT_H__

#include <kos.h>
#include "scene.h"

int   checkCombination();
void  drawGlyphs(scene *self);
void  updateSides(int i);
void  resetEnigme();
void  enigmeHideout(scene *self);
void  updateLights(scene *self);

void loadHideout    (scene *self);
void updateHideout  (scene *self);
void renderHideout  (scene *self);
void freeHideout    (scene *self);

#endif
