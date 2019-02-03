#include "libretro.hpp"

class HelloWorld : public libretropp::Libretro {
	void init() {
		std::cout << "HelloWorld::INIT!!!!" << std::endl;
	}
} hello;
