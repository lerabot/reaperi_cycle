/*
   KallistiOS 2.0.0

   pvr-texture.c
   (c)2014 Josh PH3NOM Pearson

   Load A PVR Texture to the PVR using Open GL
*/

#include <kos.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "gl_png.h"
#include <stdio.h>
#include <string.h>

#define PVR_HDR_SIZE 0x20

static GLuint PVR_TextureHeight(unsigned char *HDR);
static GLuint PVR_TextureWidth(unsigned char *HDR);
static GLuint PVR_TextureFormat(unsigned char *HDR);
static GLuint PVR_TextureColor(unsigned char *HDR);

/* Load a PVR texture file into memory, and then bind the texture to Open GL.
   fname is the name of the PVR texture file to be opened and read.
   isMipMapped should be passed as 1 if the texture contains MipMap levels, 0 otherwise.
   glMipMap should be passed as 1 if Open GL should calculate the Mipmap levels, 0 otherwise */
GLuint glTextureLoadPVR(char *fname, texture *t, unsigned char isMipMapped, unsigned char glMipMap) {
    FILE *tex = NULL;
    uint16 *TEX0 = NULL;
    uint8 HDR[PVR_HDR_SIZE];
    GLuint texID, texSize, texW, texH, texFormat, texColor;

    /* Open the PVR texture file, and get its file size */
    tex = fopen(fname, "rb");

    if(tex == NULL) {
        printf("FILE READ ERROR: %s\n", fname);

        while(1);
    }



    fseek(tex, 0, SEEK_END);
    texSize = ftell(tex) - PVR_HDR_SIZE;
    fseek(tex, 0, SEEK_SET);

    /* Read in the PVR texture file header */
    fread(HDR, 1, PVR_HDR_SIZE, tex);

    /* Extract some information from the PVR texture file header */
    texW = PVR_TextureWidth(HDR);
    texH = PVR_TextureHeight(HDR);
    texFormat = PVR_TextureFormat(HDR);
    texColor = PVR_TextureColor(HDR);


    /* Allocate Some Memory for the texture. If we are using Open GL to build the MipMap,
       we need to allocate enough space to hold the MipMap texture levels. */
    if(!isMipMapped && glMipMap)
        TEX0 = malloc(glKosMipMapTexSize(texW, texH));
    else
        TEX0 = malloc(texSize);

    fread(TEX0, 1, texSize, tex); /* Read in the PVR texture data */

    /* If requested, tell Open GL to build the MipMap levels for the texture. */
    /* For now, the input texture to gluBuild2DMipmaps must have a width and height divisible by two. */
    /* Also, color format is only set by the 2nd to last parameter, here as texColor.
       The color format may be one of the three: PVR_TXRFMT_RGB565, PVR_TXRFMT_ARGB1555, or PVR_TXRFMT_ARGB4444 */
    if(!isMipMapped && glMipMap)
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, texW, texH, GL_RGB, texColor, TEX0);

    /* Generate and bind a texture as normal for Open GL */
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);


    if(texFormat & PVR_TXRFMT_VQ_ENABLE)
        glCompressedTexImage2D(GL_TEXTURE_2D,
                               (isMipMapped || glMipMap) ? 1 : 0,
 	                       texFormat | texColor,
 	                       texW,
 	                       texH,
 	                       0,
 	                       texSize,
 	                       TEX0);
    else
        glTexImage2D(GL_TEXTURE_2D,
                     (isMipMapped || glMipMap) ? 1 : 0,
                     GL_RGB,
                     texW, texH,
                     0,
                     GL_RGB,
                     texFormat | texColor,
                     TEX0);

    free(TEX0);


    printf("%s", "Before Texture Data");
    fflush(stdout);

    t->id = texID;
    t->w = 256;
    t->h = 256;
    t->u = 0.f;
    t->v = 0.f;
    t->a = 1;
    t->uSize = t->vSize = 1.f;
    t->xScale = t->yScale = 1.f;
    t->format = texFormat;
    t->min_filter = t->mag_filter = GL_NEAREST;

    return texID;
}

static GLuint PVR_TextureColor(unsigned char *HDR) {
    switch((GLuint)HDR[PVR_HDR_SIZE - 8]) {
        case 0x00:
            return PVR_TXRFMT_ARGB1555; //(bilevel translucent alpha 0,255)

        case 0x01:
            return PVR_TXRFMT_RGB565;   //(non translucent RGB565 )

        case 0x02:
            return PVR_TXRFMT_ARGB4444; //(translucent alpha 0-255)

        case 0x03:
            return PVR_TXRFMT_YUV422;   //(non translucent UYVY )

        case 0x04:
            return PVR_TXRFMT_BUMP;     //(special bump-mapping format)

        case 0x05:
            return PVR_TXRFMT_PAL4BPP;  //(4-bit palleted texture)

        case 0x06:
            return PVR_TXRFMT_PAL8BPP;  //(8-bit palleted texture)

        default:
            return PVR_TXRFMT_RGB565;
    }
}

