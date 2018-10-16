#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../header.h"
#include "../global_var.h"
#include "scene_hideout.h"
#include "gl_font.h"
#include "dreamroqlib.h"

//ENIGME
int         buttonState[9] = {0};
int         combinationDone[4] = {0};
int         parchemin[3] = {0};
int         cubeLock[2] = {0};
gameObject  glyph[4];
gameObject  b[9];
gameObject  *cube;
texture     bg;
texture     cubeAnim;
sfxhnd_t    b_sound;
int         cubeY = 0;
int         enigmeActive = 0;
int         vid93 = 0;
#define     CUBE 58

#define     LIGHT_COUNT 3
int         light_active = 1;
float       z_light = 125;
GLfloat     l_pos[3][4] = {
              {662, 474, 50, 1.0f},
              {275, 452, 80, 1.0f},
              {911, 364, 60, 1.0f}};

gameObject  fire_anim;

void  loadHideout(scene* self) {
  int r = 0;
  mount_romdisk("/asset/rd_hideout.img", "/rd");
  r = loadMapData(self, "/rd/map_hideout.svg");

  self->obj[0] = createObject("/rd/soussol_floor.png", -1000, -1000, 1);
  //setScale(&self->obj[0].t, 2);
  generateFloor(self, 0);

  fire_anim = createObject("/rd/new_fire_anim.png", -1000, -1000, 1);
  setUV(&fire_anim.t, 0.25, 0.5);
  fire_anim.frames = 7;
  setScale(&fire_anim.t, 0.5);

  //Possiblement faire un fonction qui set tout ca?
  png_to_gl_texture(&cubeAnim, "/rd/cube_anim.png");
  setUV(&cubeAnim, 0.25, 0.50);
  setAnim(&cubeAnim, 0);
  cube = findObject(self, "cube");
  setTexture(cube, &cubeAnim);
  moveObject(cube, cube->x, cube->y + 25);
  cube->frames = 7;
  cubeY = cube->y;

  b_sound = snd_sfx_load("/rd/bouton.wav");
  //char *music_path = "";
  //music_path = findFile("/asset/music/soussol.ogg");
  //sndoggvorbis_start("/cd/asset/music/hideout_v2.ogg", 1);
  //sndoggvorbis_volume(255);

  char p[100];
  //BOUTONS
  for (int i = 0; i < 9; i++) {
    //sprintf(p, "/asset/map_hideout/b%i.png", i+1);
    sprintf(p, "/rd/b%i.png", i+1);
    b[i] = createObject(p, 300, 300, 1);
    setUV(&b[i].t, 0.25, 1.0);
  }
  //GLYPHS
  for (int i = 0; i < 4; i++) {
    //sprintf(p, "/asset/map_hideout/glyph_%i.png", i+1);
    sprintf(p, "/rd/glyph_%i.png", i+1);
    glyph[i] = createObject(p, -300, -300, 0);
    //setAlpha(glyph[i], float alpha)
    setUV(&glyph[i].t, 0.5, 1.0);
    setAnim(&glyph[i].t, 1);
  }
  png_to_gl_texture(&bg, "/rd/bg_enigme.png");
  setScale(&bg, 1.3);

  LUA_loadDialog("/rd/hideout_dialog.json");
  LUA_addQuest(89);

  game_state    = EXPLORATION;
  p1.currentMap = MAP_HIDEOUT;

  self->updateScene   = updateHideout;
  self->freeScene     = freeHideout;
  self->renderScene   = renderHideout;
  printf("Map Hideout loaded completely!\n");
}

//verify the 4 different combo
int   checkCombination() {
  int combination[4][9] = {
    {1,0,1,1,0,1,0,1,0},
    {1,0,1,0,1,0,1,0,1},
    {1,1,0,1,0,0,1,0,1},
    {1,0,0,0,1,1,0,1,1}
  };
  int result = 0; //0 = bad, 1 = good

  for (int j = 0; j < 4; j++) {
    if(memcmp(buttonState, combination[j], sizeof(buttonState)) == 0 && combinationDone[j] == 0) {
      combinationDone[j] = 1;
      return(1);
    }
  }
  return(0);
}

