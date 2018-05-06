#ifndef __GL_PVR_H__
#define __GL_PVR_H__

#include <stdio.h>
#include <kos.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "gl_png.h"

GLuint glTextureLoadPVR(char *fname, texture *t, unsigned char isMipMapped, unsigned char glMipMap);

void load_dtex(const char* fn, texture *t);

#endif