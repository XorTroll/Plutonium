
.PHONY: all clean

export PU_MAJOR := 0
export PU_MINOR := 3
export PU_MICRO := 0

all:
	@$(MAKE) -C Plutonium/

clean:
	@$(MAKE) clean -C Plutonium/