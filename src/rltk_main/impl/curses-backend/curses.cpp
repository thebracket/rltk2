#include "curses.hpp"
#define PDC_WIDE
#include <curses.h>
#include <map>
#include "../cp437.hpp"

namespace rltk
{
	namespace curses
	{
		WINDOW* mainscr;
		int N_COLORS;

		struct curses_color_t
		{
			curses_color_t(const short &red, const short &green, const short &blue) : r(red), g(green), b(blue)
			{
				rf = static_cast<float>(red) / 1000.0f;
				gf = static_cast<float>(green) / 1000.0f;
				bf = static_cast<float>(blue) / 1000.0f;
			}

			short r, g, b;
			float rf, gf, bf;
		};

		std::vector<curses_color_t> color_map;

		short find_closest_color(const color_t &c)
		{
			std::map<float, short> color_sorter;

			short count = 0;
			for (const auto &cc : color_map)
			{
				const auto diff_r = std::abs(c.red - cc.rf);
				const auto diff_g = std::abs(c.green - cc.gf);
				const auto diff_b = std::abs(c.blue - cc.bf);
				const auto total_diff = diff_r + diff_g + diff_b;
				color_sorter.insert(std::make_pair(total_diff, count));
				++count;
			}

			return color_sorter.begin()->second;
		}		

		static void init_16_colors()
		{
			// Build the color map
			for (short i = 0; i<N_COLORS; ++i)
			{
				short r, g, b;
				color_content(i, &r, &g, &b);
				color_map.emplace_back(curses_color_t{ r, g, b });
			}

			// Setup pairs for everything
			short counter = 0;
			for (auto bg = 0; bg < N_COLORS; ++bg)
			{
				for (auto fg = 0; fg < N_COLORS; ++fg)
				{
					init_pair(counter, fg, bg);
					++counter;
				}
			}
		}

		static short find_color_pair(const color_t &foreground, const color_t &background)
		{
			const auto fg = find_closest_color(foreground);
			const auto bg = find_closest_color(background);

			return (bg*N_COLORS) + fg;
		}

		void init(const rltk_mode_t mode)
		{
			mainscr = initscr();
			start_color();
			use_default_colors();
			N_COLORS = 16;
			init_16_colors();
		}

		void stop()
		{
			endwin();
		}

		void present()
		{
			refresh();
		}

		void get_dimensions(int &width, int &height)
		{
			getmaxyx(mainscr, height, width);
		}

		void present_console(const std::vector<vchar_t> &console, const std::vector<color_t> &foreground, const std::vector<color_t> &background, const int &w, const int &h)
		{
			for (auto y=0; y<h; ++y)
			{
				for (auto x=0; x<w; ++x)
				{
					const auto idx = (y*w) + x;
					const auto color_pair = find_color_pair(foreground[idx], background[idx]);
					cchar_t tmp;
					setcchar(&tmp, get_cp_mapping(console[idx].glyph), 0, color_pair, nullptr);
					mvwadd_wch(mainscr, y, x, &tmp);
				}
			}
		}
	}
}
