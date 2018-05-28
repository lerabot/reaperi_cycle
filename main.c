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

void draw_quad(texture *tex, float x, float y) {
	float texW = tex->w * tex->uSize * tex->xScale;
	float texH = tex->h * tex->vSize * tex->yScale;
	float x0 = x - texW / 2;
	float y0 = y - texH / 2;
	float x1 = x + texW / 2;
	float y1 = y + texH / 2;
	float u = tex->u;
	float v = tex->v;
	float xS = tex->uSize;
	float yS = tex->vSize;

	float vertex_data[] = {
		/* 2D Coordinate, texture coordinate */
		x0, y1, 1.0f,
		x0, y0, 1.0f,
		x1, y1, 1.0f,
		x1, y0, 1.0f
	};

	float uv_data[] = {
		/* 2D Coordinate, texture coordinate */
		u, v + yS,
		u, v,
		u + xS, v + yS,
		u + xS, v
	};

	float normal_data[] = {
		/* 2D Coordinate, texture coordinate */
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0
	};

	float color_data[] = {
		/* 2D Coordinate, texture coordinate */
		1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0
	};

	setInt(0, x1);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex->id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tex->min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tex->mag_filter);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertex_data);
	glTexCoordPointer(2, GL_FLOAT, 0, uv_data);
	glNormalPointer(GL_FLOAT, 0, normal_data);
	glColorPointer(4, GL_FLOAT, 0, color_data);

	//glColor4f(tex->light * highlight[0],tex->light * highlight[1],tex->light * highlight[2], tex->a);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, vertex_data);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

int main()
{
  glKosInit();
  enableTrans();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 640.0, 0.0, 480.0, -1.0, 2.0);
  //glScalef(1.f/320.f, 1.f/240.f, 100.f);
  //glTranslatef(-320, -240, 0);
  //glOrtho(0, 640, 0, 480, -50, 50);
  glDisable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //glEnable(GL_LIGHTING);
  //glEnable(GL_LIGHT0);

  //sounds stuff
  snd_stream_init();
  sndoggvorbis_init();
  //mp3_init();

  setLuaState(&L);
  setLuaState(&t_data);

  p1 = initPlayer(0);
  loadFont("/rd/DFKei.png");

	/*
  tempScene = malloc(sizeof(scene));
  currentScene = malloc(sizeof(scene));
  tempScene = currentScene;
  loadTest(currentScene);
	*/

  png_to_gl_texture(&t, "/rd/DFKei.png");
  setInt(1, glIsTexture(t.id));


  uint64_t b, e;
  double avg;
  char buf[24];
  while(game_active)
  {
    b =  timer_us_gettime64();

		/*
    if (tempScene != currentScene) {
      free(tempScene);
      *currentScene = *tempScene;
    }
		*/

    pvr_get_stats(&stats);
    updatePlayer();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPushMatrix();
    //glTranslated((int)displayPos[0], (int)displayPos[1], displayPos[2]);
    draw_quad(&t, 320, 240);
    drawCursor();


    /*
    drawScene(currentScene);
    //FIX THIS SHIT
    currentScene->updateScene(state, currentScene);
    //post transform - GUI stuff
    renderDialog();
    renderMenu();
    debugScreen();
    */

    //glPopMatrix();
    debugScreen();
    //thd_sleep(10);
    glKosSwapBuffers();

    //adds the buttons to the previously pressed button
    p1.pstate.buttons &= p1.state->buttons;

    //frameCount++;

    if(buttonPressed(CONT_Y))
      game_active = 0;

    e =  timer_us_gettime64();
    avg = (double)(e - b)/1000;
    if (frameCount % 30 == 0) {
      sprintf(buf, "Frame:%.4f", stats.frame_rate);
      //setParam(2, buf);
    }
  }
  return(0);
}
