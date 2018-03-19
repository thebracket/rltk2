#include "sdl2.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprite.hpp"
#include <memory>

namespace rltk
{
	namespace sdl2
	{
		struct bitmap_font_t
		{
			int pixel_size;
			int n_chars;
			std::unique_ptr<sprite_t> sprite;
		};

		static SDL_Window *window;
		static SDL_Renderer *renderer;
		int font_size = 16;
		int terminal_width, terminal_height;
		std::vector<bitmap_font_t> fonts;

		void init(const rltk_mode_t mode)
		{
			terminal_width = mode.width;
			terminal_height = mode.height;

			SDL_Init(SDL_INIT_VIDEO);
			SDL_CreateWindowAndRenderer(terminal_width * font_size, terminal_height * font_size, 0, &window, &renderer);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
		}

		void stop()
		{
			SDL_Quit();
		}

		void present()
		{
			SDL_RenderPresent(renderer);
		}

		void load_bitmap_font(const char * filename, const int size_pixels, const int n_glyphs)
		{
			fonts.emplace_back(bitmap_font_t{ size_pixels, n_glyphs, std::make_unique<sprite_t>(renderer, filename) });
		}

		const auto BLANK_SRC_X = (219 % 16);
		const auto BLANK_SRC_Y = (219 / 16);

		void present_console(const std::vector<vchar_t> &console, const std::vector<color_t> &foreground, const std::vector<color_t> &background, const int &w, const int &h)
		{
			// Clear the screen
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			auto x = 0;
			auto y = 0;
			for (auto i = 0; i<terminal_width * terminal_height; ++i) {
				const auto glyph = console[i].glyph;
				const auto src_x = (glyph % 16) * font_size;
				const auto src_y = (glyph / 16) * font_size;

				fonts[0].sprite->render_subsprite(renderer, font_size, font_size, x*font_size, y*font_size, BLANK_SRC_X * font_size, BLANK_SRC_Y * font_size, background[i]);
				fonts[0].sprite->render_subsprite(renderer, font_size, font_size, x*font_size, y*font_size, src_x, src_y, foreground[i]);

				++x;
				if (x >= terminal_width) {
					x = 0;
					++y;
				}
			}
		}
	}
}
