#include "rltk.hpp"
#include <vector>
#include <memory>
#include "impl/terminal.hpp"
#include "impl/curses-backend/curses.hpp"
#include "impl/cp437.hpp"

namespace rltk
{

	namespace impl
	{
		std::vector<std::unique_ptr<terminal_t>> terminals;
		rltk_mode_t mode;
		int current_terminal = -1;

		int init_curses()
		{
			curses::init(mode);

			int w, h;
			curses::get_dimensions(w, h);
			if (mode.add_root_terminal)
			{
				terminals.emplace_back(std::make_unique<terminal_t>(w, h));
				current_terminal = 0;
				return 0;
			}

			return -1;
		}

		int init_sdl()
		{
			return -1;
		}

		void stop_curses()
		{
			curses::stop();
		}

		void stop_sdl()
		{
			
		}
	}

	int init(const rltk_mode_t new_mode)
	{
		using namespace impl;
		mode = new_mode;

		// Initialize the back-end
		switch (mode.backend)
		{
		case CURSES: return init_curses(); break;
		case SDL: return init_sdl(); break;
		}

		return -1; // We shouldn't have got here
	}

	void stop()
	{
		using namespace impl;

		switch (mode.backend)
		{
		case CURSES: stop_curses(); break;
		case SDL: stop_sdl(); break;
		}
	}

	void set_terminal(const int t)
	{
		impl::current_terminal = t;
	}

	int get_terminal()
	{
		return impl::current_terminal;
	}

	void get_dimensions(int * width, int * height)
	{
		*width = impl::terminals[impl::current_terminal]->width;
		*height = impl::terminals[impl::current_terminal]->height;
	}

	void cls()
	{
		impl::terminals[impl::current_terminal]->cls();
	}

	void cls(const color_t &fg, const color_t &bg)
	{
		impl::terminals[impl::current_terminal]->cls(fg, bg);
	}

	void print_at(const int x, const int y, const char * text)
	{
		impl::terminals[impl::current_terminal]->print_at(x, y, text);
	}

	void print_at(const int x, const int y, const color_t fg, const color_t bg, const char* text)
	{
		impl::terminals[impl::current_terminal]->print_at(x, y, fg, bg, text);
	}

	void wprint_at(const int x, const int y, const color_t fg, const color_t bg, const wchar_t * text)
	{
		for (size_t i=0; i<wcslen(text); ++i)
		{
			const auto ch = text[i];
			const auto n = get_unicode_as_cp(ch);
			set_char(x + i, y, fg, bg, n);
		}
	}

	void set_char(const int x, const int y, const color_t fg, const color_t bg, const int glyph)
	{
		impl::terminals[impl::current_terminal]->set_char(x, y, fg, bg, glyph);
	}

	void set_wchar(const int x, const int y, const color_t fg, const color_t bg, const wchar_t * glyph)
	{
		impl::terminals[impl::current_terminal]->set_char(x, y, fg, bg, get_unicode_as_cp(*glyph));
	}

	void present()
	{
		for (const auto &t : impl::terminals)
		{
			t->present();
		}

		switch (impl::mode.backend)
		{
		case CURSES: curses::present(); break;
		case SDL: break;
		}
	}

	void main_loop(void (* fun_ptr)(bool *))
	{
		auto quitting = false;
		while (!quitting) {
			(*fun_ptr)(&quitting);
			present();
		}
	}
}
