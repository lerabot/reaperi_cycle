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
pvr_stats_t     stats;
int             game_active = 1;

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
  //mp3_init();

  setLuaState(&L);
  setLuaState(&t_data);

  p1 = initPlayer(0);
  loadFont("/rd/DFKei.png");

  tempScene = malloc(sizeof(scene));
  currentScene = malloc(sizeof(scene));
  tempScene = currentScene;
  loadTemple(currentScene);

  png_to_gl_texture(&t, "/rd/DFKei.png");
  setInt(1, glIsTexture(t.id));


  uint64_t b, e;
  double avg;
  char buf[24];
  while(game_active)
  {
    b =  timer_us_gettime64();

    if (tempScene != currentScene) {
      free(tempScene);
      *currentScene = *tempScene;
    }

    pvr_get_stats(&stats);
    updatePlayer();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslated((int)displayPos[0], (int)displayPos[1], displayPos[2]);
    drawScene(currentScene);
    drawCursor();

    //FIX THIS SHIT
    currentScene->updateScene(state, currentScene);
    //post transform - GUI stuff
    glPopMatrix();
    renderDialog();
    renderMenu();
    debugScreen();
    glKosSwapBuffers();

    //adds the buttons to the previously pressed button
    p1.pstate.buttons &= p1.state->buttons;
    frameCount++;

    if(buttonPressed(CONT_Y))
      game_active = 0;

    e =  timer_us_gettime64();
    avg = (double)(e - b)/1000;
    if (frameCount % 30 == 0) {
      sprintf(buf, "Frame:%.4f", stats.frame_rate);
      setParam(2, buf);
    }
  }
  return(0);
}
