#pragma once

namespace rltk
{
	struct color_t
	{
		float red = 0.0f;
		float green = 0.0f;
		float blue = 0.0f;
	};

	const color_t BLACK{ 0.f, 0.f, 0.f };
	const color_t WHITE{ 1.f, 1.f, 1.f };
	const color_t RED{ 1.f, 0.f, 0.f };
	const color_t GREEN{ 0.f, 1.f, 0.f };
	const color_t BLUE{ 0.f, 0.f, 1.f };
	const color_t YELLOW{ 1.f, 1.f, 0.f };
	const color_t MAGENTA{ 1.f, 0.f, 1.f };
	const color_t CYAN{ 0.f, 1.f, 1.f };
}