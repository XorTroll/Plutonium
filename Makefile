
.PHONY: all clean

export PU_MAJOR := 1
export PU_MINOR := 0
export PU_MICRO := 0

all:
	@$(MAKE) -C Plutonium/

clean:
	@$(MAKE) clean -C Plutonium/
