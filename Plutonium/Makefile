#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>/devkitpro")
endif

include $(DEVKITPRO)/devkitA64/base_rules
include $(DEVKITPRO)/libnx/switch_rules

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# SOURCES is a list of directories containing source code
# DATA is a list of directories containing data files
# INCLUDES is a list of directories containing header files
#---------------------------------------------------------------------------------
BUILD		:=	build
TARGET		:=  pu
SOURCES		:=	Source Source/pu Source/pu/audio Source/pu/ui Source/pu/ttf Source/pu/sdl2 Source/pu/ui/elm Source/pu/ui/extras Source/pu/ui/render Source/pu/web
INCLUDES	:=	include
OUT			:=	out

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH	:=	-march=armv8-a -mtune=cortex-a57 -mtp=soft -fPIC -ftls-model=local-exec

CFLAGS	:=	-g -w -D__SWITCH__ \
			-ffunction-sections \
			-fdata-sections \
			$(ARCH) \

CFLAGS	+=	$(INCLUDE) -I$(PORTLIBS)/include/freetype2 -DPU_MAJOR=$(PU_MAJOR) -DPU_MINOR=$(PU_MINOR) -DPU_MICRO=$(PU_MICRO) -DPU_VERSION=\"$(PU_MAJOR).$(PU_MINOR).$(PU_MICRO)\"

CXXFLAGS	:= $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++17

ASFLAGS	:=	-g $(ARCH)
LDFLAGS	=	-specs=${DEVKITPRO}/libnx/switch.specs -g $(ARCH) -Wl,-r,-Map,$(notdir $*.map)

SDL_IMAGE_LIBS	:= -lSDL2_image -lpng -ljpeg
SDL_GFX_LIBS	:= -lSDL2_gfx
SDL_MIXER_LIBS	:= -lSDL2_mixer -lmodplug -lmpg123 -lvorbisidec -logg

LIBS	:=  $(SDL_IMAGE_LIBS) $(SDL_GFX_LIBS) $(SDL_MIXER_LIBS) -lEGL -lGLESv2 -lglapi `sdl2-config --libs` `freetype-config --libs`

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:= $(PORTLIBS) $(LIBNX)

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
			$(foreach dir,$(DATA),$(CURDIR)/$(dir))

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
#---------------------------------------------------------------------------------
	export LD	:=	$(CC)
#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------
	export LD	:=	$(CXX)
#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------
export OUTPUT       := $(CURDIR)/$(OUT)/lib/lib$(TARGET).a
export DEPSDIR      := $(CURDIR)/$(BUILD)
export OFILES_BIN	:=	$(addsuffix .o,$(BINFILES))
export OFILES_SRC	:=	$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)
export OFILES 	:=	$(OFILES_BIN) $(OFILES_SRC)
export HFILES	:=	$(addsuffix .h,$(subst .,_,$(BINFILES)))

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			-I$(CURDIR)/$(BUILD)

.PHONY: $(BUILD) clean all

#---------------------------------------------------------------------------------
all: $(BUILD)

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@[ -d $(OUT)/lib ] || mkdir -p $(OUT)/lib
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile
	@rm -rf $(OUT)/include
	@cp -r include $(OUT)/include

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(CURDIR)/$(OUT)
	@rm -fr $(BUILD) $(OUTPUT).a

#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT)	:	$(OFILES)

$(OFILES_SRC)	: $(HFILES)

#---------------------------------------------------------------------------------
%_bin.h %.bin.o	:	%.bin
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)


-include $(DEPENDS)

#---------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------