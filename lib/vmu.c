#include <kos.h>
#include <zlib/zlib.h>
#include <dc/vmufs.h>
#include <dc/vmu_pkg.h>
#include <string.h>
#include <stdio.h>
#include "vmu.h"
#include "debug_screen.h"


int VMU_loadVMU() {
  int             buf_size;
  vmu_root_t      *vmu;
  vmu_dir_t       *vmu_dir;
  char            *buf = "";

  /*
  maple_device_t *d = maple_enum_dev(0, 1);

  if(vmufs_root_read(d, &vmu) == 0)
    buf = "VMU Loaded";

  vmu_dir = malloc(vmufs_dir_blocks(&vmu));
  if(vmufs_dir_read(d, &vmu, vmu_dir) == 0)
    buf = "VMU Dir Loaded";
  */
  setParam(5, buf);
  return(1);
}

/* Here's the actual meat of it */
int VMU_saveGame() {
    vmu_pkg_t   pkg;
    player_data p;
    uint8       data[4096], *pkg_out;
    int         pkg_size;
    int         i;
    file_t      f;

    strcpy(pkg.desc_short, "Reaperi");
    strcpy(pkg.desc_long, "This is a test VMU file");
    strcpy(pkg.app_id, "Reaperi Cycle");
    pkg.icon_cnt = 0;
    pkg.icon_anim_speed = 0;
    pkg.eyecatch_type = VMUPKG_EC_NONE;

    if (!VMU_packData(p))
      return(0);

    pkg.data_len = 4096;
    pkg.data = &p;

    vmu_pkg_build(&pkg, &pkg_out, &pkg_size);

    fs_unlink("/vmu/a1/REAPERI");
    f = fs_open("/vmu/a1/REAPERI", O_WRONLY);

    if(!f) {
      return(0);
    }

    setParam(5, "Saved File!");
    fs_write(f, pkg_out, pkg_size);
    fs_close(f);
    return(1);
}

int VMU_loadGame() {
  file_t          d;
  dirent_t        *de;
  vmu_pkg_t       pkg;
  player_data     *p;
  int             fileCount;
  char            *dir = "/vmu/a1";
  char            *filename = "";

  d = fs_open(dir, O_RDONLY | O_DIR);
  sprintf(filename, "%s/", dir);

  if(!d) {
    setParam(5, "No VMU");
    return(0);
  }
  else {
    int i = 0;
    while((de = fs_readdir(d))) {
      //setString(i, de->name);
      //i++;
      if (strcmp(de->name, "REAPERI") == 0) {
        setParam(5, "Found Save!");
        break;
      }
      else {
        setParam(5, "No Save.");
      }
    }
  }
  strcat(filename, de->name);

  int     vmu_package = fs_open(filename, O_RDONLY);
  int     filesize = fs_total(vmu_package);
  uint8   *data = (uint8*)malloc(filesize);

  fs_read(vmu_package, data, filesize);
  vmu_pkg_parse(data, &pkg);
  fs_close(vmu_package);
  sprintf(filename, "%s size %i", filename, filesize);
  setParam(5, filename);

  p = &pkg.data;

  setInt(3, p->pos[1]);

  return(1);
}

int VMU_packData(player_data p) {

  p.pos[0] = p1.obj.x;
  p.pos[1] = p1.obj.y;

  return(1);
}

int VMU_unpackGame(player_data p) {

  p1.obj.x = p.pos[0];
  p1.obj.y = p.pos[1];

  return(1);
}
