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
uint64          begin, end, t_diff;
int             game_active = 1;
int             game_state = 0;

scene     *currentScene;
scene     *tempScene;
player    p1;
font      courrier;
float     displayPos[3] = {0,0,0};
long      frameCount = 0;
lua_State *t_data;
lua_State *L;

texture t;

int main()
{
  glKosInit();
	initGL();

  //sounds stuff
  snd_stream_init();
  sndoggvorbis_init();

  setLuaState(&L);
  setLuaState(&t_data);

  p1 = initPlayer(0);
  loadFont("/rd/DFKei.png");

  tempScene = malloc(sizeof(scene));
  currentScene = malloc(sizeof(scene));
  tempScene = currentScene;
  loadSoussol(currentScene);

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
      currentScene->updateScene(currentScene);

    //GAME RENDER
    currentScene->renderScene(currentScene);
    drawCursor();

    //OVERLAYS
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
