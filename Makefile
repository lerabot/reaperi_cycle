TARGET = main.elf
OBJS = main.o utils.o

OBJS += scene_temple.o scene_test.o scene_desert.o scene_soussol.o scene_jardin.o scene_menu.o

REAP_LIBS = $(addprefix lib/, $(REAP_OBJ))
REAP_OBJ  = gl_png.o debug_screen.o game_object.o scene.o particule.o gl_font.o  tilemap.o gl_pvr_texture.o dreamroqlib.o player.o

KOS_CFLAGS += -std=c99 -I$(KOS_PORTS)/include/lua
#KOS_ROMDISK_DIR = romdisk

all: rm-elf $(TARGET)

include $(KOS_BASE)/Makefile.rules

clean:
	@$(RM) $(TARGET) $(OBJS) $(REAP_LIBS) romdisk.* *.cdi *.iso

rm-elf:
	@$(RM) $(TARGET) romdisk.*

$(TARGET): $(OBJS) $(REAP_LIBS) romdisk.o
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET) $(KOS_START) \
		$(OBJS) $(REAP_LIBS) romdisk.o $(OBJEXTRA) -lpng -llua -lGLdc -lmp3 -loggvorbisplay -lvorbis -logg -lm -lz  $(KOS_LIBS)

#make a bunch of romdisk here
romdisk.img:
	$(KOS_GENROMFS) -f romdisk.img -d romdisk
	$(KOS_GENROMFS) -f asset/rd_temple.img -d asset/map_temple
	$(KOS_GENROMFS) -f asset/rd_soussol.img -d asset/map_soussol
	$(KOS_GENROMFS) -f asset/rd_jardin.img -d asset/map_jardin
	$(KOS_GENROMFS) -f asset/rd_desert.img -d asset/map_desert
	$(KOS_GENROMFS) -f asset/rd_menu.img -d asset/map_menu
	$(KOS_GENROMFS) -f asset/rd_test.img -d asset/map_test

	gzip -f -9 asset/rd_temple.img asset/rd_desert.img asset/rd_soussol.img asset/rd_jardin.img asset/rd_test.img asset/rd_menu.img
	#mkisofs -o ../phenix_data.iso fiole intro sounds

romdisk.o: romdisk.img
	$(KOS_BASE)/utils/bin2o/bin2o romdisk.img romdisk romdisk.o

run: $(TARGET)
	$(KOS_LOADER) $(TARGET)

dist:
	rm -f $(OBJS) romdisk.o romdisk.img
	$(KOS_STRIP) $(TARGET)
