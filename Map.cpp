#include "Map.hpp"
#include "TextMan.hpp"
#include <fstream>
//#include "Serializer.hpp"
bool drewn = false;
bool needsUpdate = false;

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
	SDL_Log("Loaded map from maps folder");

	src.x = src.y = 0;
	src.w = dest.w = 32;
	src.h = dest.h = 32;

	dest.x = dest.y = 0;
};

Map::~Map() {
	SDL_DestroyTexture(dirt);
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(water);
	SDL_DestroyTexture(gravel);
	SDL_DestroyTexture(path);
	SDL_DestroyTexture(lava);
	SDL_DestroyTexture(placeholder);

}

void Map::LoadMapFromFile(const char* path) {

	//Datenstrom zum lesen der Datei öffnen
	std::ifstream mapstream(path, std::ifstream::in);

	//Falls der Datenstrom nicht erfolgreich geöffnet wurde,
	//den fallbackBuffer, also eine Fallback-Map laden
	if (!mapstream.is_open()) {

		//Fallback, Karte existiert nicht!
		SDL_Log("Map \" %s \" doesn't exist! Falling back to default map.", path);
		LoadMap(fallbackMapBuffer);
	}
	else {

		//Karte existiert
		SDL_Log("Map \" %s \" exists! Continuing with loading process.", path);

		//Über alle Zellen in der Datei laufen und in die variable Map einlesen
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
	//Lokale Variable zum speichern der Zahl,
	//Je nach welcher der Boden gezeichnet werden soll
	int type = 0;

	//Über alle einzelnen Zellen (Zahlen) in der Datei laufen
	for (int row = 0; row < 20; row++) {
		for (int col = 0; col < 25; col++) {

			//Setze den typ auf die momentane Zelle
			type = map[row][col];


			dest.x = col * 32;
			dest.y = row * 32;

			//Je nach momentanem Typ die korrespondierende Textur zeichnen
			switch (type) {
			case 0:
				//Falls der Typ 0 ist, Erde zeichnen
				TextMan::Draw(dirt, src, dest);
				break;
			case 1:
				//Falls der Typ 1 ist, Gras zeichnen
				TextMan::Draw(grass, src, dest);
				break;
			case 2:
				//Falls der Typ 2 ist, Wasser zeichnen
				TextMan::Draw(water, src, dest);
				break;
			case 3:
				//Falls der Typ 3 ist, Kies zeichnen
				TextMan::Draw(gravel, src, dest);
				break;
			case 4:
				//Falls der Typ 4 ist, Pfad zeichnen
				TextMan::Draw(path, src, dest);
				break;
			case 5:
				//Falls der Typ 6 ist, Lava zeichnen
				TextMan::Draw(lava, src, dest);
				break;
			case 6:
				//Falls der Typ 6 ist, Platzhalter zeichnen
				TextMan::Draw(placeholder, src, dest);
				break;
			default:
				//Falls der Typ mit keinem der obigen übereinstimmt, den Platzhalter zeichnen
				TextMan::Draw(placeholder, src, dest);
				break;
			}
		}
	}
}

void Map::DrawTile(Vector2D* position, int tileID) {
	int x = position->x;
	int y = position->y;

	map[x][y] = tileID;
}