#include <kos.h>
#include "quest.h"
#include "../global_var.h"
#include "../header.h"
#include "../utils.h"

texture   questBox;
sfxhnd_t  questSound;
int       lastQuest = 0;
int       currentQuest = 0;
int       displayTime = 0;
int       displayDelay = 60 * 4.5;
int       questVolume = 0;
float     fontAlpha = 1.0;

void     initQuest() {
  LUA_loadQuestData("/cd/script/quest_data.json");
  //LUA_loadQuestData(findFile("/script/quest_data.json"));
  png_to_gl_texture(&questBox, "/rd/box_small_raw.png");
  questSound = snd_sfx_load("/rd/pluck_2.wav");
  questVolume = 185;
}

int updateQuest(int questNumber) {
  //LUA_addQuest(questNumber);
  snd_sfx_play(questSound, questVolume, 128);
  questBox.w = (strlen(p1.questDesc) * getCellSize() + 50);
  questBox.h = getCellSize() * 5;
  displayTime = frameCount + (60 * 4.5);
  fontAlpha = 0.85;
  return(1);
}

int     title_anim = 0;
int     desc_anim = 0;
int     questInfoActive;

void    renderQuest(){
  float cellSize = 10;

  if (game_state == EXPLORATION && questDescIsValid()) {
    if(frameCount > displayTime && fontAlpha > 0.02)
      fontAlpha -= 0.02;

    setFontAlpha(fontAlpha);
    fontColor(0.9, 0.85, 0.5);

    char *questUpdate = "Quest updated";
    writeFont(questUpdate, 320 - ((strlen(questUpdate) * cellSize) / 2.0f) + title_anim, 430);
    resetFontColor();
    writeFont(p1.questDesc, 320 - ((strlen(p1.questDesc) * cellSize) / 2.0f) + desc_anim, 410);
    resetFontScale();
    resetFontColor();
    setFontAlpha(1.0);
  }

  //QUEST INFO SHOULD BE IN CENTER
  if (game_state == MENU) {

    fontColor(0.9, 0.85, 0.5);
    char questInfo[200];
    sprintf(questInfo, "Current Quest");
    writeFont(questInfo, 320 - ((strlen(questInfo) * cellSize) / 2.0f) + title_anim, 430);
    resetFontColor();
    writeFont(p1.questDesc, 320 - ((strlen(p1.questDesc) * cellSize) / 2.0f) + desc_anim, 410);
    resetFontScale();
    resetFontColor();
    setFontAlpha(1.0);
  }
}

int questIsNew() {
  if(currentQuest != lastQuest)
    return(1);
  else
    return(0);
}

int questDescIsValid() {
  if(strlen(p1.questDesc) > 2)
    return(1);
  else {
    setParam(3, "Quest Desc is invalid");
  }
    return(0);
}
