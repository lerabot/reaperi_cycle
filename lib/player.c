#include <kos.h>
#include "player.h"
#include "../global_var.h"
#include "debug_screen.h"
#include "gl_font.h"
#include "game_object.h"

int     currentItem = 0;
int     edgeSize = 120;
float   velocity[2] = {0, 1};
float   direction[2] = {0, 1};

player      initPlayer(int playerNum) {
    player temp;
    //Texture
    temp.obj = createObject("", 320, 240, 1);
    setScale(&temp.obj.t, 0.5);

    //data
    temp.cSpeed = 3;
    temp.cont = maple_enum_type(playerNum, MAPLE_FUNC_CONTROLLER);
    temp.inventorySize = 0;
    temp.inventory = malloc(sizeof(gameObject) * MAX_ITEM);

    if(temp.inventory == 0)
      setParam(3, "Inventory Malloc Fail");

    temp.inventory[0] = createObject("/rd/cursor_2.png", 0, 0 ,1);
    setScale(&temp.inventory[0].t, 0.5);
    temp.currentItem = &temp.inventory[0];


    p1.state = (cont_state_t *)maple_dev_status(p1.cont);
    return(temp);
}

void updatePlayer() {
  updateController();
  updateItem();
}

void        updateController() {
  p1.cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER);
  int cursorSpeed = p1.cSpeed;

  if (p1.cont){
    p1.state = (cont_state_t *)maple_dev_status(p1.cont);

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

    if (p1.obj.x > currentScene->mapSize[0] - edgeSize * 1.5)
      p1.obj.x -= cursorSpeed;
    if (p1.obj.x < 0 + edgeSize * 1.5)
      p1.obj.x += cursorSpeed;
    if (p1.obj.y > currentScene->mapSize[1] - edgeSize)
      p1.obj.y -= cursorSpeed;
    if (p1.obj.y < 0 + edgeSize)
      p1.obj.y += cursorSpeed;

    direction[0] = 320 - displayPos[0] - p1.obj.x;
    direction[1] = 240 - displayPos[1] - p1.obj.y;

    velocity[0] = direction[0] / 100 * 2.5;
    velocity[1] = direction[1] / 100 * 2.5;

    displayPos[0] += velocity[0];
    displayPos[1] += velocity[1];

    velocity[0] *= 0.99;
    velocity[1] *= 0.99;

    toggleDebug(p1.state);
  }
}

void        updateItem() {
  if(buttonPressed(CONT_B))
    dropItem();

  switchItem();

  if(p1.currentItem != NULL) {
    p1.currentItem->x = p1.obj.x;
    p1.currentItem->y = p1.obj.y;
  }
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

void        displayInventory() {
  /*
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
  */
}

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

int         clicked(gameObject *target, uint16 key) {
  if (p1.state->buttons & key)
  {
    if (over(target) && !(p1.pstate.buttons & key))
    {
      p1.pstate.buttons |= p1.state->buttons;
      return(1);
    }
  }
  //else
    //p1.pstate.buttons |= p1.state->buttons; // MIGHT BE SLOW?
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
  //else
    //p1.pstate.buttons |= p1.state->buttons; // MIGHT BE SLOW?
  return(0);
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

void        hideController(){
  p1.obj.t.a = 0;
  p1.cSpeed = 0;
}

void        showController(){
  p1.obj.t.a = 1;
  p1.cSpeed = 3;
}

void        drawCursor() {
  if (p1.obj.visible) {
    //draw_textured_quad(&p1.obj.t, p1.obj.x, p1.obj.y);
    //writeFont(currentItem, p1.obj.x, p1.obj.y + 20);

    if(p1.currentItem != NULL)
      drawObject(p1.currentItem);

  }
}
