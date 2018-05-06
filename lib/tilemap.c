#include <kos.h>
#include <stdlib.h>
#include <kos/img.h>
#include <png/png.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "../global_var.h"
#include "gl_png.h"
#include "gl_font.h"
#include "tilemap.h"
#include "debug_screen.h"

int rMap = 300;
int mapData2[300][300];

void generateFloor(scene* self, int texNum) {
  setUV(&self->obj[texNum].t, 0.25, 0.25);
  self->floorTex = texNum;
  for (int j = 0; j < rMap; j++) {
    for (int i = 0; i < rMap; i++) {
      mapData2[j][i] = (rand() % 16);
    }
  }
}

void drawMap(texture *t, int x, int y) {
  int xPos, yPos, xCenter, yCenter, xOffset, yOffset;
  int xTile = t->w * t->uSize * t->xScale;
  int yTile = t->h * t->vSize * t->xScale / 2;
  int maxTile = 15;

  xPos = yPos = 0;
  xCenter = (xTile * maxTile/2) + xTile; //LEGIT!
  yCenter = (yTile * maxTile/2) + yTile; //LEGIT

  xOffset = (-displayPos[0]/2 / xTile);
  yOffset = (-displayPos[1]/2 / yTile);

  int _i, _j;
  for(int j = 0; j < maxTile; j++){
    for(int i = 0; i < maxTile; i++) {
      _i = i + xOffset;
      _j = j + yOffset;
      xPos = ((_i) * xTile) + ((j + xOffset) * xTile) - xCenter;
      yPos = ((_j) * yTile) - ((i - yOffset) * yTile) + yCenter;
      setAnim(t, mapData2[_i - yOffset + 100][_j + xOffset + 100]);
      drawHex(t, xPos, yPos);
      //snprintf(buf, 8, "%u", i + (j * mapSize));
      //snprintf(buf, 8, "i%u j%u", _i - yOffset, _j + xOffset);
      //writeFont(buf, xPos, yPos);
    }
  }
}

void drawMap2(texture *t, int x, int y) {
  int xPos, yPos, xMap, yMap;
  int mapSize = (640 / t->size[0]) + 5;
  int tileSize = t->h * t->vSize;

  xPos = yPos = 0;
  xMap = (int)(-displayPos[0] - t->w * t->uSize) / t->w * t->uSize;
  yMap = (int)(-displayPos[1] - t->h * t->vSize) / t->h * t->vSize;

  setInt(2, mapSize);
  setInt(3, yMap);

  for(int j = 0; j < mapSize; j++){
    for(int i = 0; i < mapSize; i++) {
      xPos = ((xMap + i) * tileSize*0.86) + (((yMap + j) % 2) * tileSize*0.43) + x;
      yPos = ((yMap + j) * tileSize) - ((yMap + j) * tileSize/4) + y;
      //setAnim(t, mapData[i + xMap][j + yMap]);
      setAnim(t, mapData2[(i + xMap) + (j + yMap)]);
      //setAnim(t, 1);
      //setAnim(t, (i * 3 + xMap) + (j * i/2 + yMap));
      //setAnim(t, rand()%20);
      drawHexa(t, xPos, yPos);
    }
  }
}

void drawHex(texture *tex, float x, float y) {
  //trouver les coord
  float texW = tex->w * tex->uSize * tex->xScale;
  float texH = tex->h * tex->vSize * tex->yScale;
  float x0 = x - texW; //LA WIDTH D'UNE TILE = tex->Size[0] * 2;
  float y0 = y - texH / 2;
  float x1 = x + texW;
  float y1 = y + texH / 2;
  float u = tex->u;
  float v = tex->v;
  float xS = tex->uSize;
  float yS = tex->vSize;

  //pack les coord
  float vertex_data[] = {
  	/* 2D Coordinate, texture coordinate */
  	x0, y,  u, v + yS,
  	x, y1,  u + xS, v + yS,
  	x, y0,  u , v,
    x1, y,  u + xS, v
  };

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, tex->id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glVertexPointer  (2, GL_FLOAT, 4 * sizeof(float), vertex_data);
  glTexCoordPointer(2, GL_FLOAT, 4 * sizeof(float), vertex_data + 2);

  //trouver un facon de mettre le
  glColor4f(tex->light,tex->light,tex->light, tex->a);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
