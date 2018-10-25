#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <kos.h>

void toggleDebug(cont_state_t *state);
void debugScreen();
void printString(char *string, int x, int y);
void setParam(int paramIndex, char *text);
void setString(int paramIndex, char *text);
void setInt(int paramIndex, uint32 i);
void printDir();
void setFloat(int paramIndex, float i);
void updateFrameTime(uint64_t new_frame_time);

#endif
