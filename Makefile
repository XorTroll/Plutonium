
.PHONY: all clean

all:
	$(MAKE) -C libpu/
	$(MAKE) -C example/

clean:
	$(MAKE) clean -C libpu/
	$(MAKE) clean -C example/