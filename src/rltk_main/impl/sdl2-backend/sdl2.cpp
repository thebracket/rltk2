#include "sdl2.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "sprite.hpp"
#include <memory>
#include "../cp437.hpp"
#include <cassert>

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

			SDL_Init(SDL_INIT_EVERYTHING);
			TTF_Init();
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
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
			}
			SDL_RenderPresent(renderer);
		}

		void load_bitmap_font(const char * filename, const int size_pixels, const int n_glyphs)
		{
			fonts.emplace_back(bitmap_font_t{ size_pixels, n_glyphs, std::make_unique<sprite_t>(renderer, filename) });
		}

		void build_bitmap_font_from_ttf(const char * filename, const int size_pixels, const int n_glyphs)
		{
			typedef std::basic_string<Uint16, std::char_traits<Uint16>, std::allocator<Uint16> > u16string;

			TTF_Font * font = TTF_OpenFont(filename, size_pixels);
			if (font == nullptr)
			{
				printf("TTF_OpenFont: %s\n", TTF_GetError());
			}
			SDL_Color White = { 255, 255, 255 };
			SDL_Color Black = { 0, 0, 0 };

			/* SDL interprets each pixel as a 32-bit number, so our masks must depend
			on the endianness (byte order) of the machine */
			Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			rmask = 0xff000000;
			gmask = 0x00ff0000;
			bmask = 0x0000ff00;
			amask = 0x000000ff;
#else
			rmask = 0x000000ff;
			gmask = 0x0000ff00;
			bmask = 0x00ff0000;
			amask = 0xff000000;
#endif
			SDL_Surface * temp_surface = SDL_CreateRGBSurface(0, 16 * size_pixels, (n_glyphs/16) * size_pixels, 32, rmask, gmask, bmask, amask);
			SDL_FillRect(temp_surface, nullptr, 0x000000);

			const int glyph_count = get_registered_items_size();
			assert(glyph_count <= n_glyphs);

			auto x = 0;
			auto y = 0;
			for (auto i=0; i<glyph_count; ++i)
			{
				const auto text = get_unicode(i);
				u16string utext(text.begin(), text.end());
				const auto surface_glyph = TTF_RenderUNICODE_Blended(font, utext.c_str(), White);
				assert(surface_glyph != nullptr);
				SDL_Rect dst{ x * size_pixels, y * size_pixels, size_pixels, size_pixels };
				SDL_BlitSurface(surface_glyph, nullptr, temp_surface, &dst);
				SDL_FreeSurface(surface_glyph);

				++x;
				if (x > 15)
				{
					x = 0;
					y += 1;
				}
			}

			//SDL_SaveBMP(temp_surface, "temp.bmp");
			fonts.emplace_back(bitmap_font_t{ size_pixels, n_glyphs, std::make_unique<sprite_t>(renderer, temp_surface) });

			// Cleanup
			TTF_CloseFont(font);
			SDL_FreeSurface(temp_surface);
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

				// Render a background!
				SDL_Rect bgrect{ x*font_size, y*font_size, font_size, font_size };
				SDL_SetRenderDrawColor(renderer, color_to_byte(background[i].red), color_to_byte(background[i].green), color_to_byte(background[i].blue), 255);
				SDL_RenderFillRect(renderer, &bgrect);
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
