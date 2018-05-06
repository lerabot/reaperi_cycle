#include <stdio.h>
#include <string.h>
#include <kos.h>
#include <kos/img.h>
#include <png/png.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <kmg/kmg.h>
#include "gl_png.h"
#include "debug_screen.h"
#include "../global_var.h"

#define CLEANUP(x) { ret = (x); goto cleanup; }

float light = 1;
GLfloat highlight[] = {1, 1, 1};

int png_to_gl_texture(texture * tex, char const * const filename) {
	int ret = 0;
	FILE * file = 0;
	uint8_t * data = 0;
	png_structp parser = 0;
	png_infop info = 0;
	png_bytep * row_pointers = 0;

	png_uint_32 w, h;
	int bit_depth;
	int color_type;


	if(!tex || !filename) {
		CLEANUP(1);
	}

	file = fopen(filename, "rb");
	if(!file) {
		CLEANUP(2);
	}

	parser = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	if(!parser) {
		CLEANUP(3);
	}

	info = png_create_info_struct(parser);
	if(!info) {
		CLEANUP(4);
	}

	if(setjmp(png_jmpbuf(parser))) {
		CLEANUP(5);
	}

	png_init_io(parser, file);
	png_read_info(parser, info);
	png_get_IHDR(parser, info, &w, &h, &bit_depth, &color_type, 0, 0, 0);

	if((w & (w-1)) || (h & (h-1)) || w < 8 || h < 8) {
		CLEANUP(6);
	}

	if(png_get_valid(parser, info, PNG_INFO_tRNS) || (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) || color_type == PNG_COLOR_TYPE_PALETTE) {
		png_set_expand(parser);
	}
	if(bit_depth == 16) {
		png_set_strip_16(parser);
	}
	if(color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
		png_set_gray_to_rgb(parser);
	}
	png_read_update_info(parser, info);

	int rowbytes = png_get_rowbytes(parser, info);
	rowbytes += 3 - ((rowbytes-1) % 4); // align to 4 bytes

	data = malloc(rowbytes * h * sizeof(png_byte) + 15);
	if(!data) {
		setParam(8,"no more data :(");
		CLEANUP(7);

	}

	row_pointers = malloc(h * sizeof(png_bytep));
	if(!row_pointers) {
		setParam(9,"no more row :(");
		CLEANUP(8);
  }

	// set the individual row_pointers to point at the correct offsets of data
	for(png_uint_32 i = 0; i < h; ++i) {
		row_pointers[h - 1 - i] = data + i * rowbytes;
	}

	png_read_image(parser, row_pointers);

	// Generate the OpenGL texture object
	GLuint texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	GLenum texture_format = (color_type & PNG_COLOR_MASK_ALPHA) ? GL_RGBA : GL_RGB;
	//GLenum texture_format = GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, texture_format, w, h, 0, texture_format,   GL_UNSIGNED_BYTE, data);

	tex->id = texture_id;
	tex->w = w;
	tex->h = h;
	tex->u = 0.f;
	tex->v = 0.f;
	tex->a = tex->light = 1;
	tex->uSize = tex->vSize = 1.f;
	tex->xScale = tex->yScale = 1.f;
	tex->format = texture_format;
	tex->min_filter = tex->mag_filter = GL_LINEAR;
	tex->blend_source = GL_SRC_ALPHA;
	tex->blend_dest = GL_ONE_MINUS_SRC_ALPHA;
	strcpy(tex->path, filename);

cleanup:
	if(parser) {
		png_destroy_read_struct(&parser, info ? &info : 0, 0);
	}

	if(row_pointers) {
		free(row_pointers);
	}

	if(data) {
		free(data);
	}

	if(file) {
		fclose(file);
	}

	return ret;
}
/*
int kmg_to_gl_texture(texture * tex, char const * const filename) {
		int ret = 0;
		kos_img_t img;
		pvr_ptr_t rv;

		if(kmg_to_img(filename, &img)) {
			printf("Failed to load image file: %s\n", filename);
			return NULL;
		}

		if(!(rv = pvr_mem_malloc(img.byte_count))) {
			printf("Couldn't allocate memory for texture!\n");
			//kos_img_free(&img, 0);
			return NULL;
		}
		//pvr_txr_load_kimg(&img, rv, 0);
		//kos_img_free(&img, 0);

		// Generate the OpenGL texture object
		GLuint texture_id;
		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);
		//GLenum texture_format = (color_type & PNG_COLOR_MASK_ALPHA) ? GL_RGBA : GL_RGB;
		GLenum texture_format = GL_RGB;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.w, img.h, 0, GL_RGBA,   GL_UNSIGNED_BYTE, img.data);

		tex->id = texture_id;
		tex->w = img.w;
		tex->h = img.h;
		tex->u = 0.f;
		tex->v = 0.f;
		tex->a = 1;
		tex->uSize = tex->vSize = 1.f;
		tex->xScale = tex->yScale = 1.f;
		tex->format = GL_RGBA;
		tex->min_filter = tex->mag_filter = GL_NEAREST;

		return ret;
}
*/


int getAtlasData(texture *t, char *path) {
  lua_getglobal(t_data, "loadJSON");
  lua_pcall(t_data, 0, 1, 0);
  lua_settop(t_data, 0);
  lua_getglobal(t_data, "getTextureData");
  lua_pushstring(t_data, path);
  lua_pcall(t_data, 1, 4, 0);

  t->u = lua_tonumber(t_data, 1);
  t->v = lua_tonumber(t_data, 2);
  t->uSize = lua_tonumber(t_data, 3);
  t->vSize = lua_tonumber(t_data, 4);
	/*
	setFloat(0, t->u);
	setFloat(1, t->v);
	setFloat(2, t->uSize);
	setFloat(3, t->vSize);
	*/
  lua_pop(t_data, 4);
  return(1);
}

