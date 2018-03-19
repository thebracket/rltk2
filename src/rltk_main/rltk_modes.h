/*
* RLTK2 - The Roguelike Toolkit.
* (c) 2018 Herbert Wolverson (aka Bracket Productions), all rights reserved.
* Licensed under the MIT license.
* If you use this toolkit, please include a credit and link to my page.
*/

/*
 * C-friendly header providing initialization mode structs.
 */

#ifndef RLTK_MODES_H
#define RLTK_MODES_H

extern "C" {
	enum rltk_backend_mode_t { CURSES=0, SDL=1 };
	
	struct rltk_mode_t
	{
		rltk_backend_mode_t backend = CURSES;
		bool add_root_terminal = true;

		// Curses specific initialization

		// SDL-specific initialization
		int width = 80;
		int height = 25;
	};
}

#endif