static GLuint PVR_TextureFormat(unsigned char *HDR) {
    switch((GLuint)HDR[PVR_HDR_SIZE - 7]) {
        case 0x01:
            return PVR_TXRFMT_TWIDDLED;                           //SQUARE TWIDDLED

        case 0x03:
            return PVR_TXRFMT_VQ_ENABLE;                          //VQ TWIDDLED

        case 0x09:
            return PVR_TXRFMT_NONTWIDDLED;                        //RECTANGLE

        case 0x0B:
            return PVR_TXRFMT_STRIDE | PVR_TXRFMT_NONTWIDDLED;    //RECTANGULAR STRIDE

        case 0x0D:
            return PVR_TXRFMT_TWIDDLED;                           //RECTANGULAR TWIDDLED

        case 0x10:
            return PVR_TXRFMT_VQ_ENABLE | PVR_TXRFMT_NONTWIDDLED; //SMALL VQ

        default:
            return PVR_TXRFMT_NONE;
    }
}

static GLuint PVR_TextureWidth(unsigned char *HDR) {
    return (GLuint)HDR[PVR_HDR_SIZE - 4] | HDR[PVR_HDR_SIZE - 3] << 8;
}

static GLuint PVR_TextureHeight(unsigned char *HDR) {
    return (GLuint)HDR[PVR_HDR_SIZE - 2] | HDR[PVR_HDR_SIZE - 1] << 8;
}

typedef struct {
	char	id[4];	// 'DTEX'
	short	width;
	short	height;
	int		type;
	int		size;
} header_t;

void load_dtex(const char* fn, texture *t){
   FILE* fp;
   header_t  hdr;
   fp = fopen(fn,"rb");

   //pvr_set_pal_format(PVR_PAL_ARGB8888);
   fread(&hdr,sizeof(hdr),1,fp);   // read in the header

   //Allocate texture memory
   //t->data = pvr_mem_malloc(hdr.size);

   //Temporary ram storage of texture
   void* temp = malloc(hdr.size);
   if(!temp)
    printf("%s out of memory.", fn);

   // Load texture into ram
   fread(temp,hdr.size,1,fp);

   // SQ copy into VRAM
   //pvr_txr_load(temp,t->data,hdr.size);

   GLuint texture_id;
   /*

 	 glGenTextures(1, &texture_id);
 	 glBindTexture(GL_TEXTURE_2D, texture_id);
 	 GLenum texture_format = GL_RGBA;
   GLenum t_color = hdr.type;
 	 glTexImage2D(GL_TEXTURE_2D, 0, texture_format, hdr.width, hdr.height, 0, texture_format, t_color, temp);
   */
   t->id = texture_id;
   t->w = hdr.width;
   t->h = hdr.height;
   t->format = hdr.type;
   t->u = 0.f;
   t->v = 0.f;
   t->a = 1;
   t->uSize = t->vSize = 1.f;
   t->xScale = 1.f;
   t->yScale = -1.f;
   t->min_filter = t->mag_filter = GL_NEAREST;

   //Free RAM
   free(temp);
   temp = NULL;
   fclose(fp);

   printf("%s loaded.", fn);
   fflush(stdout);

   /* Palette loading and management */
   /*
   if( ((t->format >> 27) & 7) > 4 ) {
         // Append palette suffix to filepath
         char pf[64];
         strcpy(pf,fn);
         strcat(pf,".pal");
         fp = fopen(pf,"rb");
         pal_header_t phdr;
         //read in the 8-byte header
         fread(&phdr,sizeof(pal_header_t),1,fp);

      if((t->format >>27) & 1 ){
      //4bbp
         //setup buffer
         void *palette = malloc(phdr.numcolors*4);
         Uint32 i;
         //Make entries readable to PVR
         Uint32* colours = (Uint32*)palette;
         //Load entries in to buffer
         fread(colours,phdr.numcolors*4,1,fp);
         //Load palette entries into correct location ( first 512 bank)
         for(i = Pindex4*16; i < (Pindex4*16) + phdr.numcolors;i++) {
            pvr_set_pal_entry(i,colours[i&15]);
         }
         //Set palette Number
         t->palette = Pindex4;
         t->format |=  PVR_TXRFMT_4BPP_PAL(Pindex4);
      printf("\n num%d  index%d",phdr.numcolors,Pindex4);

      //Increase palette index to prevent overwrite
         Pindex4++;
         //32 possible palettes in 512 bank
         if(Pindex4 == 32){
            Pindex4 = 0; // overwrite
         }
         colours = NULL;
              free(palette);

      ////////// 8PP PALETTE

      } else if((t->fmt >>27) & 2 ){
         void * palette = malloc(phdr.numcolors*4);
         Uint32 i;
         Uint32* colours = (Uint32*)palette;
         fread(colours,phdr.numcolors*4,1,fp);

         //Load palette entries into the second 512 bank
         for(i = (512 + Pindex8*256); i < (Pindex8*256 + 512) + phdr.numcolors;i++){
            pvr_set_pal_entry(i,colours[(i&255)]);
         }
         t->palette = Pindex8 | 0x80;
         t->fmt |=  PVR_TXRFMT_8BPP_PAL(Pindex8+2);
         Pindex8++;

         //Only 2 8-bit palettes can fit into second 512 bank
         if(Pindex8 == 2){
            Pindex8 = 0;
         }
         colours = NULL;
              free(palette);
      }
      fclose(fp);
   }
   */
}