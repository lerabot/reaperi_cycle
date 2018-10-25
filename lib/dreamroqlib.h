/*
 * Dreamroq by Mike Melanson
 * Updates by lerabot for Reaperi Cycle
 *
 * This is the header file to be included in the programs wishing to
 * use the Dreamroq playback engine.
 */
#ifndef NEWROQ_H
#define NEWROQ_H

#include <kos.h>
#include <stdio.h>
#include <stdlib.h>

#define ROQ_VIDEO_DONE        -1
#define ROQ_SUCCESS           0
#define ROQ_FILE_OPEN_FAILURE 1
#define ROQ_FILE_READ_FAILURE 2
#define ROQ_CHUNK_TOO_LARGE   3
#define ROQ_BAD_CODEBOOK      4
#define ROQ_INVALID_PIC_SIZE  5
#define ROQ_NO_MEMORY         6
#define ROQ_BAD_VQ_STREAM     7
#define ROQ_INVALID_DIMENSION 8
#define ROQ_RENDER_PROBLEM    9
#define ROQ_CLIENT_PROBLEM    10

#define ROQ_RGB565 0
#define ROQ_RGBA   1

#define RoQ_INFO           0x1001
#define RoQ_QUAD_CODEBOOK  0x1002
#define RoQ_QUAD_VQ        0x1011
#define RoQ_JPEG           0x1012
#define RoQ_SOUND_MONO     0x1020
#define RoQ_SOUND_STEREO   0x1021
#define RoQ_PACKET         0x1030
#define RoQ_SIGNATURE      0x1084

#define CHUNK_HEADER_SIZE 8

#define LE_16(buf) (*buf | (*(buf+1) << 8))
#define LE_32(buf) (*buf | (*(buf+1) << 8) | (*(buf+2) << 16) | (*(buf+3) << 24))

#define MAX_BUF_SIZE (64 * 1024)

#define ROQ_CODEBOOK_SIZE 256
#define SQR_ARRAY_SIZE 256

int   playROQvideo(char* filename);
void  stopROQvideo();

/* The library calls this function when it has a frame ready for display. */
typedef int (*render_callback)(void *buf, int width, int height,
    int stride, int texture_height, int colorspace);

/* The library calls this function when it has pcm samples ready for output. */
typedef int (*audio_callback)(unsigned char *buf, int samples, int channels);

/* The library calls this function to ask whether it should quit playback.
 * Return non-zero if it's time to quit. */
typedef int (*quit_callback)();

/* The library calls this function to indicate that playback of the movie is
 * complete. */
typedef int (*finish_callback)(void);

typedef struct
{
    render_callback render_cb;
    audio_callback  audio_cb;
    quit_callback   quit_cb;
    finish_callback finish_cb;
} roq_callbacks_t;

struct roq_audio
{
     int pcm_samples;
     int channels;
     int position;
     short snd_sqr_array[SQR_ARRAY_SIZE];
     unsigned char pcm_sample[MAX_BUF_SIZE];
} roq_audio;

typedef struct
{
    int width;
    int height;
    int framerate;
    int mb_width;
    int mb_height;
    int mb_count;
    int alpha;

    int current_frame;
    unsigned char *frame[2];
    int stride;
    int texture_height;
    int colorspace;

    unsigned short cb2x2_rgb565[ROQ_CODEBOOK_SIZE][4];
    unsigned short cb4x4_rgb565[ROQ_CODEBOOK_SIZE][16];

    unsigned int cb2x2_rgba[ROQ_CODEBOOK_SIZE][4];
    unsigned int cb4x4_rgba[ROQ_CODEBOOK_SIZE][16];
} roq_state;

typedef struct
{
    FILE      *f;
    size_t    file_ret;
    uint64_t  frame_time;
    int       framerate;
    char      *filename;
    int        chunk_id;
    unsigned int chunk_size;
    unsigned int chunk_arg;
    roq_state   state;
    int         status;
    int         initialized;
    int         i, snd_left, snd_right;
    roq_callbacks_t callback;
} roq_video;

int dreamroq_play(char *filename, int colorspace, int loop,
    roq_callbacks_t *callbacks);

int dreamroq_play_frame(int loop);

int dreamroq_load(char* filename);

int render_cb(void *buf_ptr, int width, int height, int stride, int texture_height, int colorspace);
int audio_cb();
int quit_cb();
int finish_cb();
#endif  /* NEWROQ_H */
