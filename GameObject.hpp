#pragma once
#include "Game.hpp"
#include "Vector2D.hpp"

class GameObject {
public:
	GameObject(const char* name, const char* textureSheet, Vector2D* loc, int scale = 1);
	~GameObject();

	void Update();
	void Render();

private:

	int scaleFactor;

	Vector2D* location;

	SDL_Rect srcRect, destRect;
	SDL_Texture* objectTexture;
};