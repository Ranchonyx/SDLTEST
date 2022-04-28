#include "GameObject.hpp"
#include "TextMan.hpp"
#include "Vector2D.hpp"

GameObject::GameObject(const char* name, const char* textureSheet, Vector2D* loc, int scale) {
	objectTexture = TextMan::LoadTexture(textureSheet);
	location = loc;
	scaleFactor = scale;
}

void GameObject::Update() {
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = location->x;
	destRect.y = location->y;
	destRect.w = srcRect.w * scaleFactor;
	destRect.h = srcRect.h * scaleFactor;
}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, objectTexture, &srcRect, &destRect);
}