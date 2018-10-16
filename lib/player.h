#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "game_object.h"

#define MAX_ITEM 8

/* controller handle the maple data but also the "cursor" in game*/
typedef struct _player
{
  int             visible;
  int             currentMap;
  int             inventorySize;
  float           cSpeed;     //speed of cursor

  char            questDesc[256];  //quest description
  char            questName[128];  //quest title in quest list
  int             questID;    //int define in header

  maple_device_t  *cont;      //controller adress
  cont_state_t    *state;     //current state
  cont_state_t     pstate;    //next state

  gameObject      obj;        //visual
  gameObject      *currentItem;
  gameObject      *inventory;
} player;

player  initPlayer(int playerNum);
void    updateController();
void    updatePlayer();
void    updateInventory();

void  updateItem();
void  displayInventory();
void  addItem(gameObject *target, char *path);
void  setItem(gameObject *target);
void  switchItem();
void  dropItem();
int   hasItem();
int   getInventorySize();

int   clicked(gameObject *target, uint16 key);
int   pressed(gameObject *target, uint16 key);
int   buttonPressed(uint16 key);
int   over(gameObject *target);
int   grab(gameObject *target);

int   inScreen(int x, int y);
void  drawCursor();
void  drawShadow();
void  hideController();
void  showController();
void  setPosition(int x, int y);
char* getPositionString();

#endif
