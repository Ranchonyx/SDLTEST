#include "Map.hpp"
#include "TextMan.hpp"
#include <fstream>
//#include "Serializer.hpp"

#pragma region fallbackMapBuffer

int fallbackMapBuffer[20][25] = {
	{0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,},
	{0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,},
	{0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,},
	{0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,},
	{0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,},
	{0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,},
	{0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,},
	{0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,},
	{0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,},
	{0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,},
	{0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,},
	{0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,},
	{0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,},
	{0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,},
	{0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,},
	{0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,},
	{0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,},
	{0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,},
	{0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,},
	{0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,},
};

#pragma endregion

Map::Map() {
	dirt = TextMan::LoadTexture("assets/tiles/dirt.png");
	grass = TextMan::LoadTexture("assets/tiles/grass.png");
	water = TextMan::LoadTexture("assets/tiles/water.png");
	gravel = TextMan::LoadTexture("assets/tiles/gravel.png");
	path = TextMan::LoadTexture("assets/tiles/path.png");
	lava = TextMan::LoadTexture("assets/tiles/lava.png");
	placeholder = TextMan::LoadTexture("assets/tiles/placeholder.png");

	//LoadMap(lvl1);

	LoadMapFromFile("assets/maps/level1.mmap");

	src.x = src.y = 0;
	src.w = dest.w = 32;
	src.h = dest.h = 32;

	dest.x = dest.y = 0;
	Vector2D* tpos = new Vector2D(10, 10);
	DrawTile(tpos, 2);
};

void Map::LoadMapFromFile(const char* path) {
	std::ifstream mapstream(path, std::ifstream::in);
	if (!mapstream.is_open()) {
		//Fallback, map doesnt exist
		LoadMap(fallbackMapBuffer);
		printf("Map \" %s \" doesn't exist! Falling back to default map.", path);
	}
	else {
		//Map does exist
		printf("Map \" %s \" exists! Continuing with loading process.", path);
		for (int row = 0; row < 20; row++) {
			for (int col = 0; col < 25; col++) {
				mapstream >> map[row][col];
			}
		}
	}
}

void Map::LoadMap(int arr[20][25]) {
	for (int row = 0; row < 20; row++) {
		for (int col = 0; col < 25; col++) {
			map[row][col] = arr[row][col];
		}
	}
}

void Map::DrawMap() {
	int type = 0;

	for (int row = 0; row < 20; row++) {
		for (int col = 0; col < 25; col++) {
			type = map[row][col];

			dest.x = col * 32;
			dest.y = row * 32;

			switch (type) {
			case 0:
				TextMan::Draw(dirt, src, dest);
				break;
			case 1:
				TextMan::Draw(grass, src, dest);
				break;
			case 2:
				TextMan::Draw(water, src, dest);
				break;
			case 3:
				TextMan::Draw(gravel, src, dest);
				break;
			case 4:
				TextMan::Draw(path, src, dest);
				break;
			case 5:
				TextMan::Draw(lava, src, dest);
				break;
			case 6:
				TextMan::Draw(placeholder, src, dest);
				break;
			default:
				TextMan::Draw(placeholder, src, dest);
				break;
			}
		}
	}
}

void Map::DrawTile(Vector2D* position, int tileID) {
	for (int row = 0; row < 20; row++) {
		dest.y = row * 32;
		printf("\nDest Y = %i", dest.y);
		printf("\nPos Y = %i", position->getY() * 32);

		if (dest.x == position->getX() * 32) {
			printf("\n x correct");
		}

		for (int col = 0; col < 25; col++) {
			dest.x = col * 32;
		}
	}

	for (int row = 0; row < 20; row++) {
		for (int col = 0; col < 25; col++) {
			dest.x = col * 32;
			dest.y = row * 32;

			switch (tileID) {
				printf("\nDrawing %i at DestRect(%i, %i)", tileID, position->getX() * 32, position->getY() * 32);
			case 0:
				TextMan::Draw(dirt, src, dest);
				break;
			case 1:
				TextMan::Draw(grass, src, dest);
				break;
			case 2:
				TextMan::Draw(water, src, dest);
				break;
			case 3:
				TextMan::Draw(gravel, src, dest);
				break;
			case 4:
				TextMan::Draw(path, src, dest);
				break;
			case 5:
				TextMan::Draw(lava, src, dest);
				break;
			case 6:
				TextMan::Draw(placeholder, src, dest);
				break;
			default:
				TextMan::Draw(placeholder, src, dest);
				break;
			}
		}
	}
}