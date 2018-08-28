#ifndef __LUA_BINDS_H__
#define __LUA_BINDS_H__

#include "lua.h"
#include "lualib.h"

void  LUA_initLua(); //sets up the luastate + load scrips
void  LUA_addQuest(int questID);
int   LUA_getQuest();
void  LUA_loadDialog(char *filename);
void  LUA_setQuest(char *quest, int questStatus);

char* LUA_getDialog(char *npc_name);
int   LUA_getClock();

int   loadLuaFile(lua_State *L_state, char *filename);
void  setLuaState(lua_State **L_state);

#endif