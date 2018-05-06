#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include <kos.h>

void drawHex(texture *tex, float x, float y); //losange
void drawHexa(texture *tex, float x, float y); //hexagone
void initMap();
void drawMap(texture *tex, int x, int y); //map losange
void drawMap2(texture *tex, int x, int y); //map hexagone

//SHIT
void generateFloor(scene* self, int texNum);

#endif
