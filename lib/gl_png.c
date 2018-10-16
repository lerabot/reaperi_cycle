#include <stdio.h>
#include <string.h>
#include <png/png.h>
#include <GL/gl.h>
#include <GL/glkos.h>
#include <GL/glext.h>
#include <GL/glu.h>

#include "gl_png.h"
#include "debug_screen.h"
#include "../global_var.h"

#define CLEANUP(x) { ret = (x); goto cleanup; }

float light = 1;
int 	light_type = 0;
GLfloat material_ambient[] = {1.0, 1.0, 1.0, 1.0};
GLfloat material_emit[] = {1.0, 0.0, 1.0, 1.0};

int png_to_gl_texture(texture *tex, char *filename) {
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
	tex->color[0] = tex->color[1] = tex->color[2] = 1.0f;
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

// Load Bitmaps And Convert To Textures
int dtex_to_gl_texture(texture *tex, char* filename) {
    // Load Texture
    Image *image1;

    // allocate space for texture
    image1 = (Image *) malloc(sizeof(Image));
    if (image1 == NULL) {
      	setParam(3, "No mem for DTEX");
				return(0);
    }

    if (!loadDtex(filename, image1)) {
        //ERROR!
				setParam(3, "Couldn't load DTEX");
				return(0);
    }

    // Create Texture
		GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture

		/*
    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image,
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glCompressedTexImage2DARB(GL_TEXTURE_2D, 0, image1->internalFormat, image1->sizeX, image1->sizeY, 0,image1->dataSize, image1->data
    );
		*/

		//GLenum texture_format = (color_type & PNG_COLOR_MASK_ALPHA) ? GL_RGBA : GL_RGB;
		GLenum format = GL_RGBA;

		if (image1->internalFormat == GL_UNSIGNED_SHORT_1_5_5_5_REV_TWID_KOS){
			format = GL_BGRA;
			}

		glTexImage2D(GL_TEXTURE_2D, 0,
				GL_RGBA, image1->sizeX, image1->sizeY, 0,
				format, image1->internalFormat, image1->data);

		tex->id = texture_id;
		tex->w = image1->sizeX;
		tex->h = image1->sizeY;
		tex->u = 0.f;
		tex->v = 0.f;
		tex->a = tex->light = 1;
		tex->color[0] = tex->color[1] = tex->color[2] = 1.0f;
		tex->uSize = tex->vSize = 1.f;
		tex->xScale = tex->yScale = 1.f;
		tex->format = image1->internalFormat;
		tex->min_filter = tex->mag_filter = GL_LINEAR;
		tex->blend_source = GL_SRC_ALPHA;
		tex->blend_dest = GL_ONE_MINUS_SRC_ALPHA;
		strcpy(tex->path, filename);

		//free(image1);
		return(1);
};

int loadDtex(char *filename, Image *image) {
    FILE* file = NULL;

    // make sure the file is there.
    if ((file = fopen(filename, "rb")) == NULL)
    {
      	setParam(3, "DTEX : Couldn't find file");
        return 0;
    }

    struct {
        char	id[4];	// 'DTEX'
        GLushort	width;
        GLushort	height;
        GLuint		type;
        GLuint		size;
    } header;

    fread(&header, sizeof(header), 1, file);

    GLboolean twiddled = (header.type & (1 << 26)) < 1;
    GLboolean compressed = (header.type & (1 << 30)) > 0;
    GLboolean mipmapped = (header.type & (1 << 31)) > 0;
    GLboolean strided = (header.type & (1 << 25)) > 0;
    GLuint format = (header.type >> 27) & 0b111;

    image->data = (char *) malloc (header.size);
    image->sizeX = header.width;
    image->sizeY = header.height;
    image->dataSize = header.size;

    GLuint expected = 2 * header.width * header.height;
    GLuint ratio = (GLuint) (((GLfloat) expected) / ((GLfloat) header.size));

    fread(image->data, image->dataSize, 1, file);
    fclose(file);

		if(compressed) {
				if(twiddled) {
						switch(format) {
								case 0: {
										if(mipmapped) {
												image->internalFormat = GL_COMPRESSED_ARGB_1555_VQ_MIPMAP_TWID_KOS;
										} else {
												image->internalFormat = GL_COMPRESSED_ARGB_1555_VQ_TWID_KOS;
										}
								} break;
								case 1: {
										if(mipmapped) {
												image->internalFormat = GL_COMPRESSED_RGB_565_VQ_MIPMAP_TWID_KOS;
										} else {
												image->internalFormat = GL_COMPRESSED_RGB_565_VQ_TWID_KOS;
										}
								} break;
								case 2: {
										if(mipmapped) {
												image->internalFormat = GL_COMPRESSED_ARGB_4444_VQ_MIPMAP_TWID_KOS;
										} else {
												image->internalFormat = GL_COMPRESSED_ARGB_4444_VQ_TWID_KOS;
										}
								}
								break;
								default:
										fprintf(stderr, "Invalid texture format");
										return 0;
						}
				} else {
						switch(format) {
								case 0: {
										if(mipmapped) {
												image->internalFormat = GL_COMPRESSED_ARGB_1555_VQ_MIPMAP_KOS;
										} else {
												image->internalFormat = GL_COMPRESSED_ARGB_1555_VQ_KOS;
										}
								} break;
								case 1: {
										if(mipmapped) {
												image->internalFormat = GL_COMPRESSED_RGB_565_VQ_MIPMAP_KOS;
										} else {
												image->internalFormat = GL_COMPRESSED_RGB_565_VQ_KOS;
										}
								} break;
								case 2: {
										if(mipmapped) {
												image->internalFormat = GL_COMPRESSED_ARGB_4444_VQ_MIPMAP_KOS;
										} else {
												image->internalFormat = GL_COMPRESSED_ARGB_4444_VQ_KOS;
										}
								}
								break;
								default:
										fprintf(stderr, "Invalid texture format");
										return 0;
						}
				}
		} else {
			if(twiddled) {
					switch(format) {
							case 0: {
								image->internalFormat = GL_UNSIGNED_SHORT_1_5_5_5_REV_TWID_KOS;
								break;
							}
							case 1: {
								image->internalFormat = GL_UNSIGNED_SHORT_5_6_5_TWID_KOS;
								break;
							}
							case 2: {
								image->internalFormat = GL_UNSIGNED_SHORT_4_4_4_4_REV_TWID_KOS;
								break;
							}
							default:
									fprintf(stderr, "Invalid texture format");
									return 0;
					}
			} else {
					switch(format) {
							case 0: {
									image->internalFormat = GL_UNSIGNED_SHORT_1_5_5_5_REV;
							}
							break;
							case 1: {
									image->internalFormat = GL_UNSIGNED_SHORT;
									}
							break;
							case 2: {
									image->internalFormat = GL_UNSIGNED_SHORT_4_4_4_4_REV;
									}
							break;
							default:
									fprintf(stderr, "Invalid texture format");
									return 0;
					}
			}
		}
		char *m = "";
		sprintf(m, "Twid=%u Format=%u", twiddled, format);
		setParam(4, m);
    // we're done.
    return 1;
}

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

void setAmbientLight(float r, float g, float b){
	material_ambient[0] = r;
	material_ambient[1] = g;
	material_ambient[2] = b;
}

void resetAmbientLight() {
	material_ambient[0] = material_ambient[1] = material_ambient[2] = 1.0;
}

void setLightType(int type) {
	light_type = type;
}

void draw_textured_quad(texture *tex, float x, float y, float z) {
	GLfloat texW = tex->w * tex->uSize * tex->xScale;
	GLfloat texH = tex->h * tex->vSize * tex->yScale;
	//texW = 10;
	//texH = 10;
	GLfloat x0 = x - texW / 2;
	GLfloat y0 = y - texH / 2;
	GLfloat x1 = x + texW / 2;
	GLfloat y1 = y + texH / 2;
	GLfloat u = tex->u;
	GLfloat v = tex->v;
	GLfloat xS = tex->uSize;
	GLfloat yS = tex->vSize;


	GLfloat vertex_data[] = {
		/* 2D Coordinate, texture coordinate */
		x0, y1, z,
		x1, y1, z,
		x1, y0, z,
		x0, y0, z
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

	GLfloat color_data[] = {
		/* 2D Coordinate, texture coordinate */
		tex->color[0], tex->color[1], tex->color[2], tex->a,
		tex->color[0], tex->color[1], tex->color[2], tex->a,
		tex->color[0], tex->color[1], tex->color[2], tex->a,
		tex->color[0], tex->color[1], tex->color[2], tex->a
	};

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex->id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tex->min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tex->mag_filter);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	//glEnableClientState(GL_COLOR_MATERIAL);

	glVertexPointer			(3, GL_FLOAT, 0, vertex_data);
	glTexCoordPointer		(2, GL_FLOAT, 0, uv_data);
	glNormalPointer			(GL_FLOAT, 0, normal_data);
	glColorPointer			(4, GL_FLOAT, 0, color_data);
	//glColorMaterial			(GL_FRONT_AND_BACK, GL_AMBIENT);
	//glMaterialfv(GL_FRONT, GL_EMISSION, material_ambient);

	/*
	switch (light_type) {
		case 0:
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material_ambient);
			break; //normal case
		case 1:
			glMaterialfv(GL_FRONT, GL_EMISSION, material_ambient);
			break; //text case
	}
	*/

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	//glDisableClientState(GL_COLOR_MATERIAL);
}

void blackScreen(float a) {
	float x0 = -200;
	float y0 = 0;
	float x1 = 1000;
	float y1 = 480;

	float z = 20;

	GLfloat vertex_data[] = {
		/* 2D Coordinate, texture coordinate */
		x0, y1, z,
		x1, y1, z,
		x1, y0, z,
		x0, y0, z
	};

	GLfloat normal_data[] = {
		/* 2D Coordinate, texture coordinate */
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0
	};

	GLfloat color_data[] = {
		/* 2D Coordinate, texture coordinate */
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer		(3, GL_FLOAT, 0, vertex_data);
	glColorPointer		(4, GL_FLOAT, 0, color_data);
	glNormalPointer		(GL_FLOAT, 0, normal_data);

	//glColorMaterial		(GL_FRONT_AND_BACK, GL_AMBIENT);
	glMaterialfv			(GL_FRONT, GL_EMISSION, material_ambient);
	glBlendFunc				(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays			(GL_QUADS, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
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
