#ifndef __GLFONT_H__
#define __GLFONT_H__

#include "gl_png.h"

#define A_ICON 140
#define B_ICON 141
#define X_ICON 142
#define Y_ICON 143

typedef struct _font
{
  texture txtFont;
  int glyphSize;
} font;

font    loadFont(char *path);
int     loadText(char ***textArray, char *path);
char**  loadText2(char *path);
//DIALOG////////////////////////
int     toggleDialog();
void    renderDialog();
void    activateNPC (char *npc_name, char *filename);
int     setDialog(char *dialog);
int     setDesciption (char *dialog);
char*   getLuaDialog(char *npc_name);
int     setPortrait (char *filename);
void    textBox(char *string);
//MENU////////////////////////
void    displayMenu();
//FONT////////////////////////
void    writeFont(char *string, int x, int y);
int     writeFontDelay(char *string, int x, int y, int delay);
void    setFontAlpha(float a);
void    setChar(int c);
void    resetText();
//FONT COLOR///////////////////////
void    fontColor(float r, float g, float b);
void    resetFontColor();


#endif
