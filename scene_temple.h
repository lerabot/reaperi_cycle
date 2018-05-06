#ifndef __SCENE_TEMPLE_H__
#define __SCENE_TEMPLE_H__

#include <kos.h>
#include "lib/scene.h"

void loadTemple   (scene *self);
void updateGUI    (scene*self);
void updateTemple (cont_state_t *state, scene *self);
void freeTemple   (scene *self);
void resetTemple  (scene *self, int status);
void toTableau    (scene *self);

void introTemple  (scene *self);
void fioleAnim    (scene *self);

#endif
