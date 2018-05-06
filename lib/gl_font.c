#include <kos.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include "gl_png.h"
#include "gl_font.h"
#include "debug_screen.h"
#include "../global_var.h"

font f;

texture box;
texture portrait;
char *portraitFile;
char boxText[196] = "";

int showDialog = 0;
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

void    setFont(font *f){
  //theFont = f;
}

void    renderDialog() {
  float speed = 2;
  float aSpeed = 0.01;
  int margin = 36;
  int x = 56 + margin * 2;
  int y = 100 + 64 - margin;

  if(showDialog != 0 && frame < 90) {
    //portraitX = sin(frame * (3.1416 / 180)) * 320;
    portraitY = sin(frame * (3.1416 / 180)) * 240;
    frame += speed;
    box.a += aSpeed;
    hideController();
  }

  if(showDialog == 0 && frame > -90) {
    //portraitX = sin(frame * (3.1416 / 180)) * 320;
    portraitY = sin(frame * (3.1416 / 180)) * 240;
    frame -= speed;
    box.a -= aSpeed;
    showController();
  }

  blackScreen(box.a);
  if(strlen(portrait.path) > 1)
    draw_textured_quad(&portrait, portraitX, portraitY);

  if (boxText != NULL) {
    draw_textured_quad(&box, 320, 100);
    if(showDialog != 0 && frame > 70) {
      if(portraitY > 200)
        writeFontDelay(boxText, x, y, 6);
    }
  }
}

void    setDialog(char *s, char *filename) {
  memcpy(boxText, s, strlen(s));
  boxText[strlen(s)] = '\0';
  showDialog = strlen(s);

  if (strcmp(filename, portraitFile) != 0) {
    glDeleteTextures(1, &portrait.id);
    png_to_gl_texture(&portrait, filename);
    portraitFile = filename;
  }
  setString(0, portraitFile);
  len = 0;
}

void    resetText() {
  len = 0;
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
    draw_textured_quad(&f.txtFont, x + (c*cellSize), y - (line * 16));
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
  int c = 0; //char number
  int line = 0;
  int l = strlen(string);
  char glyph;
  char nString[len];

  strncpy(nString, string, len);
  for (int i = 0; i < len; i++){
    glyph = nString[i];
    setChar(glyph);
    draw_textured_quad(&f.txtFont, x + (c*cellSize), y - (line * 16));
    c++;
    if (c == l)
      c = line = 0;
    if (glyph == '\n' || (c > 30 && glyph == ' ' )) {
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
