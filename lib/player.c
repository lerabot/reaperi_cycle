#include <string.h>
#include "player.h"
#include "../global_var.h"
#include "../utils.h"
#include "../header.h"
#include "lua_binds.h"
#include "debug_screen.h"
#include "gl_font.h"
#include "game_object.h"

int     currentItem = 0;
int     edgeSize = 120;
float   velocity[2] = {0, 1};
float   direction[2] = {0, 1};
float   position[2] = {0, 1}; //save the OG position if you add delta
char*   posString = "";

//sfxhnd_t null_sfx[3];
//sfxhnd_t click_sfx;

texture spirit_base;
texture spirit_outer;
texture ombre;
gameObject spirit_core;
gameObject spirit_particule;

player      initPlayer(int playerNum) {
    player temp;
    //Texture
    temp.obj = createObject("rd/inside_blue_2.png", 320, 240, 1);
    setScale(&temp.obj.t, 0.5);

    //VISUAL
    png_to_gl_texture(&ombre, "/rd/ombre.png");
    png_to_gl_texture(&spirit_base, "/rd/inside_blue_2.png");
    setScale(&spirit_base, 0.5);

    spirit_particule = createObject("/rd/spirit_particule.png", -1000, -1000, 1);
    //setScale(&spirit_particule.t, 0.5);
    setUV(&spirit_particule.t, 0.125, 1);
    setAnim(&spirit_particule.t, 0);
    spirit_particule.cFrame = 0;
    spirit_particule.frames = 7;
    spirit_particule.z = 8;
    spirit_particule.t.a = 0.6;

    //SOUND
    //click_sfx = snd_sfx_load("/rd/neg2.wav");

    //null_sfx[0] = snd_sfx_load("/rd/neg1.wav");
    //null_sfx[1] = snd_sfx_load("/rd/neg2.wav");
    //null_sfx[2] = snd_sfx_load("/rd/neg3.wav");

    //click_sfx[0] = snd_sfx_load("/rd/goodshit_3.wav");
    //click_sfx[1] = snd_sfx_load("/rd/goodshit_4.wav");
    //click_sfx[2] = snd_sfx_load("/rd/goodshit_5.wav");

    //DATA
    temp.questID = 0;
    strcpy(temp.questName, "");
    strcpy(temp.questDesc, "");
    temp.obj.z = 10;
    temp.cSpeed = 3;
    temp.cont = maple_enum_type(playerNum, MAPLE_FUNC_CONTROLLER);
    p1.state = (cont_state_t *)maple_dev_status(p1.cont);

    temp.inventorySize = 0;
    temp.inventory = malloc(sizeof(gameObject) * MAX_ITEM);
    if(temp.inventory == 0)
      setParam(3, "Inventory Malloc Fail");

    //BOOTLEG.
    temp.inventory[0] = createObject("/rd/spirit_base_spin.png", 0, 0 ,1);
    setUV(&temp.inventory[0].t, 0.125, 1);
    setAnim(&temp.inventory[0].t, 0);
    temp.inventory[0].cFrame = 0;
    temp.inventory[0].frames = 7;
    setScale(&temp.inventory[0].t, 0.5);
    temp.currentItem = &temp.inventory[0];
    return(temp);
}

void        movePlayer() {
  int cursorSpeed = p1.cSpeed;

  if (game_state == EXPLORATION || game_state == ENIGME) {
    if (p1.state->buttons & CONT_DPAD_DOWN)
      p1.obj.y -= cursorSpeed;
    if (p1.state->buttons & CONT_DPAD_UP)
      p1.obj.y += cursorSpeed;
    if (p1.state->buttons & CONT_DPAD_LEFT)
      p1.obj.x -= cursorSpeed;
    if (p1.state->buttons & CONT_DPAD_RIGHT)
      p1.obj.x += cursorSpeed;

    p1.obj.x += (int)p1.state->joyx / (128 / p1.cSpeed);
    p1.obj.y -= (int)p1.state->joyy / (128 / p1.cSpeed);

    if (p1.obj.x > currentScene->mapSize[0])
      p1.obj.x -= cursorSpeed;
    if (p1.obj.x < 0)
      p1.obj.x += cursorSpeed;
    if (p1.obj.y > currentScene->mapSize[1])
      p1.obj.y -= cursorSpeed;
    if (p1.obj.y < 0)
      p1.obj.y += cursorSpeed;
  }

  setFloat(2, p1.state->joyx);

  if (game_state == EXPLORATION) {
    direction[0] = 320 - displayPos[0] - p1.obj.x;
    direction[1] = 240 - displayPos[1] - p1.obj.y;

    velocity[0] = direction[0] / 100 * 2.5;
    velocity[1] = direction[1] / 100 * 2.5;

    displayPos[0] += velocity[0];
    displayPos[1] += velocity[1];

    velocity[0] *= 0.99;
    velocity[1] *= 0.99;
  }
}

void        updateController() {
  p1.cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER);

  if (p1.cont)
    p1.state = (cont_state_t *)maple_dev_status(p1.cont);
}

void        updateItem() {
  /*
  if(buttonPressed(CONT_B))
    dropItem();
  switchItem();
  */

  if(p1.currentItem != NULL) {
    p1.currentItem->x = p1.obj.x;
    p1.currentItem->y = p1.obj.y;
  }
}

void        updatePlayer() {
  //LUA
  LUA_updatePlayer();

  //ENGINE
  updateController();
  updateItem();
  movePlayer();

  //GAME ACTION
  if(buttonPressed(CONT_START))
    toggleMenu();

  toggleDebug(p1.state);
}

