#include "terminal.hpp"
#include "curses-backend/curses.hpp"

namespace rltk
{
	terminal_t::terminal_t(const int w, const int h)
	{
		width = w;
		height = h;
		console_.resize(width * height);
		foreground_.resize(width * height);
		background_.resize(width * height);
	}

	void terminal_t::cls()
	{
		std::fill(console_.begin(), console_.end(), vchar_t{ ' ' });
		std::fill(foreground_.begin(), foreground_.end(), color_t{ 0.0f, 0.0f, 0.0f });
		std::fill(background_.begin(), background_.end(), color_t{ 0.f, 0.f, 0.f });
	}

	void terminal_t::cls(const color_t& fg, const color_t& bg)
	{
		std::fill(console_.begin(), console_.end(), vchar_t{ ' ' });
		std::fill(foreground_.begin(), foreground_.end(), fg);
		std::fill(background_.begin(), background_.end(), bg);
	}

	void terminal_t::print_at(const int x, const int y, const char* text)
	{
		const auto idx = (y * width) + x;
		for (auto i=0; i < strlen(text); ++i)
		{
			console_[idx + i].glyph = text[i];
		}
	}

	void terminal_t::print_at(const int x, const int y, const color_t fg, const color_t bg, const char* text)
	{
		const auto idx = (y * width) + x;
		for (auto i = 0; i < strlen(text); ++i)
		{
			console_[idx + i].glyph = text[i];
			foreground_[idx + i] = fg;
			background_[idx + i] = bg;
		}
	}

	void terminal_t::set_char(const int x, const int y, const color_t fg, const color_t bg, const uint16_t glyph)
	{
		const auto idx = (y * width) + x;
		console_[idx].glyph = glyph;
		foreground_[idx] = fg;
		background_[idx] = bg;
	}


	void terminal_t::present() const
	{
		curses::present_console(console_, foreground_, background_, width, height);
	}

}