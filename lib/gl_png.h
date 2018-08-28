#ifndef __GL_PNG_H__
#define __GL_PNG_H__

#include <stdio.h>
#include <kos.h>
#include <png/png.h>
#include <GL/gl.h>

typedef struct _texture {
	GLuint 		id;
	GLenum 		format;
	GLenum 		min_filter;
	GLenum 		mag_filter;
	GLenum		blend_source;
	GLenum		blend_dest;
	uint16_t 	w, h; // width / height of texture image
	int				size[2];
	float 		u, v; //uv COORD
	float 		uSize, vSize; // uvSize
	float 		xScale, yScale; //render scale
	float 		a; //alpha
	float 		light; //alpha
	float 		color[3];
	char  		path[32];

} texture;

/*
typedef struct _quads {
	float	vect[4][3];
	float color[3];
	int 	visible;

} quads;
*/

/* DTEX Image type - contains height, width, and data */
typedef struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
    GLenum internalFormat;
    GLboolean mipmapped;
    unsigned int dataSize;
} Image;

//loaders
int 	png_to_gl_texture(texture *tex, char *filename);
int 	dtex_to_gl_texture(texture *tex, char* filename);
int 	loadDtex(char *filename, Image *image);
int 	getAtlasData(texture *t, char *path);
void 	draw_textured_quad(texture *tex, float x, float y, float z);
void 	blackScreen(float a);
//set UV size
void 	setUV(texture *tex, float u, float v);
void 	setUVHex(texture *tex, float xSize, float ySize);


//set frame in sprite sheet
void 	setAnim(texture *tex, int a);
void 	flipU(texture *tex);
void  setAmbientLight(float r, float g, float b);
void 	resetAmbientLight();
void 	setLightType(int type);
void 	setScale(texture *tex, float scale);
void 	setPattern(texture *tex, int x, int y);

//quads


#endif
