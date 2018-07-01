#include <kos.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <kos/string.h>
#include <stdio.h>
#include <png/png.h>
#include <zlib/zlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <malloc.h>
#include <oggvorbis/sndoggvorbis.h>
#include <mp3/sndserver.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

///////////////////////
//game related
#include "global_var.h"
#include "utils.h"
#include "lib/gl_font.h"
#include "lib/debug_screen.h" //vital
#include "lib/game_object.h" //vital
#include "lib/gl_png.h"
#include "lib/scene.h"
#include "lib/tilemap.h"
#include "lib/player.h"
#include "lib/particule.h"
#include "lib/lua_binds.h"
#include "lib/dreamroqlib.h"

/////////////////////////
//scenes

#define MAP_NOID 0
#define MAP_TEMPLE 1
#define MAP_SOUSSOL 2
#define MAP_DESERT 3
#define MAP_JARDIN 4
#define MAP_HIDEOUT 77

//MAIN STORYLINE 0-50
#define NO_QUEST 0
#define QUEST_INTRO 1
#define QUEST_SCROLL 2

//EXTRA QUEST 50-???
#define QUEST_MARCHANT_1 50

#include "scene_menu.h"
#include "scene_temple.h"
#include "scene_soussol.h"
#include "scene_jardin.h"
#include "scene_desert.h"
#include "scene_test.h"
