#include <kos.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "gl_png.h"
#include "gl_font.h"
#include "debug_screen.h"
#include "../global_var.h"

font f;
texture box;
texture portrait;
char *portraitFile = "";
char *active_npc = "";
char boxText[196] = "";

int textActive = 0;
int showDialog = 0;
int showPortait = 0;
int portraitX, portraitY;
float frame;
float screenAlpha;

int len; //longeur du texte actuel

//probablement chercke si retourner un font tmp est une bonne chose pour la mémoire.
font    loadFont(char *path){
  font tmp;

  frame = -90;
  portraitX = 320;
  portraitY = -240;
  showDialog = 0;

  png_to_gl_texture(&portrait, "/rd/trans32.png");
  portraitFile = "";

  png_to_gl_texture(&box, "/rd/box_raw.png");
  box.a = 0;

  png_to_gl_texture(&tmp.txtFont, path);
  tmp.glyphSize = 16;
  setUV(&tmp.txtFont, 0.0625, 0.0625);
  f = tmp;
  return(tmp);
}

//main rendering fonction
void    renderDialog() {
  float speed = 3;
  float aSpeed = 0.015;
  int margin = 36;
  int x = 56 + margin * 2;
  int y = 100 + 64 - margin;

  if(buttonPressed(CONT_A)) {
    //check for NPC
    if (showPortait == 1)
      setDialog(getLuaDialog(active_npc));
    else
      textActive = 0;
  }

  setString(3, active_npc);

  //show dialog animation
  if(textActive != 0 && frame < 90) {
    portraitY = sin(frame * (3.1416 / 180)) * 240;
    frame += speed;
    box.a += aSpeed;
    textActive = 1;
    hideController();
  }

  //Remove dialog animation
  if(textActive == 0 && frame > -90) {
    portraitY = sin(frame * (3.1416 / 180)) * 240;
    frame -= speed;
    box.a -= aSpeed;
    showController();
  }


  if (textActive == 0 && frame <= -90) { //
    game_state = EXPLORATION;
  }


  //draw the portait
  if(showPortait == 1)
    draw_textured_quad(&portrait, portraitX, portraitY, 5.0);

  if(showDialog == 1) {
    draw_textured_quad(&box, 320, 100, 5.0);
    if(frame > 40)
      writeFontDelay(boxText, x, y, 6);
  }
}

//activate a NPC portait and trigger thier dialog
void    activateNPC (char *npc_name, char *filename) {
  setPortrait(filename);
  setDialog(getLuaDialog(npc_name));
  active_npc = npc_name;
}

//set the portrait / image. 1 = new image, 0 = not new image
int     setPortrait (char *filename) {
  if (strcmp(filename, portraitFile) != 0) {
    glDeleteTextures(1, &portrait.id);
    png_to_gl_texture(&portrait, filename);
    portraitFile = filename;
    showPortait = 1;
    return(1);
  }
  return(0);
}

void    resetPortrait() {
  if(strcmp(portraitFile, "") != 0) {
    glDeleteTextures(1, &portrait.id);
    portraitFile = "";
    showPortait = 0;
  }
}

int     setDialog (char *dialog) {
  //Check for the dialog length for valid text
  if (strlen(dialog) > 2) {
    memcpy(boxText, dialog, strlen(dialog));
    boxText[strlen(dialog)] = '\0';
    showDialog = 1;
    textActive = 1;
    game_state = DIALOG;
    len = 0;
    return(1);
  } else { //otherwise, go back to exploration
    boxText[0] = '\0';
    textActive = 0;
    showDialog = 0;
    active_npc = "";
  }
  len = 0;
  return(0);
}

int     setDesciption (char *dialog) {
  //reset both the portrait and the current npc
  resetPortrait();
  active_npc = "";

  //Check for the dialog length for valid text
  if (strlen(dialog) > 2) {
    memcpy(boxText, dialog, strlen(dialog));
    boxText[strlen(dialog)] = '\0';
    showDialog = 1;
    textActive = 1;
    game_state = DIALOG;
    len = 0;
    return(1);
  } else { //otherwise, go back to exploration
    boxText[0] = '\0';
    textActive = 0;
    showDialog = 0;
    game_state = EXPLORATION;
  }
  len = 0;
  return(0);
}

char*   getLuaDialog(char *npc_name) {
  char *buf = "";
  lua_getglobal(L, "setDialog");
  lua_pushstring(L, npc_name);
  lua_pcall(L, 1, 0, 0);
  lua_settop(L, 0);
  lua_getglobal(L, "getDialog");
  lua_pcall(L, 0, 1, 0);
  buf = lua_tostring(L, -1);
  lua_pop(L,1);
  return(buf);
}

void    fontColor(float r, float g, float b) {
  f.txtFont.color[0] = r;
  f.txtFont.color[1] = g;
  f.txtFont.color[2] = b;
}

void    resetFontColor() {
  f.txtFont.color[0] = f.txtFont.color[1] = f.txtFont.color[2] = 1.0f;
}

void    writeFont(char *string, int x, int y){
  int cellSize = 10; //char width
  int c = 0; //char number
  int l = strlen(string);
  int line = 0;
  char glyph;

  for (int i = 0; i < l; i++){
    glyph = *string;
    setChar(glyph);
    draw_textured_quad(&f.txtFont, x + (c*cellSize), y - (line * 16), 9);
    c++;
    string++;
    if (glyph == '\n') {
      line++;
      c = 0;
    }
  }
}

int     writeFontDelay(char *string, int x, int y, int delay){
  int cellSize = 10; //char width
  int maxGlyph = 36;
  int c = 0; //char number
  int line = 0;
  int l = strlen(string);
  char glyph;
  char nString[len];

  strncpy(nString, string, len);
  for (int i = 0; i < len; i++){
    glyph = nString[i];
    setChar(glyph);
    draw_textured_quad(&f.txtFont, x + (c*cellSize), y - (line * 16), 9);
    c++;
    if (c == l)
      c = line = 0;
    if (glyph == '\n' || (c > maxGlyph && glyph == ' ' )) {
      line++;
      c = 0;
    }
  }

  if (frameCount % delay == 0 && len < l)
    len++;

  if (len == l)
    return(0);
  else
    return(1);
}

void    setFontAlpha(float a) {
  f.txtFont.a = a;
}

void    setChar(int c){
  float u = f.txtFont.uSize;
  float v = f.txtFont.vSize;

  c -= 16;
  f.txtFont.u = (c % (int)(1 / u)) * u;
  f.txtFont.v = 1 - ((c / (int)(1 / u)) * v);
}

void    resetText() {
  len = 0;
}