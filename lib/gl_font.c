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
char *portraitFile   = "";
char activeNPC[64];
char boxText[196]    = "";

int dialogActive = 0;
int showDialog = 0;
int showPortrait = 0;
int portraitX, portraitY;
float frame;
float screenAlpha;

int tLength = 0; //text length
int cLength = 0; //current length

int len = 0; //longeur du texte actuel

//probablement chercke si retourner un font tmp est une bonne chose pour la mémoire.
font    loadFont(char *path){
  font tmp;

  frame = -90;
  portraitX = 320;
  portraitY = -240;
  showDialog = 0;

  png_to_gl_texture(&portrait, "/rd/trans32.png");
  png_to_gl_texture(&box, "/rd/box_raw.png");
  box.a = 0;

  png_to_gl_texture(&tmp.txtFont, path);
  tmp.glyphSize   = 16;
  tmp.cellSize    = 10;
  tmp.glyphScale  = 1;
  setUV(&tmp.txtFont, 0.0625, 0.0625);
  tmp.txtFont.mag_filter = GL_NEAREST;
  f = tmp;
  return(tmp);
}

//main rendering fonction
void    renderDialog() {
  float speed =   3.7;
  float aSpeed =  0.012;
  int margin =    36;
  int x =         56 + margin * 2;
  int y =         100 + 64 - margin;

  //LOGIC FUR BUTTONS
  if(buttonPressed(CONT_A)) {
    //check for NPC
    if (cLength < tLength)
      cLength = tLength;
    else {
      dialogActive = setDialog(LUA_getDialog(activeNPC));
    }
  }

  if(buttonPressed(CONT_B)) {
    dialogActive = 0;
  }

  if (game_state == DIALOG) {
    //show dialog animation
    if(dialogActive != 0 && frame < 90) {
      portraitY = sin(frame * (3.1416 / 180)) * 240;
      frame += speed;
      box.a += aSpeed;
      dialogActive = 1;
      //blackScreen(aSpeed);
      hideController();
    }

    //Remove dialog animation
    if(dialogActive == 0 && frame > -90) {
      portraitY = sin(frame * (3.1416 / 180)) * 240;
      frame -= speed;
      box.a -= aSpeed;
      //blackScreen(aSpeed);
      showController();
    }

    //Return to the exploration state once the animation is done
    if (dialogActive == 0 && frame <= -90) { //
      game_state = EXPLORATION;
    }

    //draw the portait
    if(showPortrait)
      draw_textured_quad(&portrait, portraitX, portraitY, 5.0);

    //if(dialogActive) {
      draw_textured_quad(&box, 320, 100, 5.0);
      if(frame > 40)
        writeFontDelay(boxText, x, y, 4);
    //}
  }
}

//activate a NPC portait and trigger thier dialog
int     activateNPC (const  char *npc_name, char *filename) {
  game_state = DIALOG;
  //Get the portrait
  showPortrait = setPortrait(filename);
  //Get the textID
  dialogActive = setDialog(LUA_getDialog(npc_name));

  strcpy(activeNPC, npc_name);
  //activeNPC = npc_name;
  return(dialogActive);
}

//set the portrait / image. 1 = new image, 0 = not new image
int     setPortrait (char *filename) {
  char message[256];
  file_t file;

  //check if file exists
  if ((file = fs_open(filename, O_RDONLY)) != -1){
    fs_close(file);
    sprintf(message, "Found %s", filename);

    //check if the portrait is the same
    if (strcmp(filename, portraitFile) == 0) {
      printf("Same portrait\n");
      return (1);
    }

    //if the portrait is different
    if (strcmp(filename, portraitFile)) {
      glDeleteTextures(1, &portrait.id);
      png_to_gl_texture(&portrait, filename);
      strcpy(portraitFile, filename);
      return(1);
    }
  //if the file doesn't exist
  } else {
    strcpy(portraitFile, "");
    return(0);
  }
  return(0);
}

void    resetPortrait() {
  /*
  if(strcmp(portraitFile, "") != 0) {
    glDeleteTextures(1, &portrait.id);
    strcpy(portraitFile, '\0');
  }
  */
  showPortrait = 0;
}

void    resetActiveNPC() {
  activeNPC[0] = '\0';
}

char*   getActiveNPC() {
  return(activeNPC);
}

//returns 1 if there's a dialog
int     setDialog (char *dialog) {
  cLength = tLength = 0;
  if(strlen(dialog) > 2) {
    strcpy(boxText, dialog);
    return(1);
  }
  boxText[0] = '\0';
  cLength = tLength = 0;
  return (0);
}

int     setDescription (char *dialog) {
  //reset both the portrait and the current npc
  resetPortrait();
  resetActiveNPC();

  //Check for the dialog length for valid text
  if (strlen(dialog) > 2) {
    memcpy(boxText, dialog, strlen(dialog));
    boxText[strlen(dialog)] = '\0';
    showDialog = 1;
    dialogActive = 1;
    game_state = DIALOG;
    len = 0;
    return(1);
  } else { //otherwise, go back to exploration
    boxText[0] = '\0';
    dialogActive = 0;
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

int     getCellSize() {
  return(f.cellSize);
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
  float cellSize  = 10 * f.glyphScale; //char width
  int   maxGlyph  = 36;
  int   line      = 0;
  int   c         = 0; //current char;
  char  glyph;
  char  nString[cLength];

  tLength = strlen(string);
  strncpy(nString, string, cLength);
  for (int i = 0; i < cLength; i++){
    glyph = nString[i];
    setChar(glyph);
    draw_textured_quad(&f.txtFont, x + (c * cellSize), y - (line * 16), 9);
    c++;
    if (c == cLength)
      c = line = 0;
    if (glyph == '\n' || (c > maxGlyph && glyph == ' ' )) {
      line++;
      c = 0;
    }
  }

  if (frameCount % delay == 0 && cLength < tLength)
    cLength++;

  if (cLength == tLength)
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
