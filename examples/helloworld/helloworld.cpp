#include "libretro.hpp"

using libretropp::Libretro;

class HelloWorld : public Libretro {
public:
	HelloWorld() {
	}

	void deinit() {
		std::cout << "HelloWorld::DEINIT!!!!" << std::endl;
	}

	void reset() {
		std::cout << "Reset()" << std::endl;
	}
};

void retro_init(void) {
	std::cout << "retro_init() " << std::endl;
	Libretro::init(new HelloWorld());
}