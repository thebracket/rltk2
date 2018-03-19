#pragma once
#include <string>

namespace rltk {
	const wchar_t * get_cp_mapping(const int n);
	int get_unicode_as_cp(const wchar_t c);
	int add_unicode_mapping(const wchar_t c);
	size_t get_registered_items_size();
	std::wstring get_unicode(const int n);
}
