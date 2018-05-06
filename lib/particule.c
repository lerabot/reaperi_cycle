#include <stdio.h>
#include <kos.h>
#include <png/png.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "particule.h"

pSystem createSystem(int size, vec3f_t pos){
  pSystem temp;

  temp.pNum = size;
  temp.p = malloc(sizeof(particule) * size); //est-ce ok pour la mémoire???
  temp.pos = pos;

  return(temp);
}

particule createParticule(vec3f_t pos){
  particule temp;

  temp.pos = pos;
  return(temp);
}


void freeSystem(pSystem *s){
  free(s->p);
}
