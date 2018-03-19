#pragma once

namespace rltk {
	const wchar_t * get_cp_mapping(const int n);
	int get_unicode_as_cp(const wchar_t c);
	int add_unicode_mapping(const wchar_t c);
}
