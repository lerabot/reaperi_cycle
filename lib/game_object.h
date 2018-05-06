#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "gl_png.h"
#include "lua.h"

typedef struct game_object {
  int     visible;
  int     size;
  int     frames, cFrame;
  int     active;
  char    *script;
  char    *name;
  float   x, y, angle;
  float   emitLight;
  texture t;
} gameObject;

gameObject  createObject(char *path, float x, float y, int visible);
gameObject  createObjectDTEX(char *path, float x, float y, int visible);
int         setScript(gameObject *object, lua_State *L, char *path);
int         activate(gameObject *object, lua_State *L);
void        moveObject(gameObject *object, float x, float y);
void        drawObject(gameObject *object);
void        executeLight(gameObject *object, gameObject *target);
void        setVisible(gameObject *object, int visible);
void        setAlpha(gameObject *object, float alpha);
void        nextFrame(gameObject *object, int delay);
int         mouseOver(gameObject *cursor, gameObject *target);
void        setTexture(gameObject *object, texture *t);

#endif
