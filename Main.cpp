//Die SDL-Entwicklungsbibliothek einbinden
#include "SDL.h"

//Game.h, die Game-Headerdatei mit Spielelogik einbinden
#include "Game.hpp"

//Das eigentliche Spiel "game" als Variable deklarieren
Game* game = nullptr;


//Haupteintrittspunkt f�r das Programm
int main(int argc, char* args[]) {

	SDL_Log("Starting");

	//Initialisieren der "game" Variable
	game = new Game();

	//Spiel initialisieren und in 800Pixel * 600Pixel Dimensionen ohne Vollbild starten
	game->init("Facharbeit Test Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	//Solange die Methode "running" der "Game"-Klasse true zur�ckgibt, die Hauptmethoden des Spiels ausf�hren
	while (game->running()) {

		//Bildschirmupdate start setzen
		game->setFrameStart();

		//Interne SDL-Events, wie zum Beispiel schlie�en des Fensters verarbeiten
		game->handleEvents();

		//Den internen Updatezyklus des Spiels ausf�hren
		game->update();

		//Texturen und Sprites, auf den Bildschirm zeichnen
		game->render();

		//Frametime, die dauer des momentane Updatezyklus berechnen
		game->computeFrameTime();

		//Daf�r sorgen, dass Updatezyklen durchschnittlich 60 Bilder pro Sekunde betragen (FPS)
		game->runFrameDelay();
	}

	SDL_Log("Game quitting");

	//Wenn die Methode "running" der "Game"-Klasse nicht mehr true zur�ckgibt,
	//Das SDL-Fenster schlie�en und den SDL-Renderer l�schen, danach die Anwendung schlie�en
	game->clean();

	exit(0);
	return 0;
}