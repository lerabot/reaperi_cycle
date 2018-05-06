#include <kos.h>
#include <stdlib.h>
#include "header.h"
#include "scene_test.h"

#include "lib/dreamroqlib.h"
#include "asset/map_test/mapdata.c"

void loadTestData(scene* self);

texture _t;
gameObject portrait;
roq_callbacks_t cbs;

void loadTest(scene* self) {
  mount_romdisk("asset/rd_test.img.gz", "/rd");
  generateFloor(self, -1);

  loadTestData(self);
  setMapInfo(self, 1000, 1000, 320, 240);

  cbs.render_cb = render_cb;
  cbs.audio_cb = audio_cb;
  cbs.quit_cb = quit_cb;
  cbs.finish_cb = finish_cb;

  //self->bgm = "/cd/music/soussol.ogg";
  //sndoggvorbis_start(self->bgm, 1);

  //loadLuaFile(t_data, "/rd/json.lua");
  loadLuaFile(t_data, "/rd/jsontest.lua");

  portrait = createObject("/rd/data_map.png", 320, 240, 1);
  getAtlasData(&portrait.t, "autel.png");

  lua_getglobal(t_data, "loadXML");
  lua_pcall(t_data, 0, 1, 0);
  //lua_settop(t_data, 0);
  setParam(2, lua_tostring(t_data, -1));
  char *buf = lua_tostring(t_data, -1);
  setDialog(buf, "");

  self->objNum = 0;
  self->updateScene = updateTest;
  //self->updateGUI = updateGUI;
  self->freeScene = freeTest;
}


void _updateGUI(scene *self){
  if(buttonPressed(CONT_A))
    toggleDialog();
}

void updateTest(cont_state_t *state, scene *self){
  drawObject(&portrait);

  char *buf = "";
  snprintf(buf, 16, "x-%d y-%d", (int)p1.obj.x, (int)p1.obj.y);
  setParam(5, buf);

  //if(dreamroq_play("/rd/test_512_square.roq", ROQ_RGB565, 1, &cbs))
    //setParam(2, "Can't open ROQ file.");
}

void freeTest(scene *self){

  for (int i = 0; i < self->objNum; i++){
    if(&self->obj[i].t.id != 0)
      glDeleteTextures(1, &self->obj[i].t.id);
  }

  free(self->obj);
}
