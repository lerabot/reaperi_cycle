#ifndef __SCENE_JARDIN_H__
#define __SCENE_JARDIN_H__

#include <kos.h>
#include "lib/scene.h"

void loadJardin(scene *s);
void freeJardin(scene *s);
void updateJardin(cont_state_t *state, scene *self);

#endif
