/*
 * RLTK2 - The Roguelike Toolkit.
 * (c) 2018 Herbert Wolverson (aka Bracket Productions), all rights reserved.
 * Licensed under the MIT license.
 * If you use this toolkit, please include a credit and link to my page.
 */

/*
 * This is the main C++ entry point to the windowing API. It is deliberately C-like to
 * facilitate integration with other bindings. It also imports more headers than it
 * strictly needs, so as to expose the whole API.
 */

#pragma once

#include "rltk_modes.h"
#include "impl/color.hpp"

/*
 * In C++ bindings, everything in this library is nested inside the RLTK library.
 */
namespace rltk
{
	/*
	 * Basic initializer. Starts the library with the specified back-end.
	 * Returns: 
	 *		-1 if not using a default terminal.
	 *		The ID# of the root terminal is you are using one (it'll always be zero).
	 */
	int init(const rltk_mode_t new_mode);

	/*
	 * Cleanup all RLTK-related resources, close windows and exit gracefully.
	 */
	void stop();

	/*
	 * The default main loop.
	 */
	void main_loop(void (* fun_ptr)(bool *));

	/*
	 * Sets the current terminal for output
	 */
	void set_terminal(const int t);

	/*
	 * Retrieves the current output terminal. Relatively unlikely that you'll need to use this.
	 */
	int get_terminal();

	/* 
	 * Retrieves the current console dimensions.
	 */
	void get_dimensions(int * width, int * height);

	/*
	 * Clear the screen with no specified color, so black background/white foreground.
	 */
	void cls();

	/* 
	 * Clear the screen with specified colors.
	 */
	void cls(const color_t &fg, const color_t &bg);

	/*
	 * Provides support for outputting a string at a given location.
	 */
	void print_at(const int x, const int y, const char * text);

	/*
	 * Provides support for outputting a string at a given location, with specified colors.
	 */
	void print_at(const int x, const int y, const color_t fg, const color_t bg, const char* text);

	/*
	* Provides support for outputting a string at a given location, with specified colors.
	*/
	void wprint_at(const int x, const int y, const color_t fg, const color_t bg, const wchar_t * text);

	/*
	 * Provides support for setting a single character.
	 */
	void set_char(const int x, const int y, const color_t fg, const color_t bg, const int glyph);

	/*
	* Provides support for setting a single unicode character.
	*/
	void set_wchar(const int x, const int y, const color_t fg, const color_t bg, const wchar_t * glyph);

	/*
	 * Display the current screen to the world.
	 */
	void present();

	/*
	 * Loads a bitmap font into the SDL subsystem
	 */
	void load_bitmap_font(const char * filename, const int size_pixels, const int n_glyphs);
}