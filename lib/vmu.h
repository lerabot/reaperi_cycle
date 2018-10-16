#ifndef __VMU_H__
#define __VMU_H__

#include "../header.h"
#include <kos.h>

typedef struct p_data {
  int pos[2];
  char map;

  //questProg[0] = questID | questProg[1] = status
  char questProg[QUEST_NUMBER][2];

  //figure out a way to do a binary encoding.
  char spiritState;

} player_data;

int VMU_loadVMU();

int VMU_saveGame();
int VMU_loadGame();

int VMU_packData(player_data p);
int VMU_unpackData(player_data p);


#endif