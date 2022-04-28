#include "TextMan.hpp"
#include "SDL_image.h"

SDL_Texture* TextMan::LoadTexture(const char* texture) {
	SDL_Log("Loading texture: %s", texture);
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	

	return tex;
}

void TextMan::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}