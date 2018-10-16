#include <kos.h>
#include <GL/gl.h>
#include <GL/glkos.h>
#include <time.h>
#include <dc/pvr.h>
#include <stdio.h>
#include "header.h"
#include "global_var.h"

extern uint8    romdisk[];
KOS_INIT_ROMDISK(romdisk);
maple_device_t  *cont;
cont_state_t    *state;
uint64          e_time, s_time;
int             game_active = 1;
int             game_state = 0;
int             render_map = 1;

scene     *currentScene;
scene     *tempScene;
player    p1;
font      courrier;
float     displayPos[3] = {0,0,0};
long      frameCount = 0;
char      *loadPath = "/cd";

texture t;

int main()
{
  glKosInit();
	initGL();

  //sounds stuff
  snd_init();
  snd_stream_init();
  sndoggvorbis_init();

  LUA_initLua();
  p1 = initPlayer(0);
  initQuest();
  //VMU_loadGame();
  loadFont("/rd/DFKei.png");
  //loadCycle();

  tempScene = malloc(sizeof(scene));
  currentScene = malloc(sizeof(scene));
  tempScene = currentScene;
  loadHideout(currentScene);

  game_state = EXPLORATION;

  while(game_active)
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (tempScene != currentScene) {
      free(tempScene);
      *currentScene = *tempScene;
    }

    //GAME RENDER
    glEnable(GL_LIGHTING);
    limitScreen(currentScene->mapSize[0], currentScene->mapSize[1]);
    renderScene(currentScene);
    drawCursor();

    //UPDATE
    updatePlayer();
    if(game_state == EXPLORATION || game_state == ENIGME)
      updateScene(currentScene);

    //MENU + GUI
    glDisable(GL_LIGHTING);
    renderDialog();
    renderQuest();
    debugScreen();
    renderMenu();

    //END FRAME
    frameCount++;
    p1.pstate.buttons &= p1.state->buttons;
    glKosSwapBuffers();
    //game_active = 0;
  }
  printf("Exiting game.\n");
  return(0);
}
