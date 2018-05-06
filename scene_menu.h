#ifndef __SCENE_MENU_H__
#define __SCENE_MENU_H__

#include <kos.h>
#include "lib/scene.h"

void loadMenu(scene *s);
void freeMenu(scene *s);
void updateMenu(cont_state_t *state, scene *self);

#endif
