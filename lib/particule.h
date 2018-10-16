#ifndef __PARTICULE_H__
#define __PARTICULE_H__

#include <kos.h>
#include <png/png.h>
#include "gl_png.h"
#include <dc/vec3f.h>

typedef struct part {
  vec3f_t pos;
  vec3f_t vel;

} particule;

typedef struct part_system {
  int pNum; //particule number
  particule *p; //pointeur vers un array de particules
  vec3f_t pos;
  texture t; //est-ce que ca devrais etre un pointeur de texture?

} pSystem;

pSystem createSystem(int size, vec3f_t pos);
particule createParticule(vec3f_t pos);
void applyForce(particule *part);
void updateSystem(pSystem *s);
void drawSystem(pSystem *s);
void freeSystem(pSystem *s);

#endif
