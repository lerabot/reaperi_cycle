#include <kos.h>
#include <stdlib.h>
#include "header.h"
#include "global_var.h"
#include "scene_hideout.h"
//#include <dc/sound/sfxmgr.h>
#include "lib/gl_font.h"

//ENIGME
int         buttonState[9] = {0};
gameObject  b[9];
texture     bg;
sfxhnd_t    b_sound;
int         enigmeActive = 1;

int light_active = 1;

void loadHideout(scene* self) {
  mount_romdisk("asset/rd_hideout.img.gz", "/rd");
  loadMapData(self, "/rd/map_hideout.svg");


  self->obj[0] = createObject("/rd/soussol_floor.png", -1000, -1000, 1);
  //setScale(&self->obj[0].t, 2);
  generateFloor(self, 0);

  b_sound = snd_sfx_load("/rd/bouton.wav");

  char* p = "";
  for (int i = 0; i < 9; i++) {
    sprintf(p, "/rd/b%i.png", i+1);
    b[i] = createObject(p, 300, 300, 1);
    setUV(&b[i].t, 0.25, 1.0);
  }

  png_to_gl_texture(&bg, "/rd/bg.png");

  LUA_loadDialog("/rd/hideout_dialog.json");
  LUA_addQuest(90);

  game_state = EXPLORATION;
  p1.currentMap = MAP_HIDEOUT;

  self->updateScene   = updateHideout;
  self->freeScene     = freeHideout;
  self->renderScene   = renderHideout;
}

//verify the 4 different combo
int checkCombination() {
  int combination[4][9] = {
    {0,1,0,1,0,1,0,1,0},
    {1,0,1,0,1,0,1,0,1},
    {1,1,1,1,0,1,1,0,1},
    {1,0,0,0,1,1,0,1,1}
  };
  int result = 0; //0 = bad, 1 = good

  for (int j = 0; j < 4; j++) {
    if(memcmp(buttonState, combination[j], sizeof(buttonState)) == 0)
      return(1);
  }
  return(0);
}

//update the side of each clicks
void updateSides(int i) {
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
void resetEnigme() {
  for (int i = 0; i < 9; i++) {
    buttonState[i] = 0;
  }
}

//actual enigme
void enigmeHideout(scene *self){
  int spacing = 64 + 2;
  int xO = 320 + -displayPos[0];
  int yO = 240 + -displayPos[1];

  if(game_state == ENIGME) {
    if(buttonPressed(CONT_B)) {
      resetEnigme();
      game_state = EXPLORATION;
    }

    glPushMatrix();
    //BACKGROUND
    setScale(&bg, 1.3);
    draw_textured_quad(&bg, xO, yO, -5);

    //TILES
    for (int j = -1; j < 2; j++) {
      for (int i = -1; i < 2; i++) {
        int k = (i+1) + (j+1)*3;

        if(clicked(&b[k], CONT_A)){
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
          snd_sfx_play(b_sound, 250, 128);
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

        //char* num = "";
        //sprintf(num, "b%i", k);
        setAnim(&b[k].t, buttonState[k]);
        moveObject(&b[k], i * spacing + xO, j * spacing + yO);

        drawObject(&b[k]);
        //writeFont(num, i * spacing + xO, j * spacing + yO);
      }
    }
    glPopMatrix();
  }
}

void updateLights(scene *self){
  float flick[4];
  GLfloat l_diff[] = {0.5f, 0.5f, 0.5f, 1.0f};
  float z_light = 15;
  GLfloat l_pos[4][4] = {
          {292, 291, z_light, 1.0f},
          {626, 447, z_light, 1.0f},
          {298, 645, z_light, 1.0f},
          {232, 428, z_light, 1.0f}
  };

  if(frameCount % 5 == 0)
    flick[rand()%4] = rand()%10 / 100.0f;


  if(light_active == 1){
    glDisable(GL_LIGHT0);
    glLoadIdentity();
    glPushMatrix();
    glTranslated((int)displayPos[0], (int)displayPos[1], displayPos[2]);
    for(int i = 0; i < 4; i++) {
      l_diff[0] = l_diff[1] = l_diff[2] = 0.8;
      glLightfv(GL_LIGHT1 + i, GL_DIFFUSE,  l_diff);
      glLightfv(GL_LIGHT1 + i, GL_POSITION, l_pos[i]);
      glEnable(GL_LIGHT1 + i);
    }
    glPopMatrix();
  } else {
    glEnable(GL_LIGHT0);
  }
}

void updateHideout(scene *self){
  //Activate Enigme
  if(pressed(&self->obj[29], CONT_A))
    game_state = ENIGME;

  //Lights
  updateLights(self);
  if(buttonPressed(CONT_X))
    light_active = -light_active;

  //setString(3, getPositionString());
  //blackScreen(1);
}

void renderHideout(scene *self){
  if (game_state == ENIGME)
    enigmeHideout(self);
}

void freeHideout(scene *self){
  freeSpritesheet();
}
