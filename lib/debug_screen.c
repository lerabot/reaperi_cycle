#include <kos.h>
//#include <fs_romdisk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "gl_font.h"
#include "../global_var.h"

char debugData[6][60];
char debugName[6][128];
char mem_buf[32];

float f_time[60] = {0};
int   f_index = 0;
float f_sum = 0;
float avgFrameTime = 0;

int visible = 0;
int release = 0;

void toggleDebug(cont_state_t *state) {
  if (state->buttons & CONT_Y)
  {
    if (release == 0)
    {
      if (visible == 0)
        visible = 1;
      else
        visible = 0;
      release = 1;
    }
  }
  else
    release = 0;

}

void setParam(int paramIndex, char *text) {
  strcpy(debugName[paramIndex], text);
}

void setString(int paramIndex, char *text) {
  strcpy(debugData[paramIndex], text);
}

void setInt(int paramIndex, uint i) {
  char *toString = "";
  sprintf(toString, "%u", i);
  strcpy(debugData[paramIndex], toString);
}

void setFloat(int paramIndex, double i) {
  char *toString = "";
  sprintf(toString, "%.3f", i);
  strcpy(debugData[paramIndex], toString);
}

void printString(char *string, int x, int y) {
  bfont_draw_str(vram_s + 640 * y + x, 640, 0, string);
}

void memoryInfo(){
  char  *mem_buf = "";
  double maxMem = 4077736;
  double avail = pvr_mem_available();
  double rem;

  rem = ((avail / maxMem) * 100);
  sprintf(mem_buf, "PVR:%0.2f/100", rem);
  setParam(0, mem_buf);
}

float minFPS = 30;
float maxFPS = 30;
float avgFPS, finalFPS;

void FPSinfo() {
  pvr_stats_t stats;
  char buf[128];

  pvr_get_stats(&stats);

  if(stats.frame_rate < minFPS && stats.frame_rate > 0)
    minFPS = stats.frame_rate;
  if(stats.frame_rate > maxFPS)
    maxFPS = stats.frame_rate;

  if(frameCount % 60 == 0){
    finalFPS = avgFPS/60;
    avgFPS = 0;
  }

  avgFPS += stats.frame_rate;

  sprintf(buf, "FPS:%.2f | Frame Time:%.2f", stats.frame_rate, avgFrameTime);
  printf("FPS:%.2f | Frame Time:%.2f\n", stats.frame_rate, avgFrameTime);
  setParam(1, buf);
}

void updateFrameTime(uint64_t new_frame_time) {
  f_sum -= f_time[f_index];
  f_sum += new_frame_time;
  f_time[f_index] = new_frame_time;

  if(f_index > 60)
    f_index = 0;
  else
    f_index++;

  //avgFrameTime = f_sum/60;
  avgFrameTime = new_frame_time;
}

int dirInfo = 0;
void printDir() {
  vfs_handler_t   rd;
  file_t          d;
  dirent_t        *dir;
  const char      *path = fs_getwd();

  path = "/rd";
  setParam(3, fs_getwd());
  if(dirInfo == 0) {
    char buf[512];
    //d = romdisk_open(rd, path, O_RDONLY  | O_DIR);
    d = fs_open(path, O_RDONLY  | O_DIR);
    if (d != -1) {
      printf("Found %s\n", path);
      strcpy(buf, "Found Romdisk\n");
      //while (dir = romdisk_readdir(d)) {
      while (dir = fs_readdir(d)) {
        printf("%s\n", dir->name);
        strcat(buf, dir->name);
        strcat(buf, "\n");
      }
    } else {
      printf("Couldn't find %s\n", path);
      strcpy(buf, "Couldn't find /rd\n");
    }
    fs_close(d);
    writeFont(buf, 16, 460 - (7 * 20));
    dirInfo = 1;
  }
}

void debugScreen() {
  int left = 16;
  int right = 16 * 32;
  int lineHeight = 20;
  char cursorPos[16];

  memoryInfo();
  FPSinfo();

  if (visible == 1)
  {
    //printDir();
    for (int i = 0; i < 6; i++)
    {

      if (debugName[i] != '\0')
        writeFont(debugName[i], 16, 460 - lineHeight * i);
      if (debugData[i] != '\0')
        writeFont(debugData[i], 512, 460 - lineHeight * i);

        /*
      if (debugName[i] != '\0')
        bfont_draw_str(vram_s + 640 * lineHeight * i + left, 640, 1, debugName[i]);
      if (debugData[i] != '\0')
        bfont_draw_str(vram_s + 640 * lineHeight * i + right, 640, 1, debugData[i]);
        */
    }
  }
}
