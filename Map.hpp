#pragma once
#include "Game.hpp"
#include "Vector2D.hpp"

class Map {
public:

	Map();
	~Map();

	void LoadMap(int arr[20][25]);
	void LoadMapFromFile(const char* path);
	void DrawMap();
	void DrawTile(Vector2D* position, int tileID);

private:
	int map[20][25];
	SDL_Rect src, dest;

	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;
	SDL_Texture* gravel;
	SDL_Texture* path;
	SDL_Texture* lava;
	SDL_Texture* placeholder;
};