//MIGHT HAVE SOME MEMORY PROBLEM HERE
void        addItem(gameObject *target, char *path) {
  if(p1.inventorySize < MAX_ITEM && target->active == 1) {
    int i = p1.inventorySize + 1;
    p1.inventory[i] = *target;
    png_to_gl_texture(&p1.inventory[i].t, path);
    p1.inventory[i].name = target->name;
    p1.inventory[i].t.w = p1.inventory[i].t.h = 32;
    target->active = target->t.a = 0;
    p1.inventorySize += 1;
  }
}

/*
void        displayInventory() {
  for(int i = 0; i < p1.inventorySize; i++) {
    //if (i == cMenu)
      //setColor(1.0, 0.0, 0.0);
    //char *buf = inventory[i].name;
    //writeFont(buf, 80 - (strlen(buf)/2 * 10), 240 + (p1.inventorySize/2 * 20) - (20 * i));
    //resetColor();
    int _x = 320 + sin((2 * 3.1416) / p1.inventorySize * i) * 50;
    int _y = 240 + cos((2 * 3.1416) / p1.inventorySize * i) * 50;
    draw_textured_quad(&inventory->t, _x, _y);
  }
}
*/
void        setItem(gameObject *target) {
  if (hasItem())
    dropItem();

  p1.currentItem = target;
}

void        switchItem() {

  if (buttonPressed(CONT_X))
    currentItem++;
  if (currentItem > p1.inventorySize)
    currentItem = 0;

  p1.currentItem->active = p1.currentItem->visible = 0;
  p1.currentItem = &p1.inventory[currentItem];
  p1.currentItem->active = p1.currentItem->visible = 1;

  //char *buf = "";
  //sprintf(buf, "Item : %d/%d", currentItem, p1.inventorySize);
  //setString(2, buf);
}

void        dropItem() {
  if(p1.currentItem != NULL)
    p1.currentItem = NULL;
}

int         hasItem() {
  if(p1.currentItem != NULL)
    return(0);
  else
    return(1);
}

int noClickFlag = 0;
int noClickDelay = 0;
int         noClickSound() {
  if(noClickFlag) {
    //noClickDelay = frameCount + 120;
    //snd_sfx_play(null_sfx[rand()%3], 150, 128);
    //noClickFlag = 0;
  } else {
    if(frameCount > noClickDelay)
    noClickFlag = 1;
  }
}

int         clicked(gameObject *target, uint16 key) {
  if (p1.state->buttons & key)
  {
    if (over(target) && !(p1.pstate.buttons & key))
    {
      //snd_sfx_play(click_sfx, 150, 128);
      noClickFlag = 0;
      p1.pstate.buttons |= p1.state->buttons;
      return(1);
    }
    //else
    //if (!(p1.pstate.buttons & key))
      //noClickSound();
  }
  return(0);
}

int         pressed(gameObject *target, uint16 key) {
  if (p1.state->buttons & key)
  {
    if (over(target))
    {
      return(1);
    }
  }
  return(0);
}

int         buttonPressed(uint16 key) {
  if (p1.state->buttons & key)
  {
    if (!(p1.pstate.buttons & key))
    {
      p1.pstate.buttons |= p1.state->buttons;
      return(1);
    }
  }
  return(0);
}

void        toggleMenu() {
  if(game_state == MENU) {
    game_state = l_game_state;
  }
  else {
    l_game_state = game_state;
    game_state = MENU;
  }

}

int         over(gameObject *target) {
  float xSize = target->t.w * target->t.uSize;
  float ySize = target->t.h * target->t.vSize;
  float cX = p1.obj.x;
  float cY = p1.obj.y;

  if (target->active == 1) {
    if (  (cX > target->x-xSize/2) &&
          (cX < target->x+xSize/2) &&
          (cY > target->y-ySize/2) &&
          (cY < target->y+ySize/2))
          {
            return(1);
          }
          else
            return(0);
  }
  return(0);
}

int         inScreen(int x, int y) {
  int buffer = 50;
  int xS = 640;
  int yS = 480;

  if (   -x > displayPos[0] - xS - buffer
      && -x < displayPos[0] + buffer
      && -y > displayPos[1] - yS - buffer
      && -y < displayPos[1] + buffer)
      return (1);
  else
      return (0);
}

void        setPosition(int x, int y) {
  p1.obj.x = x;
  p1.obj.y = y;
  displayPos[0] = -x + 320;
  displayPos[1] = -y + 240;
}

char*       getPositionString() {
  sprintf(posString, "x%0.0f-y%0.0f", (double)p1.obj.x, (double)p1.obj.y);
  return(posString);
}

void        hideController(){
  p1.cSpeed = 0;
  p1.obj.visible = 0;
}

void        showController(){
  p1.cSpeed = 3;
  p1.obj.visible = 1;
}

void        drawCursor() {
  glLoadIdentity();
  glPushMatrix();
  glTranslated(displayPos[0], displayPos[1], displayPos[2]);
  if (p1.obj.visible) {
    if(p1.currentItem != NULL) {
      //particules updates
      nextFrame(&p1.inventory[0], 7);
      moveObject(&spirit_particule, p1.obj.x, p1.obj.y);
      nextFrame(&spirit_particule, 10);

      //spirit_core drawing
      p1.obj.dX += sin(frameCount/80.0f) * 2;
      p1.obj.dY += cos(frameCount/110.0f) * 5;
      p1.obj.angle = sin(frameCount/110.0f) * 15;
      drawObject(&p1.obj);
    }
  }
  glPopMatrix();
}

void        drawShadow() {
  if (p1.obj.visible) {
    draw_textured_quad(&ombre, p1.obj.x,  p1.obj.y - 50, -5);
  }
}