/*
int nDelay = 100;
sfxhnd_t  test;
void wierdMusic(scene *self) {
  if (frameCount % nDelay == 0) {
    test = snd_sfx_load(findFile("/asset/SFX/pluck_2.wav"));
    int r = getRand(6);
    int v = getRand(40) + 120;
    setInt(2, r);
    //snd_sfx_stop_all
    setInt(3, snd_sfx_play(test, 128, 128));
    nDelay = 100 + getRand(50);
  }
  //snd_sfx_play(desert_sfx, 128, 128);
}
*/
void  drawGlyphs(scene *self) {
  int glyphPos[4][3] = {
    {320, 240 + 160, 5},
    {320 + 160, 240, 5},
    {320, 240 - 160, 5},
    {320 - 160, 240, 5},
  };

  for (int i = 0; i < 4; i++) {
    if(combinationDone[i] == 1 && glyph[i].t.a < 0.90)
      glyph[i].t.a+= 0.02;

    //ALTERNATE ANIM
    /*
    if(combinationDone[i] == 0)
      setAnim(&glyph[i].t, 0);
    else
      setAnim(&glyph[i].t, 1);
    */

    moveObject(&glyph[i], glyphPos[i][0] - displayPos[0], glyphPos[i][1] - displayPos[1]);
    drawObject(&glyph[i]);
  }
}

//update the side of each clicks
void  updateSides(int i) {
  // HAUT
  if (i + 3 < 9 && i + 3 > -1){
    switch(buttonState[i+3]){
      case 0:
        buttonState[i+3] = 1;
        break;
      case 1:
        buttonState[i+3] = 0;
        break;
    }
  }

  // BAS
  if (i - 3 < 9 && i - 3 > -1){
    switch(buttonState[i-3]){
      case 0:
        buttonState[i-3] = 1;
        break;
      case 1:
        buttonState[i-3] = 0;
        break;
    }
  }

  // GAUCHE
  if (i - 1 < 9 && i - 1 > -1 && ((i+1) - 1) % 3 != 0){
    switch(buttonState[i-1]){
      case 0:
        buttonState[i-1] = 1;
        break;
      case 1:
        buttonState[i-1] = 0;
        break;
    }
  }

  // DROITE
  if (i + 1 < 9 && i + 1 > -1 && ((i+1) + 1) % 3 != 1){
    switch(buttonState[i+1]){
      case 0:
        buttonState[i+1] = 1;
        break;
      case 1:
        buttonState[i+1] = 0;
        break;
    }
  }
}

//reset the tiles
void  resetEnigme() {
  for (int i = 0; i < 9; i++) {
    buttonState[i] = 0;
  }
}

//actual enigme
void  enigmeHideout(scene *self){
  int spacing = 64 + 2;
  int xO = 320 + -displayPos[0];
  int yO = 240 + -displayPos[1];

  if(game_state == ENIGME) {
    if(buttonPressed(CONT_B)) {
      resetEnigme();
      resetActiveNPC();
      render_map = 1;
      light_active = 1;
      game_state = EXPLORATION;
    }

    //ENIGME COMPLETE
    int c[4] = {1,1,1,1};
    if(memcmp(combinationDone, c, sizeof(int) * 4) == 0) {
      LUA_addQuest(93);
      render_map = 1;
      light_active = 1;
      game_state = EXPLORATION;
    }


    light_active = -1;
    draw_textured_quad(&bg, xO, yO, -5);
    drawGlyphs(self);
    //TILES
    for (int j = -1; j < 2; j++) {
      for (int i = -1; i < 2; i++) {
        int k = (i+1) + (j+1)*3;

        if(clicked(&b[k], CONT_A)){
          setInt(1, k);
          switch(buttonState[k]){
            case 0:
              buttonState[k] = 1;
              break;
            case 1:
              buttonState[k] = 0;
              break;
            case 2:
              buttonState[k] = 0;
              break;
          }
          snd_sfx_play(b_sound, 175, 128);
          updateSides(k);

          if(checkCombination()) {
            for(int i = 0; i < 9; i++){
              if(buttonState[i] == 1)
                buttonState[i] = 2;
            }
          } else {
            for(int i = 0; i < 9; i++){
              if(buttonState[i] == 2)
                buttonState[i] = 1;
            }
          }
        }

        setAnim(&b[k].t, buttonState[k]);
        moveObject(&b[k], i * spacing + xO, j * spacing + yO);
        drawObject(&b[k]);
      }
    }
  }
}

