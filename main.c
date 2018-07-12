#include <GL/gl.h>
#include <GL/glkos.h>
#include <time.h>
#include <dc/pvr.h>
#include <stdio.h>
#include "header.h"

extern uint8    romdisk[];
KOS_INIT_ROMDISK(romdisk);
maple_device_t  *cont;
cont_state_t    *state;
uint64          e_time, s_time;
int             game_active = 1;
int             game_state = 0;

scene     *currentScene;
scene     *tempScene;
player    p1;
font      courrier;
float     displayPos[3] = {0,0,0};
long      frameCount = 0;

texture t;

int main()
{
  s_time = clock();
  glKosInit();
	initGL();

  //sounds stuff
  snd_stream_init();
  sndoggvorbis_init();

  LUA_initLua();
  p1 = initPlayer(0);
  //VMU_loadGame();
  loadFont("/rd/DFKei.png");

  tempScene = malloc(sizeof(scene));
  currentScene = malloc(sizeof(scene));
  tempScene = currentScene;
  loadTemple(currentScene);

  while(game_active)
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (tempScene != currentScene) {
      free(tempScene);
      *currentScene = *tempScene;
    }

    //UPDATE
    updatePlayer();
    if(game_state == EXPLORATION)
      updateScene(currentScene);

    //GAME RENDER
    glEnable(GL_LIGHTING);
    renderScene(currentScene);
    drawCursor();

    //MENU + GUI
    glDisable(GL_LIGHTING);
    renderMenu();
    if (game_state == DIALOG)
      renderDialog();

    debugScreen();

    glKosSwapBuffers();
    frameCount++;
    p1.pstate.buttons &= p1.state->buttons;
  }
  return(0);
}
