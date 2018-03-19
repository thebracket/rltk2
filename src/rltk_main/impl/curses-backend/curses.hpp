#pragma once
#include "../vchar.hpp"
#include <vector>
#include "../color.hpp"
#include "../../rltk.hpp"

namespace rltk
{
	namespace curses
	{
		void init(const rltk_mode_t mode);
		void stop();
		void present();

		void get_dimensions(int &width, int &height);
		void present_console(const std::vector<vchar_t> &console, const std::vector<color_t> &foreground, const std::vector<color_t> &background, const int &w, const int &h);
	}
}
