#include "sprite.hpp"

sprite_t::sprite_t(SDL_Renderer *renderer, const char * filename) {
	image_ = IMG_Load(filename);
	if (!image_)
	{
		printf("IMG_Load Error: %s\n", IMG_GetError());
	}
	else {
		tex_ = SDL_CreateTextureFromSurface(renderer, image_);
	}
}

sprite_t::sprite_t(SDL_Renderer *renderer, SDL_Surface * surface) {
	tex_ = SDL_CreateTextureFromSurface(renderer, surface);
}

void sprite_t::display(SDL_Renderer *renderer) const
{
	SDL_Rect dest = { 200, 100, 200, 200 };
	SDL_RenderCopy(renderer, tex_, nullptr, &dest);
}

uint8_t color_to_byte(const float c)
{
	return static_cast<uint8_t>(c * 255.0f);
}

void sprite_t::render_subsprite(SDL_Renderer *renderer, const int &width, const int &height, const int &x, const int &y, const int &src_x, const int &src_y, const rltk::color_t color) const
{
	SDL_Rect dest = { x, y, width, height };
	SDL_Rect src = { src_x, src_y, width, height };
	SDL_SetTextureColorMod(tex_, color_to_byte(color.red), color_to_byte(color.green), color_to_byte(color.blue));
	SDL_RenderCopy(renderer, tex_, &src, &dest);
}

sprite_t::~sprite_t() {
	SDL_DestroyTexture(tex_);
	SDL_FreeSurface(image_);
}