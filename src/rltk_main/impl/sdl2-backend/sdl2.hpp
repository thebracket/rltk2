#pragma once

#include "../vchar.hpp"
#include <vector>
#include "../color.hpp"
#include "../../rltk.hpp"

namespace rltk
{
	namespace sdl2
	{
		void init(const rltk_mode_t mode);
		void stop();
		void present();
		void load_bitmap_font(const char * filename, const int size_pixels, const int n_glyphs);
		void present_console(const std::vector<vchar_t> &console, const std::vector<color_t> &foreground, const std::vector<color_t> &background, const int &w, const int &h);
	}
}