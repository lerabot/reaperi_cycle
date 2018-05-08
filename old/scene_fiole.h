#ifndef __SCENE_FIOLE_H__
#define __SCENE_FIOLE_H__

#include <kos.h>
#include "scene.h"

void drawSceneFiole();
void loadFiole(scene *self);
void updateFiole(cont_state_t *state, scene *self);
void indexSwitcher(scene *self); //genre les différent tableau
void updateBouton(scene *self);
void updateGlow(scene *self);
void activator(scene *self);
void freeFiole(scene *self);

#endif
