#include "Game.hpp"
#include "SDL_image.h"
#include "TextMan.hpp"
#include "GameObject.hpp"
#include "Map.hpp"

GameObject* player;
Vector2D* startPos = new Vector2D(0, 0);

Map* map;
Vector2D* tpos = new Vector2D(10, 10);

SDL_Renderer* Game::renderer = nullptr;

Game::Game() {
}
Game::~Game() {
}

void Game::setFrameStart() {
	frameStart = SDL_GetTicks();
}
void Game::computeFrameTime() {
	frameTime = SDL_GetTicks() - frameStart;
}
void Game::runFrameDelay() {
	if (__GLOBAL__FPS__ > frameTime) {
		SDL_Delay(__GLOBAL__FRAME__DELAY__ - frameTime);
	}
}

int Game::computeFps() {
	return (count / (fps.get_ticks() / 1000.f));
}

void Game::init(const char* title, int x, int y, int w, int h, bool fullscreen) {
	//SDL Fenster-Flags

	int flags = 0;
	//Vollbild angegeben? dann die flags modden, andernfalls normal windowed
	fullscreen ? flags = SDL_WINDOW_FULLSCREEN : flags = SDL_WINDOW_SHOWN;
	printf("Initializing...\n");
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "[--- + ---] SDL Subsystem initialized successfully." << std::endl;

		window = SDL_CreateWindow(title, x, y, w, h, flags | SDL_WINDOW_OPENGL);
		if (window) {
			std::cout << "[--- + ---] SDL Window created successfully." << std::endl;
		}
		else {
			std::cout << "[--- ! ---] SDL Window not created successfully.";
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			std::cout << "[--- + ---] SDL Renderer created successfully." << std::endl;
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		else {
			std::cout << "[--- ! ---] SDL Renderer not created successfully.";
			abort();
		}

		//SDl ist korrekt gestartet
		isRunning = true;
		secondTimer.start();
		fps.start();
	}
	else {
		//SDl ist nicht korrekt gestartet
		isRunning = false;
	}

	player = new GameObject("Player", "assets/sprites/Player.png", startPos, 2);
	map = new Map();
}

void Game::handleEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		printf("\nEvent recieved!");
		switch (event.type) {
		case SDL_QUIT:
			clean();
			break;
		}
	}
}

void Game::update() {
	count++;
	printf("\n Tick: %i, FPS: %i", (count), (computeFps()));

	player->Update();
	map->DrawTile(tpos, 2);
}

void Game::render() {
	SDL_RenderClear(renderer);

	map->DrawMap();
	player->Render();

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "[--- * ---] Shutting down SDL, quitting.";
}