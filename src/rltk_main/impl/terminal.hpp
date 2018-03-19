#pragma once
#include "vchar.hpp"
#include <vector>
#include "color.hpp"

namespace rltk
{
	class terminal_t
	{
	public:
		terminal_t(const int w, const int h);
		void cls();
		void cls(const color_t &fg, const color_t &bg);
		void print_at(const int x, const int y, const char * text);
		void print_at(const int x, const int y, const color_t fg, const color_t bg, const char* text);
		void set_char(const int x, const int y, const color_t fg, const color_t bg, const uint16_t glyph);
		void present() const;
		int width, height;

	private:
		std::vector<vchar_t> console_;
		std::vector<color_t> background_;
		std::vector<color_t> foreground_;
	};
}
