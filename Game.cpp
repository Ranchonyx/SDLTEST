#include "Game.hpp"
#include "SDL_image.h"
#include "TextMan.hpp"
#include "Map.hpp"
#include "ECS.hpp"
#include "Components.hpp"
#include "Collision.hpp"


#define null NULL


Map* map;
Vector2D* tpos = new Vector2D(10.0f, 10.0f);
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Manager manager;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

Game::Game() {
}

Game::~Game() {
	clean();
}

void Game::init(const char* title, int x, int y, int w, int h, bool fullscreen) {
	int flags = 0;

	fullscreen ? flags = SDL_WINDOW_FULLSCREEN : flags = SDL_WINDOW_SHOWN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "[--- + ---] SDL Subsystem initialized successfully." << std::endl;

		window = SDL_CreateWindow(title, x, y, w, h, flags | SDL_WINDOW_OPENGL);

		if (window) {
			std::cout << "[--- + ---] SDL Window created successfully." << std::endl;
		} else {
			std::cout << "[--- ! ---] SDL Window not created successfully.";
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer) {
			std::cout << "[--- + ---] SDL Renderer created successfully." << std::endl;
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		} else {
			std::cout << "[--- ! ---] SDL Renderer not created successfully.";
			exit(0);
		}

		isRunning = true;

		secondTimer.start();
		fps.start();
	} else {
		isRunning = false;
	}

	map = new Map();

	//ECS Impl



	player.addComponent<TransformComponent>(0, 0, 32, 32, 2);
	player.addComponent<SpriteComponent>("assets/sprites/enemy.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1, true);
	wall.addComponent<SpriteComponent>("assets/tiles/placeholder.png");
	wall.addComponent<ColliderComponent>("wall");

}

//Den Anfang eines Updatezyklus setzen
void Game::setFrameStart() {
	frameStart = SDL_GetTicks();
}

//Die Dauer des aktuellen Updatezyklus berechnen
void Game::computeFrameTime() {
	frameTime = SDL_GetTicks() - frameStart;
}

//Durch verzögerung in SDL dafür sorgen,
//das SDL durchschnittlich 60 Updatezyklen pro Sekunde durchführt
void Game::runFrameDelay() {
	if (__GLOBAL__FPS__ > frameTime) {
		SDL_Delay(__GLOBAL__FRAME__DELAY__ - frameTime);
	}
}

//Die momentanen Updatzyklen pro Sekunde berechnen
int Game::computeFps() {
	return (int)(count / (fps.get_ticks() / 1000.f));
}

//SDL-Ereignisse behandeln
void Game::handleEvents() {

		SDL_PollEvent(&event);

		switch (event.type) {
		//Falls ein SDL_QUIT (Stop) Signal durch das Schließen des Fensters gesendet wurde,
		//die "clean"-Methode ausführen
		case SDL_QUIT:
			clean();
			isRunning = false;
			break;
		default:
			break;
		}
}

//Einen Updatezyklus ausführen
void Game::update() {
	count++;
	//SDL_Log("Tick: %i, FPS: %i", (count), (computeFps()));

	manager.refresh();
	manager.update();

	if (Collision::AABB(player.getComponent<ColliderComponent>().collider, wall.getComponent<ColliderComponent>().collider)) {
		
		/*
		Vector2D vel = player.getComponent<TransformComponent>().velocity;
		
		if (vel.x > vel.y) {
			player.getComponent<TransformComponent>().velocity = { vel.x - 0.5f, vel.y };
			player.getComponent<TransformComponent>().velocity = { 0, 0 };
		}
		else
		{
			player.getComponent<TransformComponent>().velocity = { vel.x, vel.y - 0.5f };

			player.getComponent<TransformComponent>().velocity = { 0, 0 };
		}
		*/

		std::cout << "Kollision nicht implementiert!" << std::endl;
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	//map->DrawTile(tpos, 2);

	map->DrawMap();
	
	manager.draw();

	SDL_RenderPresent(renderer);
}

//Anwendung "säubern", Fenster schließen, Renderer löschen und die Anwendung beenden.
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "[--- * ---] Shutting down SDL, quitting.";
}