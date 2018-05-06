
OBJS = gl_png.o debug_screen.o game_object.o scene.o controller.o particule.o glfont.o  tilemap.o gl_pvr_texture.o dreamroqlib.o

KOS_CFLAGS += -std=c11 -I$(KOS_PORTS)/include/lua
#KOS_LDFLAGS += -shared

all: rm-elf $(TARGET)

include $(KOS_BASE)/Makefile.rules

clean:
	@$(RM) $(TARGET) $(OBJS)

rm-elf:
	@$(RM) $(TARGET) romdisk.*

all: $(OBJS)
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) $(OBJS) -lpng -lkmg -llua -lGL -lmp3 -loggvorbisplay -lvorbis -logg -lparallax -lm -lz $(KOS_LIBS)

run: $(TARGET)
	$(KOS_LOADER) $(TARGET)
