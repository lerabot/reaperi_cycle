#include <kos.h>
#include <string.h>
#include <unistd.h>
#include <zlib/zlib.h>
#include "header.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

int l_game_state;


char* findFile(char *filename) {
  FILE *file;
  char *dest[3];
  char *path = "";


  dest[0] = "/cd";
  dest[1] = "/pc";
  dest[2] = "/sd";

  for(int i = 0; i < 3; i ++){
    snprintf(path, 50, "%s%s", dest[i], filename);
    if (file = fopen(path, "r")){
      fclose(file);
      setParam(1, path);
      return(path);
    }
  }
  return("NoFile!");
}

int mount_romdisk(char *filename, char *mountpoint){
  void *buffer;
  char path[50];
  char *dest[3];
  int length;

  dest[0] = "/cd";
  dest[1] = "/pc";
  dest[2] = "/sd";

  for(int i = 0; i < 3; i ++){
    snprintf(path, 50, "%s%s", dest[i], filename);
    length = zlib_getlength(path);
    if(length != 0)
      break;
  }

  // Open file
  gzFile file = gzopen(path, "rb");
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

int mount_gz_romdisk(char *filename, char *mountpoint){
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

int loadFile(char *filename) {
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

int loadLuaFile(lua_State *L_state, char *filename) {
  if(luaL_loadfile(L_state, filename) || lua_pcall(L_state, 0, 0, 0)) {
    setParam(3, lua_tostring(L_state, -1));
    return(0);
  }
  return (1);
}

void setLuaState(lua_State **L_state) {
  *L_state = luaL_newstate();
  luaL_openlibs(*L_state);
  luaopen_io(*L_state);
}

void toggleMenu() {
  if (buttonPressed(CONT_START)) {
    if(game_state != MENU) {
      l_game_state = game_state;
      game_state = MENU;
    }
    else
      game_state = l_game_state;
  }
}

int cMenu = 0;
void renderMenu() {
  char *option[4] = {"Return to Menu", "Save (not yet)", "Load (not yet)", "Quit Game (DEV ONLY)"};
  toggleMenu();
  if (game_state == MENU) {
    if(buttonPressed(CONT_DPAD_DOWN) && cMenu < 3)
      cMenu++;
    if(buttonPressed(CONT_DPAD_UP) && cMenu > 0)
      cMenu--;

    if(buttonPressed(CONT_A))
    switch(cMenu) {
      case 0:
        currentScene->freeScene(currentScene);
        loadMenu(tempScene);
        break;
      case 1:
        currentScene->freeScene(currentScene);
        loadSoussol(tempScene);
        break;
      case 2:
        break;
      case 3:
        quitGame();
        break;
    }

    for(int i = 0; i < 4; i++) {
      if (i == cMenu)
        fontColor(1.0, 0.0, 0.0);

      writeFont(option[i], 320 - (strlen(option[i])/2 * 10), (240 + 20) - (20 * i));
      resetFontColor();
    }
  }
}

void initGL() // We call this right after our OpenGL window is created.
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
  glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  //glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
  //glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
  glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				// Reset The Projection Matrix
  glOrtho(0.0, 640.0, 0.0, 480.0, -100.0, 100.0);
  //gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
  //glScalef(0.75, 1, 1);
  //glScalef(0.1, 0.1, 0.1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void quitGame(){
    exit(1);
}

clock_t cTime, lTime;
double avgTime = 0;
char buf[24];
float getFrameTime() {
  lTime = cTime;
  cTime = clock();
  avgTime = (double) (cTime - lTime) / CLOCKS_PER_SEC;
  if (frameCount % 60 == 0) {
    sprintf(buf, "Fr:%.8f", avgTime);
    setParam(1, buf);
  }
  return (float)avgTime/CLOCKS_PER_SEC/60;
}

