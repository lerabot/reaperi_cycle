#ifndef __GLOBAL_VAR_H__
#define __GLOBAL_VAR_H__

#include "lib/player.h"
#include "lib/scene.h"
#include "lua.h"

extern lua_State    *L;               //game data
extern lua_State    *t_data;          //texture data
extern uint64       e_time, s_time;   //time stuff
extern player       p1;               //player data
extern scene        *currentScene;    //...
extern scene        *tempScene;       //... to load shit
extern float        displayPos[3];    //glTranslate vector
extern long         frameCount;       //number of Frame
extern int          game_state;       //general state machine for controller
extern int          render_map;       //render the map/environnement
extern char         *loadPath;        ///cd or /pc

#endif
