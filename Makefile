TARGET		:= vitaET
TITLE		:= WETLEGACY
GIT_VERSION := $(shell git describe --abbrev=6 --dirty --always --tags)

SOURCES  := src/rendererGLES src/qcommon src/botlib src/client src/server src/psp2 src/sys src/renderercommon
CPPSOURCES := code/splines
INCLUDES := src/rendererGLES src/qcommon src/botlib src/client src/server src/psp2 src/sys src/renderercommon

LIBS = -lvitaGL -lvorbisfile -lvorbis -logg  -lspeexdsp -lmpg123 -lcurl -lssl -lcrypto \
	-lc -lSceCommonDialog_stub -lSceAudio_stub -lSceLibKernel_stub -lSceSsl_stub \
	-lSceNet_stub -lSceNetCtl_stub -lpng -lz -lSceDisplay_stub -lSceGxm_stub \
	-lSceSysmodule_stub -lSceCtrl_stub -lSceTouch_stub -lSceMotion_stub -lm -lSceAppMgr_stub \
	-lSceAppUtil_stub -lScePgf_stub -ljpeg -lSceRtc_stub -lScePower_stub -lmathneon

CFILES   := $(filter-out src/psp2/psp2_dll_hacks.c,$(foreach dir,$(SOURCES), $(wildcard $(dir)/*.c)))
CPPFILES   := $(foreach dir,$(CPPSOURCES), $(wildcard $(dir)/*.cpp))
BINFILES := $(foreach dir,$(DATA), $(wildcard $(dir)/*.bin))
OBJS     := $(addsuffix .o,$(BINFILES)) $(CFILES:.c=.o) $(CPPFILES:.cpp=.o)

export INCLUDE	:= $(foreach dir,$(INCLUDES),-I$(dir))

PREFIX  = arm-vita-eabi
CC      = $(PREFIX)-gcc
CXX      = $(PREFIX)-g++
CFLAGS  = $(INCLUDE) -D__PSP2__ -D__FLOAT_WORD_ORDER=1 -D__GNU__ -DFEATURE_MULTIVIEW \
        -DUSE_ICON -DARCH_STRING=\"arm\" -DBOTLIB -DUSE_CODEC_VORBIS \
        -DPRODUCT_VERSION=\"1.36_GIT_ba68b99c-2018-01-23\" -DHAVE_VM_COMPILED=true \
        -mfpu=neon -mcpu=cortex-a9 -fsigned-char -DFEATURE_RENDERER_GLES \
        -Wl,-q -O2 -ftree-vectorize -g -ffast-math -fno-short-enums -DRELEASE
CXXFLAGS  = $(CFLAGS) -fno-exceptions -std=gnu++11 -fpermissive
ASFLAGS = $(CFLAGS)

all: $(TARGET).vpk

$(TARGET).vpk: $(TARGET).velf
	make -C src/cgame
	cp -f src/cgame/cgame.suprx ./cgame.mp.arm.suprx
	make -C src/ui
	cp -f src/ui/ui.suprx ./ui.mp.arm.suprx
	make -C src/game
	cp -f src/game/qagame.suprx ./qagame.mp.arm.suprx
	vita-make-fself -s $< build/eboot.bin
	vita-mksfoex -s TITLE_ID=$(TITLE) -d ATTRIBUTE2=12 "$(TARGET)" param.sfo
	cp -f param.sfo build/sce_sys/param.sfo

	#------------ Comment this if you don't have 7zip ------------------
	7z a -tzip ./$(TARGET).vpk -r ./build/sce_sys ./build/eboot.bin ./build/mp_eboot.bin
	#-------------------------------------------------------------------

eboot.bin: $(TARGET).velf
	vita-make-fself -s $< eboot.bin

%.velf: %.elf
	cp $< $<.unstripped.elf
	$(PREFIX)-strip -g $<
	vita-elf-create $< $@

$(TARGET).elf: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

clean:
	@make -C src/cgame clean
	@make -C src/ui clean
	@make -C src/game clean
	@rm -rf $(TARGET).velf $(TARGET).elf $(OBJS) $(TARGET).elf.unstripped.elf $(TARGET).vpk build/eboot.bin build/sce_sys/param.sfo ./param.sfo
