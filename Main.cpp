#include "SDL.h"
#include "Game.hpp"
Game* game = nullptr;

int main(int argc, char* args[]) {
	game = new Game();

	game->init("Facharbeit Test Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (game->running()) {
		game->setFrameStart();

		game->handleEvents();
		game->update();
		game->render();

		game->computeFrameTime();

		game->runFrameDelay();
	}

	printf("Game quitting");

	game->clean();
	exit(0);
	return 0;
}