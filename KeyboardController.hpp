#pragma once
#include "Game.hpp"
#include "ECS.hpp"
#include "Components.hpp"

class KeyboardController : public Component {

public:
	TransformComponent* transform;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override {

		//Falls eine Taste grdrückt wird
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym)
			{
				//Falls W gedrückt wurde, die Geschwindigkeit des Characters auf der y-Achse auf -1 setzen,
				//um ihn nach oben zu bewegen
			case SDLK_w:
				transform->velocity.y = -1;
				SDL_Log("w pressed");
				break;

				//Falls A gedrückt wurde, die Geschwindigkeit des Characters auf der x-Achse auf -1 setzen,
				//um ihn nach links zu bewegen
			case SDLK_a:
				transform->velocity.x = -1;
				SDL_Log("a pressed");
				break;

				//Falls S gedrückt wurde, die Geschwindigkeit des Characters auf der y-Achse auf 1 setzen,
				//um ihn nach unten zu bewegen
			case SDLK_s:
				transform->velocity.y = 1;
				SDL_Log("s pressed");
				break;

				//Falls d gedrückt wurde, die Geschwindigkeit des Characters auf der x-Achse auf 1 setzen,
				//um ihn nach rechts zu bewegen
			case SDLK_d:
				transform->velocity.x = 1;
				SDL_Log("d pressed");
				break;
			default:
				break;
			}
		}

		//Falls eine Taste losgelassen wird
		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym)
			{

				//Geschwindigkeit auf y-Achse auf 0 setzen
			case SDLK_w:
				transform->velocity.y = 0;
				break;

				//Geschwindigkeit auf s-Achse auf 0 setzen
			case SDLK_a:
				transform->velocity.x = 0;
				break;

				//Geschwindigkeit auf y-Achse auf 0 setzen
			case SDLK_s:
				transform->velocity.y = 0;
				break;

				//Geschwindigkeit auf x-Achse auf 0 setzen
			case SDLK_d:
				transform->velocity.x = 0;
				break;
			default:
				break;
			}
		}
	}

};