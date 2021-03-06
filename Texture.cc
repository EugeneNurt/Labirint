#include "Texture.h"
#include <SDL2/SDL_image.h>
#include <stdexcept>

#include <cassert>

Texture::Texture(std::shared_ptr<SDL_Renderer> &renderer, const char * filename)
: _renderer(renderer)
{
	std::shared_ptr<SDL_Surface> surf;

	surf = std::shared_ptr<SDL_Surface>(
		IMG_Load(filename),
		SDL_FreeSurface
	);

	if (surf == nullptr){
		throw std::runtime_error(
				std::string("?? ??????? ????????? ????????: ") +
				std::string(SDL_GetError()));
	}

	_width = surf->w;
	_height = surf->h;

	assert(_renderer != nullptr);

	_texture = std::shared_ptr<SDL_Texture>(
			SDL_CreateTextureFromSurface(_renderer.get(), surf.get()),
			SDL_DestroyTexture
	);

	if (_texture == nullptr){
		throw std::runtime_error(
				std::string("?? ??????? ??????? ????????: ") +
				std::string(SDL_GetError()));
	}

}

void Texture::draw(SDL_Rect *what, SDL_Rect *where) {
	SDL_RenderCopy(_renderer.get(), _texture.get(), what, where);
}
