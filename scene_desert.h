#ifndef __SCENE_DESERT_H__
#define __SCENE_DESERT_H__

#include <kos.h>
#include "lib/scene.h"

void loadDesert(scene *s);
void freeDesert(scene *s);
void updateDesert(cont_state_t *state, scene *self);

#endif