void  updateLights(scene *self){
  float flick[4];
  GLfloat l_diff[] = {0.5f, 0.5f, 0.5f, 1.0f};


  if(frameCount % 5 == 0)
    flick[rand()%4] = rand()%10 / 100.0f;


  if(game_state != ENIGME){
    glDisable(GL_LIGHT0);
    glLoadIdentity();
    glPushMatrix();
    glTranslated((int)displayPos[0], (int)displayPos[1], displayPos[2]);
    //Let's draw the lights here
    for(int i = 0; i < LIGHT_COUNT; i++) {
      l_diff[0] = l_diff[1] = l_diff[2] = 0.7;
      glLightfv(GL_LIGHT1 + i, GL_DIFFUSE,  l_diff);
      glLightfv(GL_LIGHT1 + i, GL_POSITION, l_pos[i]);
      glEnable(GL_LIGHT1 + i);
    }
    glPopMatrix();
  } else {
    glEnable(GL_LIGHT0);
  }
}

void  updateHideout(scene *self){
  char* m = "";

  if(p1.questID == 89) {
    playROQvideo("/cd/asset/video/hideout_intro_sound.roq");
    activateNPC("intro", "/rd/intro.png");
  }

  if(p1.questID == 90) {
    if(strcmp(getActiveNPC(), "s_mystere") == 0)
      cubeLock[0] = 1;
    if(strcmp(getActiveNPC(), "cube") == 0)
      cubeLock[1] = 1;

    if(cubeLock[0] == 1 && cubeLock [1] == 1 && game_state == EXPLORATION) {
      LUA_addQuest(91);
    }
  }

  // MYSTERIOUS CUBE
  if(p1.questID == 91) {
    if(strcmp(getActiveNPC(), "parchemin1") == 0)
      parchemin[0] = 1;
    if(strcmp(getActiveNPC(), "parchemin2") == 0)
      parchemin[1] = 1;
    if(strcmp(getActiveNPC(), "parchemin3") == 0)
      parchemin[2] = 1;

    sprintf(m, "P1%u|P2%u|P3%u", parchemin[0], parchemin[1], parchemin[2]);
    setString(3, m);
    if(parchemin[0] == 1 && parchemin[1] == 1 && parchemin[2] == 1) {
      LUA_addQuest(92);
      enigmeActive = 1;
      setString(4, "Cube unlocked");
    }
  }

  //Activate Enigme
  char *npc = getActiveNPC();
  if(p1.questID == 92 && (strcmp(npc, "cube") == 0)) {
    game_state = ENIGME;
    render_map = 0;
  }

  //Lights
  //if (buttonPressed(CONT_X))
    //light_active = -light_active;
  updateLights(self);
}

void  renderHideout(scene *self){
  if (game_state == ENIGME)
    enigmeHideout(self);

  if (game_state != ENIGME) {
    nextFrame(&fire_anim, 7);
    for(int i = 0; i < LIGHT_COUNT; i++){
      moveObject(&fire_anim, l_pos[i][0], l_pos[i][1]);
      drawObject(&fire_anim);
    }
  }

  setString(3, getPositionString());

  if(p1.questID == 93 && vid93 == 0) {
    //playROQvideo("/cd/video/cube_v1.roq");
    //vid93 = 1;
  }
  //update cube anim
  cube->y = cubeY + (sin(frameCount/100.0f) * 10);
  nextFrame(cube, getRand(5) + 4);
}

void  freeHideout(scene *self){
  freeSpritesheet();
}
