#ifndef __SCENE_SOUSSOL_H__
#define __SCENE_SOUSSOL_H__

#include <kos.h>
#include "lib/scene.h"

void loadSoussol   (scene *self);
void updateSoussol (cont_state_t *state, scene *self);
void freeSoussol   (scene *self);

#endif
