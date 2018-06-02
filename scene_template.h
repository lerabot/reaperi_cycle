#ifndef __SCENE_TEMPLATE_H__
#define __SCENE_TEMPLATE_H__

#include <kos.h>
#include "lib/scene.h"

void loadTemplate    (scene *self);
void updateTemplate  (cont_state_t *state, scene *self);
void renderTemplate  (scene *self);
void freeTemplate    (scene *self);

#endif
