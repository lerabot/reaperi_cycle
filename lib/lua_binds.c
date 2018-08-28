#include <string.h>
#include "../utils.h"
#include "../global_var.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

lua_State *t_data;
lua_State *L;

void        LUA_initLua() {
  setLuaState(&L); //player + game related
  setLuaState(&t_data); // refreses on each map?

  //scripts
  loadLuaFile(L,      findFile("/script/player.lua"));
  loadLuaFile(L,      findFile("/script/questlist.lua"));
  loadLuaFile(L,      findFile("/script/dialog.lua"));
  loadLuaFile(t_data, findFile("/script/loadMap.lua"));

  /*
  loadLuaFile(L,      "/cd/script/player.lua");
  loadLuaFile(L,      "/cd/script/questlist.lua");
  loadLuaFile(L,      "/cd/script/dialog.lua");
  loadLuaFile(t_data, "/cd/script/loadMap.lua");
  */
}

char*       LUA_getDialog(char *npc_name) {
  const char *buf = "";
  lua_getglobal(L, "setNPC");
  lua_pushstring(L, npc_name);
  lua_pcall(L, 1, 0, 0);
  lua_getglobal(L, "getDialog");
  lua_pcall(L, 0, 1, 0);
  buf = lua_tostring(L, -1);
  //setString(1, buf);
  lua_pop(L,1);
  return(buf);
}

int         LUA_getQuest() {
  const char* questName;

  lua_getglobal(L, "getQuest");
  lua_pcall(L, 0, 4, 0);
  p1.questName = lua_tostring(L, 1);
  p1.questDesc = lua_tostring(L, 2);
  p1.questID = lua_tonumber(L, 3);
  lua_settop(L, 0);
  return(1);
}

//update the player position
void        LUA_updatePlayer() {
  lua_getglobal(L, "updatePlayer");
  lua_pushnumber(L, p1.currentMap);
  lua_pushnumber(L, p1.obj.y);
  lua_pushnumber(L, p1.obj.x);
  lua_pcall(L, 3, 0, 0);
}

//get the quest data from lua.
void        LUA_addQuest(int questNum) {
  const char* questName;
  int questActive;
  lua_getglobal(L, "addQuest");
  lua_pushnumber(L, questNum);
  lua_pcall(L, 1, 3, 0);
  p1.questName = lua_tostring(L, 1);
  p1.questDesc = lua_tostring(L, 2);
  p1.questID = lua_tonumber(L, 3);
  lua_settop(L, 0);
}

//get the dialog data from lua.
void        LUA_loadDialog(char *filename) {
  lua_getglobal(L, "loadDialog");
  lua_pushstring(L, filename);
  lua_pcall(L, 1, 1, 0);
  //setParam(3, lua_tostring(L, -1));
  lua_settop(L, 0);
}

int        LUA_getClock() {
  int t = 0;
  lua_getglobal(L, "getTime");
  lua_pcall(L, 0, 1, 0);
  t = lua_tonumber(L, 1);
  lua_settop(L, 0);
  return t;
}

//loads a lua script
int loadLuaFile(lua_State *L_state, char *filename) {
  if(luaL_loadfile(L_state, filename) || lua_pcall(L_state, 0, 0, 0)) {
    //setParam(3, lua_tostring(L_state, -1));
    lua_tostring(L_state, -1);
    return(0);
  }
  return (1);
}

void setLuaState(lua_State **L_state) {
  *L_state = luaL_newstate();
  luaL_openlibs(*L_state);
  luaopen_io(*L_state);
}
