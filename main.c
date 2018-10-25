#include <kos.h>
#include <GL/gl.h>
#include <GL/glkos.h>
#include <time.h>
#include <dc/pvr.h>
#include <stdio.h>
#include "header.h"
#include "global_var.h"
#include "lib/debug_screen.h"

extern uint8    romdisk[];
KOS_INIT_ROMDISK(romdisk);
maple_device_t  *cont;
cont_state_t    *state;
uint64_t         end_time = 0;
uint64_t         start_time = 0;
int             game_active = 1;
int             game_state = 0;
int             l_game_state = 0;
int             render_map = 1;

scene     *currentScene;
scene     *tempScene;
player    p1;
font      courrier;
float     displayPos[3] = {0,0,0};
char      *loadPath = "/cd";
long      frameCount = 0;

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

  currentScene = malloc(sizeof(scene));
  tempScene = currentScene;
  loadHideout(currentScene);

  game_state = EXPLORATION;

  while(game_active)
  {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (tempScene != currentScene) {
      *currentScene = *tempScene;
      free(tempScene);
    }

    start_time = getTime_MS();

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

    //END FRAME
    glKosSwapBuffers();
    p1.pstate.buttons &= p1.state->buttons;
    //game_active = 0;
    frameCount++;
    setInt(0, frameCount);
    end_time = getTime_MS();
    //updateFrameTime(end_time - start_time); //Crashed the game?

  }
  printf("Exiting game.\n");
  return(0);
}
