#include <GL/gl.h>
#include <GL/glkos.h>
#include <GL/glu.h>
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
  enableTrans();
  glMatrixMode(GL_PROJECTION);
  glOrtho(0, 640, 0, 480, -50, 50);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //glShadeModel(GL_SMOOTH);
  //glScalef(1.f/320.f, 1.f/240.f, 100.f);
  //glTranslatef(-320, -240, 0);

  //sounds stuff
  snd_stream_init();
  sndoggvorbis_init();
  //mp3_init();

  setLuaState(&L);
  setLuaState(&t_data);

  //lua_push

  p1 = initPlayer(0);
  loadFont("/rd/DFKei.png");

  tempScene = malloc(sizeof(scene));
  currentScene = malloc(sizeof(scene));
  tempScene = currentScene;
  loadTest(currentScene);

  png_to_gl_texture(&t, "/rd/DFKei.png");

  uint64_t b, e;
  double avg;
  char buf[24];
  while(1)
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
    draw_textured_quad(&t, 320, 240);

    //drawCursor();
    /*
    drawScene(currentScene);


    //FIX THIS SHIT
    currentScene->updateScene(state, currentScene);
    //post transform - GUI stuff
    renderDialog();
    renderMenu();
    debugScreen();

    */
    glPopMatrix();
    debugScreen();
    glKosSwapBuffers();

    //adds the buttons to the previously pressed button
    p1.pstate.buttons &= p1.state->buttons;


    //thd_sleep(10);
    //frameCount++;

    if(buttonPressed(CONT_Y))
      quitGame();

    e =  timer_us_gettime64();
    avg = (double)(e - b)/1000;
    if (frameCount % 30 == 0) {
      sprintf(buf, "Frame:%.4f", stats.frame_rate);
      setParam(2, buf);
    }
  }
  return(0);
}
