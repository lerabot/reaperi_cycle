#ifndef __UTILS_H__
#define __UTILS_H__

#include "lua.h"

char*   findFile(char* filename);
int     mount_romdisk(char *filename, char *mountpoint);
int     mount_gz_romdisk(char *filename, char *mountpoint);
int     loadFile(char *filename);
int     loadLuaFile(lua_State *L, char *filename);
void    setLuaState(lua_State **L);
void    initGL();
void    basicLight();
void    renderMenu();
int     getTime();
int     getRand(int modulo);
float   getFrameTime();
uint64_t getTime_MS();
void    quitGame();
void    limitScreen(int width, int height);
void    quitGame();

//MATH//////////////
double distance(float x1,float y1,float x2,float y2);

//CYCLE/////////////
void loadCycle();
void renderCycle();

#endif
