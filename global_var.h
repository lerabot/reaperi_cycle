#ifndef __GLOBAL_VAR_H__
#define __GLOBAL_VAR_H__

#include "lib/player.h"
#include "lib/scene.h"
#include "lua.h"

//Game States
#define EXPLORATION 1
#define MENU 4
#define DIALOG 2
#define INVENTORY 3

extern lua_State    *L;               //game data
extern lua_State    *t_data;          //texture data
extern player       p1;               //player data
extern scene        *currentScene;    //...
extern scene        *tempScene;       //... to load shit
extern float        displayPos[3];    //glTranslate vector
extern long         frameCount;       //number of Frame
extern int          game_state;       //general state machine for controller

#endif
