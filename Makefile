all: examples/helloworld/helloworld_libretro.so

examples/helloworld/helloworld_libretro.so:
	make --directory=examples/helloworld

vendor/noarch/README.md:
	git submodule update --init

vendor/noarch/noarch: vendor/noarch/README.md
	@$(MAKE) --directory=vendor/noarch

test: vendor/noarch/noarch all
	vendor/noarch/noarch examples/helloworld/helloworld_libretro.so README.md
