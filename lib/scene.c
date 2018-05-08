#include <kos.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <malloc.h>
#include "game_object.h"
#include "scene.h"
#include "tilemap.h"

//all maps
void updateLoading(){
  /*
  if (frameCount % 4 == 0)
    loadingScene.obj[0].currentFrame++;

  if (loadingScene.obj[0].currentFrame > 3)
    loadingScene.obj[0].currentFrame = 0;

  setSprite(&loadingScene.obj[0].t, loadingScene.obj[0].currentFrame, 1);
  */
}

void drawScene(scene *s){
  if (s != NULL)
  {
    setLight(&s->obj[s->floorTex].t, 0.25);
    if (s->floorTex != -1)
      drawMap(&s->obj[s->floorTex].t, s->mapSize[0]/2, s->mapSize[1]/2);

    for (int i = 0; i < s->objNum; i++){
      //setScale(&s->obj[i].t, 0.5);
      drawObject(&s->obj[i]);
    }


  }
}

void loadMapData(scene *self) {
  
}

void setMapInfo(scene *s, int x, int y, int xStart, int yStart){
  s->mapSize[0] = x;
  s->mapSize[1] = y;
  setPosition(xStart, yStart);
}

void freeScene2(scene *s){
  /*
  //DON'T FORGET THE FLOOR!
  for (int i = 0; i < sizeof(s->tex); i++){
      t = s->tex[i];
      glDeleteTextures(1, &s->obj[].t.id);
  }
  free(s->obj);
  mp3_stop();
  fs_romdisk_unmount("/rd");
  */
}