void setUV(texture *tex, float u, float v){
	if (u == 0)
		u = 1;
	if (v == 0)
		v = 1;

	tex->uSize = u;
	tex->vSize = v;
}

void setUVHex(texture *tex, float xSize, float ySize){
	tex->uSize = xSize;
	tex->vSize = ySize;
}

void flipU(texture *tex){
	tex->xScale = -1;
}

void setColor(float r, float g, float b){
	highlight[0] = r;
	highlight[1] = g;
	highlight[2] = b;
}

void resetColor() {
	highlight[0] = highlight[1] = highlight[2] = 1.0;
}

void setAnim(texture *tex, int a){ // exemple avec index
	float u = tex->uSize;
	float v = tex->vSize;
	if (tex->uSize == tex->vSize) {
		tex->u = (a % (int)(1 / u)) * u;
		tex->v = (a / (int)(1 / u)) * v;
	}
	else {
		//tex->u = (a % (int)(1 / u)) * u + ((a / (int)(1 / u)) * u/2);
		//tex->v = (a / (int)(1 / u)) * v - ((a / (int)(1 / u)) * v/4);
		tex->u = (a % (int)(1 / u)) * u;
		tex->v = (a / (int)(1 / u)) * v;
	}
}

void setPattern(texture *tex, int x, int y){
	tex->u = x;
	tex->v = y;
	tex->uSize = x;
	tex->vSize = y;
}

void setScale(texture *tex, float scale){
	tex->xScale = scale;
	tex->yScale = scale;
}

void setLight(texture *tex, float light){
	tex->light = light;
	if (tex->light > 1)
		tex->light = 1;
	if (tex->light < 0)
		tex->light = 0;
}

void draw_textured_quad(texture *tex, float x, float y) {
	float texW = tex->w * tex->uSize * tex->xScale;
	float texH = tex->h * tex->vSize * tex->yScale;
	float x0 = x - texW / 2;
	float y0 = y - texH / 2;
	float x1 = x + texW / 2;
	float y1 = y + texH / 2;
	float u = tex->u;
	float v = tex->v;
	float xS = tex->uSize;
	float yS = tex->vSize;

	float vertex_data[] = {
		/* 2D Coordinate, texture coordinate */
		x0, y1, 0.0, u, v + yS, 0.0, 0.0, -1.0,
		x0, y0, 0.0, u, v, 0.0, 0.0, -1.0,
		x1, y1, 0.0, u + xS, v + yS, 0.0, 0.0, -1.0,
		x1, y0, 0.0, u + xS, v, 0.0, 0.0, -1.0
	};
	/*
	float vertex_data[] = {

		x0, y1, 0.0, 0.0, u, v + yS,
		x0, y0, 0.0, 0.0, u, v,
		x1, y1, 0.0, 0.0, u + xS, v + yS,
		x1, y0, 0.0, 0.0, u + xS, v,
	};
	*/

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex->id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tex->min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tex->mag_filter);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer  	(3, GL_FLOAT, 8 * sizeof(float), vertex_data);
  glTexCoordPointer	(2, GL_FLOAT, 8 * sizeof(float), vertex_data + 3);
	glNormalPointer		(GL_FLOAT, 8 * sizeof(float), vertex_data + 5);

	glColor4f(tex->light * highlight[0],tex->light * highlight[1],tex->light * highlight[2], tex->a);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glBlendFunc(tex->blend_source, tex->blend_dest);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void blackScreen(float a) {
	float texW = 1000;
	float texH = 480;
	float x0 = -200;
	float y0 = 0;
	float x1 = 1000;
	float y1 = 480;
	float u = 0;
	float v = 0;
	float xS = 1;
	float yS = 1;

	float vertex_data[] = {
		/* 2D Coordinate, texture coordinate */
		x0, y1,  u, v + yS,
		x0, y0,  u, v,
		x1, y1,  u + xS, v + yS,
		x1, y0,  u + xS, v,
	};

	//glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer  (2, GL_FLOAT, 4 * sizeof(float), vertex_data);

	glColor4f(0.0f,0.0f,0.0f, a);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void draw_textured_quad2(texture *tex, float x, float y) {
	float texW = tex->w * tex->uSize * tex->xScale;
	float texH = tex->h * tex->vSize * tex->yScale;
	float x0 = x - texW / 2;
	float y0 = y - texH / 2;
	float x1 = x + texW / 2;
	float y1 = y + texH / 2;
	float u = tex->u;
	float v = tex->v;
	float xS = tex->uSize;
	float yS = tex->vSize;

	float vertex_data[] = {
		/* 2D Coordinate, texture coordinate */
		x0, y1, 0.0f,  u, v + yS,
		x0, y0, 0.0f,  u, v,
		x1, y1, 0.0f,  u + xS, v + yS,
		x1, y0, 0.0f,  u + xS, v,
	};

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex->id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tex->min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tex->mag_filter);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer  (3, GL_FLOAT, 4 * sizeof(float), vertex_data);
  glTexCoordPointer(2, GL_FLOAT, 6 * sizeof(float), vertex_data + 3);

	glColor4f(1.0f,1.0f,1.0f, tex->a);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
