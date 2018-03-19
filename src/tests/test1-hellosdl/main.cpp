/*
* RLTK2 - The Roguelike Toolkit.
* (c) 2018 Herbert Wolverson (aka Bracket Productions), all rights reserved.
* Licensed under the MIT license.
* If you use this toolkit, please include a credit and link to my page.
*/

/*
 * Test 1 - Hello Curses
 * Produces a simple Curses window, and says "hello world" in it.
 */

#include "../../rltk_main/rltk.hpp"
#include <cwchar>
#include "../../rltk_main/impl/cp437.hpp"
#include "../../rltk_main/impl/sdl2-backend/sdl2.hpp"

using namespace rltk;

int root_terminal;
const wchar_t * good_day_russian = L"Добрый день, по-русски";

void mymain(bool * quitting)
{
	set_terminal(root_terminal);
	cls();

	int w, h;
	get_dimensions(&w, &h);

	print_at(0, 0, "Hello CP437 World!");
	print_at(0, 2, YELLOW, BLACK, "This should be 2 lines down; in yellow!");
	print_at(0, 3, MAGENTA, BLUE, "This should be 3 lines down; with a magenta foreground and blue background.");
	print_at(0, h-1, WHITE, BLACK, "Press any key to quit.");
	wprint_at(0, 4, RED, WHITE, L"ßracket ¶roductions");
	wprint_at(0, 5, YELLOW, RED, good_day_russian);

	print_at(0, 7, YELLOW, BLACK, "Here is a CP437 Character Map:");
	auto x = 0;
	auto y = 8;
	for (auto i=0; i<255; ++i)
	{
		set_char(x, y, WHITE, BLACK, i);
		++x;
		if (x > 15)
		{
			x = 0;
			++y;
		}
	}

	*quitting = false;
}

int main()
{
	const rltk_mode_t mode = { SDL, true, 80, 26 };
	root_terminal = init(mode);
	//load_bitmap_font("assets/terminal16x16.png", 16, 256);

	// A curses-only unicode example
	for (size_t i=0; i<wcslen(good_day_russian); ++i)
	{
		add_unicode_mapping(good_day_russian[i]);
	}
	sdl2::build_bitmap_font_from_ttf("assets/consola.ttf", 16, 512);

	main_loop(mymain);
	return 0;
}