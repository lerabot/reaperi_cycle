#include <kos.h>
#include <stdlib.h>
#include <kos/img.h>
#include <png/png.h>
#include <GL/gl.h>
#include "../global_var.h"
#include "gl_png.h"
#include "gl_font.h"
#include "tilemap.h"
#include "debug_screen.h"

int rMap = 300;
int mapData2[300][300];

void generateFloor(scene* self, int texNum) {
  //setUV(&self->obj[texNum].t, 0.25, 0.25);
  //self->obj[text]
  //setScale(&self->obj[texNum].t, 0.25);
  self->floorTex = texNum;
  for (int j = 0; j < rMap; j++) {
    for (int i = 0; i < rMap; i++) {
      mapData2[j][i] = (rand() % 16);
    }
  }
}

void drawMap(texture *t, int x, int y) {
  int xPos, yPos, xOffset, yOffset;
  float xCenter, yCenter;
  float xTile = t->w * t->uSize * t->xScale;
  float yTile = t->h * t->vSize * t->yScale;
  int maxTile = 6;

  xPos = yPos = 0;

  xOffset = -displayPos[0] / xTile;
  yOffset = -displayPos[1] / yTile;

  int _i, _j;
  char *buf = "";
  for(int j = 0; j < maxTile; j++){
    for(int i = 0; i < maxTile; i++) {
      _i = i + xOffset + (xOffset%2);
      _j = j + yOffset;

      xPos = (_i * xTile) - xTile;
      yPos = (_j * yTile) - ((i%2)  * (yTile/2));

      setAnim(t, mapData2[_j][_i]);
      drawHex(t, xPos, yPos);
      //sprintf(buf, "%i", _i + (_j * maxTile));
      //writeFont(buf, xPos, yPos);
    }
  }
}

void drawHex(texture *tex, float x, float y) {
  //trouver les coord
  float texW = tex->w * tex->uSize * tex->xScale;
  float texH = tex->h * tex->vSize * tex->yScale;
  float x0 = x - texW;
  float y0 = y - texH / 2;
  float x1 = x + texW;
  float y1 = y + texH / 2;
  float u = tex->u;
  float v = tex->v;
  float xS = tex->uSize;
  float yS = tex->vSize;
  float z = -5.0;
  GLfloat material_ambient[] = {1.0, 1.0, 1.0, 1.0};

  GLfloat vertex_data[] = {
  	/* 2D Coordinate, texture coordinate */
  	x, y1, z,
  	x1, y, z,
  	x, y0, z,
  	x0, y, z
  };

  GLfloat uv_data[] = {
  	/* 2D Coordinate, texture coordinate */
  	u, v + yS,
  	u + xS, v + yS,
  	u + xS, v,
  	u, v
  };

  GLfloat normal_data[] = {
  	/* 2D Coordinate, texture coordinate */
  	0.0, 0.0, 1.0,
  	0.0, 0.0, 1.0,
  	0.0, 0.0, 1.0,
  	0.0, 0.0, 1.0
  };

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, tex->id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tex->min_filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tex->mag_filter);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, vertex_data);
  glTexCoordPointer(2, GL_FLOAT, 0, uv_data);
  glNormalPointer(GL_FLOAT, 0, normal_data);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material_ambient);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDrawArrays(GL_QUADS, 0, 4);

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
}