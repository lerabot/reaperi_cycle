PROJECT_NAME = "Reaperi_Cycle_V3_Hideout_Video"
DIR = $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
TARGET = main.elf
OBJS = main.o utils.o

REAP_SCENES = $(addprefix scenes/, $(SCENES))
SCENES			= scene_temple.o scene_test.o scene_desert.o scene_soussol.o scene_jardin.o scene_menu.o scene_hideout.o scene_illusion.o

REAP_LIBS = $(addprefix lib/, $(REAP_OBJ))
REAP_OBJ  = gl_png.o debug_screen.o game_object.o scene.o particule.o gl_font.o  tilemap.o dreamroqlib.o player.o lua_binds.o vmu.o quest.o

KOS_CFLAGS += -std=c99 -I$(KOS_PORTS)/include/lua
KOS_CFLAGS += -I$(DIR)scenes/ -I$(DIR)lib/
#KOS_ROMDISK_DIR = romdisk

all: rm-elf $(TARGET)

include $(KOS_BASE)/Makefile.rules

clean:
	@$(RM) $(TARGET) $(OBJS) $(REAP_LIBS) $(REAP_SCENES) romdisk.* *.cdi *.iso *.img *.gz

rm-elf:
	@$(RM) $(TARGET) romdisk.*

$(TARGET): $(OBJS) $(REAP_SCENES) $(REAP_LIBS) romdisk.o
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET) $(KOS_START) \
		$(OBJS) $(REAP_SCENES) $(REAP_LIBS) romdisk.o $(OBJEXTRA) -lpng -llua -lGLdc -lmp3 -loggvorbisplay -lvorbis -logg -lm -lz  $(KOS_LIBS)

#make a bunch of romdisk here
romdisk.img:
	$(KOS_GENROMFS) -f romdisk.img -d romdisk
	$(KOS_GENROMFS) -f asset/rd_temple.img -d asset/map_temple
	$(KOS_GENROMFS) -f asset/rd_soussol.img -d asset/map_soussol
	$(KOS_GENROMFS) -f asset/rd_jardin.img -d asset/map_jardin
	$(KOS_GENROMFS) -f asset/rd_desert.img -d asset/map_desert
	$(KOS_GENROMFS) -f asset/rd_menu.img -d asset/map_menu
	$(KOS_GENROMFS) -f asset/rd_test.img -d asset/map_test
	$(KOS_GENROMFS) -f asset/rd_hideout.img -d asset/map_hideout
	$(KOS_GENROMFS) -f asset/rd_illusion.img -d asset/map_illusion

romdisk.o: romdisk.img
	$(KOS_BASE)/utils/bin2o/bin2o romdisk.img romdisk romdisk.o

run: $(TARGET)
	$(KOS_LOADER) $(TARGET)

cd: $(TARGET)
	@sh-elf-objcopy -R .stack -O binary $(TARGET) output.bin
	@$(KOS_BASE)/utils/scramble/scramble output.bin 1ST_READ.BIN
	@mkisofs -C 0,11702 -V Reaperi_Cycle -G $(KOS_BASE)/IP.BIN -r -J -l -m '*.o' -x $(DIR).git -o ../$(PROJECT_NAME).iso $(DIR)
	@$(KOS_BASE)/utils/cdi4dc/cdi4dc ../$(PROJECT_NAME).iso ../$(PROJECT_NAME).cdi -d > cdi4dc.log
	../redream ../$(PROJECT_NAME).cdi

console: $(TARGET)
	@sh-elf-objcopy -R .stack -O binary $(TARGET) output.bin
	@$(KOS_BASE)/utils/scramble/scramble output.bin 1ST_READ.BIN
	@mkisofs -C 0,11702 -V Reaperi_Cycle -G $(KOS_BASE)/IP.BIN -r -J -l -m '*.o' -x $(DIR).git -o ../$(PROJECT_NAME).iso $(DIR)
	@$(KOS_BASE)/utils/cdi4dc/cdi4dc ../$(PROJECT_NAME).iso ../$(PROJECT_NAME).cdi -d > cdi4dc.log
	sudo arp -s 192.168.0.99 00:d0:f1:03:14:02
	sudo ../dc-tool-ip -t dreamcast -c ./ -x main.elf

dist:
	rm -f $(OBJS) romdisk.o romdisk.img
	$(KOS_STRIP) $(TARGET)
