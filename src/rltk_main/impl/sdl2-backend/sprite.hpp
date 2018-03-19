#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../color.hpp"

class sprite_t {
public:
	sprite_t(SDL_Renderer *renderer, const char * filename);
	sprite_t(SDL_Renderer *renderer, SDL_Surface * surface);
	~sprite_t();
	void display(SDL_Renderer *renderer) const;
	void render_subsprite(SDL_Renderer *renderer, const int &width, const int &height, const int &x, const int &y, const int &src_x, const int &src_y, const rltk::color_t color) const;

private:
	SDL_Texture * tex_ = nullptr;
	SDL_Surface * image_ = nullptr;
};

uint8_t color_to_byte(const float c);
