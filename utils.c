#include <kos.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <zlib/zlib.h>
#include <GL/glkos.h>
#include "header.h"
#include "vmu.h"

time_t  master_time;

void  initGL() // We call this right after our OpenGL window is created.
{
  srand((unsigned) time(&master_time));
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
  glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer

  //glDepthFunc(GL_LEQUAL);				// The Type Of Depth Test To Do
  //glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
  glDisable(GL_NEARZ_CLIPPING_KOS);

  glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				// Reset The Projection Matrix
  glOrtho(0.0, 640.0, 0.0, 480.0, -20.0, 20.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  GLfloat ambi[] = {1.0, 1.0, 1.0, 1.0};
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambi);
  glEnable(GL_COLOR_MATERIAL);
}

void  basicLight() {
  GLfloat ambi[] = {1.0, 1.0, 1.0, 1.0};
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambi);
}

void  limitScreen(int width, int height) {
  if (displayPos[0] > 0)
    displayPos[0] = 0;

  if (displayPos[1] > 0)
    displayPos[1] = 0;

  if (displayPos[0] < -(width-640))
    displayPos[0] = -(width-640);

  if (displayPos[1] < -(height-480))
    displayPos[1] = -(height-480);
  }

char* findFile(char *filename) {
  file_t  file;
  char  *path[50];
  char  *dest[4];

  sprintf(path, "%s%s", loadPath, filename);
  return(path);

  /*
  dest[0] = "/cd";
  dest[1] = "/pc";
  dest[2] = "/rd";
  dest[3] = "/sd";

  for(int i = 0; i < 3; i ++){
    sprintf(path, "%s%s", dest[i], filename);
    if ((file = fs_open(path, O_RDONLY)) != -1){
      printf("Found file %s at %s\n", filename, dest[i]);
      fs_close(file);
      return(path);
    }
    fs_close(file);
  }

  return("");
  */
}

int   mount_romdisk(char *filename, char *mountpoint){
  void  *buffer;
  char  path[100];
  int   length = 0;
  char  *dest[3];
  file_t f;

  dest[0] = "/cd";
  dest[1] = "/pc";
  dest[2] = "/sd";

  for(int i = 0; i < 3; i ++){
    sprintf(path, "%s%s", dest[i], filename);
    f = fs_open(path, O_RDONLY);
    if(f != -1) {
      length = fs_total(f);
      printf("Found romdisk at %s -> size : %u\n", dest[i], length);
      break;
    } else {
    }
  }
  fs_close(f);

  ssize_t size = fs_load(path, &buffer);
  // Successfully read romdisk image
  if(size != -1)
  {
    fs_romdisk_mount(mountpoint, buffer, 1);
    printf("Romdisk mounted at %s\n", mountpoint);
  }
}
  /*
int   mount_gz_romdisk(char *filename, char *mountpoint){
    void *buffer;
    int length;

    length = zlib_getlength(filename);
    if(length == 0)
      return 2;

    // Open file
    gzFile file = gzopen(filename, "rb");
    if(!file)
        return 0;

    // Allocate memory, read file
    buffer = malloc(length);
    gzread(file, buffer, length);
    gzclose(file);

    // Mount
    fs_romdisk_mount(mountpoint, buffer, 1);
    return 1;
}
  */

int   loadFile(char *filename) {
  void *buffer;
  int size = fs_load(filename, &buffer);

  // Successfully read romdisk image
  if(size != -1)
  {
      //fs_romdisk_mount(mountpoint, buffer, 1);
      return size;
  }
  else
      return 0;
}

/*
void  toggleMenu() {
  if (buttonPressed(CONT_START)) {
    if(game_state != MENU) {
      l_game_state = game_state;
      LUA_getQuest();
      game_state = MENU;
    }
    else
      game_state = l_game_state;
  }
}
*/

int cMenu = 0;
void  renderMenu() {
  char *option[4] = {"Return to Menu", "Save (not yet)", "Load (not yet)", "Quit Game (DEV ONLY)"};
  toggleMenu();
  //basicLight();
  if (game_state == MENU) {
    if(buttonPressed(CONT_DPAD_DOWN) && cMenu < 3)
      cMenu++;
    if(buttonPressed(CONT_DPAD_UP) && cMenu > 0)
      cMenu--;

    if(buttonPressed(CONT_A)) {
      switch(cMenu) {
        case 0:
          currentScene->freeScene(currentScene);
          loadMenu(tempScene);
          break;
        case 1:
          VMU_saveGame();
          break;
        case 2:
          VMU_loadGame();
          break;
        case 3:
          quitGame();
          break;
      }
    }

    float cellSize = 10;

    for(int i = 0; i < 4; i++) {
      if (i == cMenu)
        fontColor(1.0, 0.0, 0.0);

      writeFont(option[i], 320 - (strlen(option[i])/2 * cellSize), (220 + 20) - (20 * i));
      resetFontColor();
    }

  }
}

int   getTime() {
  return clock() / CLOCKS_PER_SEC;
}

double distance(float x1,float y1,float x2,float y2) {
  double dx = x1 - x2;
  double dy = y1 - y2;
  //dx = dx;
  //dy = dy;
  return fsqrt((float)((dx)*(dx)+(dy)*(dy)));
}

gameObject cycle;
void   loadCycle() {
  cycle = createObject("/rd/horloge_v1.png", 0,0, 1);
  //setAlpha(&cycle, 0.7);
}

float angle;
void  renderCycle() {
  if(game_state == EXPLORATION) {
    glPushMatrix();
    glTranslatef(320, 480 + 64, -5);
    glRotatef(angle, 0,0,1);
    draw_textured_quad(&cycle.t, 0,0,0);
    glPopMatrix();
    angle += 0.01;
  }
}

void  quitGame(){
    exit(1);
}

int   getRand(int modulo){
  return rand() % modulo;
}

uint64_t getTime_MS() {
    uint32 s_s, s_ms;
    timer_ms_gettime(&s_s, &s_ms);
    return s_s*1000 + s_ms;
}
