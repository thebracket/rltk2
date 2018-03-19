#include "cp437.hpp"
#include <vector>
#include <map>
#include <cassert>
#include <string>

namespace rltk {
	/* This is the default CP437 map, moved to unicode. */
	std::vector<wchar_t> curses_map{
		L' ', L'☺', L'☻', L'♥', L'♦', L'♣', L'♠', L'•', L'◘', L'○', L'◙', L'♂', L'♀', L'♪', L'♫', L'☼',
		L'►', L'◄', L'↕', L'‼', L'¶', L'§', L'▬', L'↨', L'↑', L'↓', L'→', L'←', L'∟', L'↔', L'▲', L'▼',
		L' ', L'!', L'"', L'#', L'$', L'%', L'&',L'\'', L'(', L')', L'*', L'+', L',', L'-', L'.', L'/',
		L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9', L':', L';', L'<', L'=', L'>', L'?',
		L'@', L'A', L'B', L'C', L'D' ,L'E', L'F', L'G', L'H' ,L'I', L'J', L'K', L'L', L'M', L'N', L'O',
		L'P', L'Q', L'R', L'S', L'T' ,L'U', L'V', L'W', L'X' ,L'Y', L'Z', L'[',L'\\', L']', L'^', L'_',
		L'`', L'a', L'b', L'c', L'd' ,L'e', L'f', L'g', L'h' ,L'i', L'j', L'k', L'l', L'm', L'n', L'o',
		L'p', L'q', L'r', L's', L't' ,L'u', L'v', L'w', L'x' ,L'y', L'z', L'{', L'|', L'}', L'~', L'⌂',
		L'Ç', L'ü', L'é', L'â', L'ä' ,L'à', L'å', L'ç', L'ê' ,L'ë', L'è', L'ï', L'î', L'ì', L'Ä', L'Å',
		L'É', L'æ', L'Æ', L'ô', L'ö' ,L'ò', L'û', L'ù', L'ÿ' ,L'Ö', L'Ü', L'¢', L'£', L'¥', L'₧', L'ƒ',
		L'á', L'í', L'ó', L'ú', L'ñ' ,L'Ñ', L'ª', L'º', L'¿' ,L'⌐', L'¬', L'½', L'¼', L'¡', L'«', L'»',

		L'░', L'▒', L'▓', L'│', L'┤' ,L'╡', L'╢', L'╖', L'╕' ,L'╣', L'║', L'╗', L'╝', L'╜', L'╛', L'┐',
		L'└', L'┴', L'┬', L'├', L'─' ,L'┼', L'╞', L'╟', L'╚' ,L'╔', L'╩', L'╦', L'╠', L'═', L'╬', L'╧',
		L'╨', L'╤', L'╥', L'╙', L'╘' ,L'╒', L'╓', L'╫', L'╪' ,L'┘', L'┌', L'█', L'▄', L'▌', L'▐', L'▀',
		L'α', L'ß', L'Γ', L'π', L'Σ' ,L'σ', L'µ', L'τ', L'Φ' ,L'Θ', L'Ω', L'δ', L'∞', L'φ', L'ε', L'∩',
		L'≡', L'±', L'≥', L'≤', L'⌠' ,L'⌡', L'÷', L'≈', L'°', L'∙', L'∙', L'√', L'ⁿ', L'²', L'■', L' '
	};

	const wchar_t * get_cp_mapping(const int n)
	{
		if (n < curses_map.size())
			return &curses_map[n];
		return &curses_map[0];
	}

	std::wstring get_unicode(const int n)
	{
		std::wstring result;

		if (n < curses_map.size())
			result += curses_map[n];
		result += L'\0';

		return result;
	}

	static std::map<wchar_t, int> unimap;
	static bool made_unicode_map = false;

	static void build_unicode_map()
	{
		unimap.clear();
		auto i = 0;
		for (const auto &ch : curses_map)
		{
			unimap[ch] = i;
			++i;
		}
	}

	int get_unicode_as_cp(const wchar_t c)
	{
		if (!made_unicode_map)
		{
			made_unicode_map = true;
			build_unicode_map();
		}

		const auto finder = unimap.find(c);
		if (finder == unimap.end()) {
			assert(1 == 2, "Unable to find character " + c);
			return 0;
		}
		return finder->second;
	}

	int add_unicode_mapping(const wchar_t c)
	{
		const int result = curses_map.size();
		curses_map.emplace_back(c);
		build_unicode_map();
		return result;
	}

	size_t get_registered_items_size()
	{
		return curses_map.size();
	}
}
