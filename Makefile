
.PHONY: all clean

export GLOBAL_DEFS	:=	-DPU_USE_SDL2_IMAGE -DPU_USE_SDL2_GFX -DPU_USE_SDL2_MIXER

all:
	$(MAKE) -C libpu/
	$(MAKE) -C example/

clean:
	$(MAKE) clean -C libpu/
	$(MAKE) clean -C example/