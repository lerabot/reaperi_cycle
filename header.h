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
#include <GL/glut.h>
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

/////////////////////////
//test shit

#include "scene_menu.h"
#include "scene_temple.h"
#include "scene_soussol.h"
#include "scene_jardin.h"
#include "scene_desert.h"
#include "scene_test.h"
