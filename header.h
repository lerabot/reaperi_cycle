#include <kos.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
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
#include "gl_font.h"
#include "debug_screen.h" //vital
#include "game_object.h" //vital
#include "gl_png.h"
#include "scene.h"
#include "tilemap.h"
#include "player.h"
#include "quest.h"
#include "lua_binds.h"
#include "dreamroqlib.h"
#include "vmu.h"

/////////////////////////////
//Game States
#define EXPLORATION 1
#define DIALOG 2
#define INVENTORY 3
#define MENU 4
#define ENIGME 5

//////////////////////////////
//Scenes

#include "scene_menu.h"
#include "scene_temple.h"
#include "scene_soussol.h"
#include "scene_jardin.h"
#include "scene_desert.h"
#include "scene_test.h"
#include "scene_hideout.h"
#include "scene_illusion.h"

#define MAP_NOID            0
#define MAP_TEMPLE          1
#define MAP_SOUSSOL         2
#define MAP_DESERT          3
#define MAP_JARDIN          4
#define MAP_HIDEOUT         77

///////////////////////////////
//Quests

#define QUEST_NUMBER        50
//MAIN STORYLINE 0-50
#define NO_QUEST            0
#define QUEST_INTRO         1
#define QUEST_SCROLL        2
#define QUEST_DECYPHER      3
#define QUEST_GOLEMSPIT     4

//EXTRA QUEST 50-???
#define QUEST_MARCHANT_1    50
