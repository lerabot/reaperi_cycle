#include <kos.h>
#include <string.h>
#include <math.h>
#include "gl_png.h"
#include "lua_binds.h"
#include "gl_font.h"
#include "debug_screen.h"
#include "../global_var.h"
#include "../header.h"

font f;
texture box;
texture portrait;
char *portraitFile = "";
char *active_npc = "";
char boxText[196] = "";

int textActive = 0;
int showDialog = 0;
int showPortrait = 0;
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
  portraitFile = "No Portrait";

  png_to_gl_texture(&box, "/rd/box_raw.png");
  box.a = 0;

  png_to_gl_texture(&tmp.txtFont, path);
  tmp.glyphSize   = 16;
  tmp.glyphScale  = 1;
  setUV(&tmp.txtFont, 0.0625, 0.0625);
  tmp.txtFont.mag_filter = GL_NEAREST;
  f = tmp;
  return(tmp);
}

//main rendering fonction
void    renderDialog() {
  float speed = 3;
  float aSpeed = 0.010;
  int margin = 36;
  int x = 56 + margin * 2;
  int y = 100 + 64 - margin;

  if(buttonPressed(CONT_A)) {
    //check for NPC
    if (showDialog == 1)
      setDialog(LUA_getDialog(active_npc));
    else
      textActive = 0;
  }

  if(buttonPressed(CONT_B)) {
    textActive = 0;
  }

  //show dialog animation
  if(textActive != 0 && frame < 90) {
    portraitY = sin(frame * (3.1416 / 180)) * 240;
    frame += speed;
    box.a += aSpeed;
    textActive = 1;
    blackScreen(aSpeed);
    hideController();
  }

  //Remove dialog animation
  if(textActive == 0 && frame > -90) {
    portraitY = sin(frame * (3.1416 / 180)) * 240;
    frame -= speed;
    box.a -= aSpeed;
    blackScreen(aSpeed);
    showController();
  }

  //Return to the exploration state once the animation is done
  if (textActive == 0 && frame <= -90) { //
    game_state = EXPLORATION;
  }

  //draw the portait
  if(showPortrait)
    draw_textured_quad(&portrait, portraitX, portraitY, 5.0);

  if(showDialog) {
    draw_textured_quad(&box, 320, 100, 5.0);
    if(frame > 40)
      writeFontDelay(boxText, x, y, 6);
  }
}

//activate a NPC portait and trigger thier dialog
int    activateNPC (char *npc_name, char *filename) {
  showPortrait = setPortrait(filename);
  setDialog(LUA_getDialog(npc_name));
  active_npc = npc_name;
  return(textActive);
}

//set the portrait / image. 1 = new image, 0 = not new image
int     setPortrait (char *filename) {
  char message[256];
  //sprintf(message, "Old Portrait %s ,\nPortrait %s", portraitFile, filename);
  sprintf(message, "Old Portrait %s ,\nNew Portrait %s", portraitFile, filename);

  //check if the portrait is empty
  if (strcmp(filename, "") == 0) {
    strcat(message, " is empty.");
    setParam(5, message);
    return(0);
  }

  //check if the portrait has changed
  if  (strcmp(filename, portraitFile) == 0) {
    //strcat(message, " is old.");
    setParam(5, message);
    return (1);
  }

  //if they're different
  if (strcmp(filename, portraitFile)) {
    //delete the old tecture
    if(strlen(filename) > 2)
      glDeleteTextures(1, &portrait.id);
    png_to_gl_texture(&portrait, filename);
    strcpy(portraitFile, filename);
    strcat(message, " is New!");
    setParam(5, message);
    return(1);
  }

  return(0);
}

void    resetPortrait() {
  if(strcmp(portraitFile, "") != 0) {
    glDeleteTextures(1, &portrait.id);
    portraitFile = "";
  }
  showPortrait = 0;
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

int     setDescription (char *dialog) {
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

void    fontColor(float r, float g, float b) {
  f.txtFont.color[0] = r;
  f.txtFont.color[1] = g;
  f.txtFont.color[2] = b;
}

void    resetFontColor() {
  f.txtFont.color[0] = f.txtFont.color[1] = f.txtFont.color[2] = 1.0f;
}

void    setFontScale(float scale) {
  f.glyphScale = scale;
  setScale(&f.txtFont, scale);
}

void    resetFontScale() {
  f.glyphScale = 1.0;
  setScale(&f.txtFont, 1.0);
}

void    writeFont(char *string, int x, int y){
  float cellSize = 10 * f.glyphScale; //char width
  int maxGlyph = 36;
  int c = 0; //char number
  int l = strlen(string);
  int line = 0;
  char glyph;

  for (int i = 0; i < l; i++){
    glyph = *string;
    setChar(glyph);
    draw_textured_quad(&f.txtFont, x + (c * cellSize), y - (line * 16), 9);
    c++;
    string++;
    if (c == l)
      c = line = 0;
    if (glyph == '\n' || (c > maxGlyph && glyph == ' ' )) {
      line++;
      c = 0;
    }
  }
}

int     writeFontDelay(char *string, int x, int y, int delay){
  float cellSize = 10 * f.glyphScale; //char width
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
    draw_textured_quad(&f.txtFont, x + (c * cellSize), y - (line * 16), 9);
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