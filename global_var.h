#ifndef __GLOBAL_VAR_H__
#define __GLOBAL_VAR_H__

#include "lib/player.h"
#include "lib/scene.h"
#include "lua.h"

extern lua_State    *L; //game data
extern lua_State    *t_data; //texture data
extern player       p1;
extern scene        *currentScene;
extern scene        *tempScene;
extern float        displayPos[3];
extern long         frameCount;

#endif
