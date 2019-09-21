
.PHONY: all clean

all:
	@$(MAKE) -C Plutonium/

clean:
	@$(MAKE) clean -C Plutonium/