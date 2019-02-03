/* Copyright (C) 2019 Rob Loach (https://robloach.net)
 *
 * ---------------------------------------------------------------------------------------
 * The following license statement only applies to this libretro API header (libretro.h).
 * ---------------------------------------------------------------------------------------
 *
 * Permission is hereby granted, free of charge,
 * to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef LIBRETROPP_H__
#define LIBRETROPP_H__

#include "libretro.h"

#include <iostream>

namespace libretropp {
	class Libretro {
	public:
		Libretro() {
			libretropp::Libretro::setInstance(this);
		}

		void init() {
			std::cout << "Libretro::init() called" << std::endl;
		}

		void deinit() {
			std::cout << "Libretro::deinit() called" << std::endl;
		}

		static Libretro* get() {
			return m_instance;
		}

		static void setInstance(Libretro* libretro) {
			m_instance = libretro;
		}

		static Libretro* m_instance;
	};
}

void retro_init(void) {
	libretropp::Libretro::get()->init();
}

void retro_deinit(void) {
	libretropp::Libretro::get()->deinit();
}

#endif