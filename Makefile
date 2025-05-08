
.PHONY: all clean

export PU_MAJOR := 2
export PU_MINOR := 0
export PU_MICRO := 0

all:
	@$(MAKE) -C libpu/
	@$(MAKE) -C libpu-ocean/

clean:
	@$(MAKE) clean -C libpu/
	@$(MAKE) clean -C libpu-ocean/
