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
#include <cstring>
#include <string>

namespace libretropp {
	class Libretro {
	public:

		virtual void deinit() {
			std::cout << "Libretro::deinit() called" << std::endl;
		}

		void setWidth(int width) {
			m_width = width;
		}

		void setHeight(int height) {
			m_height = height;
		}

		int getWidth() {
			return m_width;
		}

		int getHeight() {
			return m_height;
		}

		virtual void reset() {
			// Nothing.
		}

		std::string name = "libretropp";
		std::string extensions = "txt";
		std::string version;
		bool needFullPath;
		bool blockExtract;

		static Libretro* get() {
			return m_instance;
		}

		static void init(Libretro* libretro) {
			m_instance = libretro;
		}

		static Libretro* m_instance;

	private:
		int m_width;
		int m_height;
	};
}

libretropp::Libretro* libretropp::Libretro::m_instance = NULL;

void retro_deinit(void) {
	std::cout << "retro_deinit() " << std::endl;
	libretropp::Libretro* lib = libretropp::Libretro::get();
	if (lib != NULL) {
		lib->deinit();
		delete lib;
		libretropp::Libretro::init(NULL);
	}
}

unsigned retro_api_version(void) {
	return RETRO_API_VERSION;
}

/**
 * libretro callback; Retrieve information about the core.
 */
void retro_get_system_info(struct retro_system_info *info) {
	libretropp::Libretro* lib = libretropp::Libretro::get();
	if (lib != NULL) {
		memset(info, 0, sizeof(*info));
		info->library_name = "libretropp";
		info->library_version  = "0.0.1";
		info->need_fullpath = false;
		info->valid_extensions = "chai|chailove";
		info->block_extract = true;
	}
	else {
		memset(info, 0, sizeof(*info));
		libretropp::Libretro* lib = libretropp::Libretro::get();
		info->library_name = lib->name.c_str();
		info->library_version  = lib->version.c_str();
		info->need_fullpath = lib->needFullPath;
		info->valid_extensions = lib->extensions.c_str();
		info->block_extract = lib->blockExtract;
	}
}

/**
 * libretro callback; Set the audio/video settings.
 */
void retro_get_system_av_info(struct retro_system_av_info *info) {
	std::cout << "retro_get_system_av_info" << std::endl;
	unsigned int width = 640;
	unsigned int height = 480;

	info->geometry.base_width   = width;
	info->geometry.base_height  = height;
	info->geometry.max_width    = width;
	info->geometry.max_height   = width;
	info->geometry.aspect_ratio = static_cast<float>(width) / static_cast<float>(height);

	info->timing.fps = 60.0;
	info->timing.sample_rate = 44100.0;
}

void retro_set_controller_port_device(unsigned port, unsigned device) {
	std::cout << "retro_set_controller_port_device" << std::endl;
	(void)port;
	(void)device;
}


/**
 * libretro callback; The frontend requested to reset the game.
 */
void retro_reset(void) {
	std::cout << "retro_reset()" << std::endl;
	libretropp::Libretro* lib = libretropp::Libretro::get();
	if (lib != NULL) {
		lib->reset();
	}
}


/**
 * libretro callback; Run a game loop in the core.
 */
void retro_run(void) {
	std::cout << "retro_run()" << std::endl;
}


/**
 * libretro callback; Load the given game.
 */
bool retro_load_game(const struct retro_game_info *info) {
	std::cout << "retro_load_game()" << std::endl;
	return true;
}

/**
 * libretro callback; Unload the current game.
 */
void retro_unload_game(void) {
	std::cout << "retro_unload_game()" << std::endl;
}

/**
 * libretro callback; Sets up the environment based on the system variables.
 */
void retro_set_environment(retro_environment_t cb) {
	std::cout << "retro_set_environment()" << std::endl;
	// The core supports having no game.
	bool no_rom = true;
	cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &no_rom);

	// Set the Variables.
	/*struct retro_variable variables[] = {
		{
			"chailove_alphablending", "Alpha Blending; enabled|disabled",
		},
		{
			"chailove_highquality", "High Quality; enabled|disabled",
		},
		{ NULL, NULL },
	};
	cb(RETRO_ENVIRONMENT_SET_VARIABLES, variables);*/
}

void retro_set_video_refresh(retro_video_refresh_t cb) {
	std::cout << "retro_set_video_refresh()" << std::endl;
}

void retro_set_audio_sample(retro_audio_sample_t cb) {
	std::cout << "retro_set_audio_sample()" << std::endl;
}

void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) {
	std::cout << "retro_set_audio_sample_batch()" << std::endl;
}

void retro_set_input_poll(retro_input_poll_t cb) {
	std::cout << "retro_set_input_poll()" << std::endl;
}

void retro_set_input_state(retro_input_state_t cb) {
	std::cout << "retro_set_input_state()" << std::endl;
}

size_t retro_serialize_size(void) {
	// Save states will be 8 KB.
	return 8192;
}

/**
 * libretro callback; Serialize the current state to save a slot.
 */
bool retro_serialize(void *data, size_t size) {
	return false;
}

/**
 * libretro callback; Unserialize the given data and load the state.
 */
bool retro_unserialize(const void *data, size_t size) {
	return false;
}



/**
 * libretro callback; Reset the enabled cheats.
 */
void retro_cheat_reset(void) {
}

/**
 * libretro callback; Set the given cheat.
 */
void retro_cheat_set(unsigned index, bool enabled, const char *code) {
}

/**
 * libretro callback; Loads the given special game.
 */
bool retro_load_game_special(unsigned game_type, const struct retro_game_info *info, size_t num_info) {
	//std::cout << "[ChaiLove] retro_load_game_special" << std::endl;
	return retro_load_game(info);
}
/**
 * libretro callback; Retrieve the active region.
 */
unsigned retro_get_region(void) {
	return RETRO_REGION_NTSC;
}

/**
 * libretro callback; Get the given memory ID.
 */
void *retro_get_memory_data(unsigned id) {
	return NULL;
}

/**
 * libretro callback; Get the size of the given memory ID.
 */
size_t retro_get_memory_size(unsigned id) {
	return 0;
}
#endif