//Die SDL-Entwicklungsbibliothek einbinden
#include "SDL.h"

//Game.h, die Game-Headerdatei mit Spielelogik einbinden
#include "Game.hpp"

//Das eigentliche Spiel "game" als Variable deklarieren
Game* game = nullptr;


//Haupteintrittspunkt für das Programm
int main(int argc, char* args[]) {

	SDL_Log("Starting");

	//Initialisieren der "game" Variable
	game = new Game();

	//Spiel initialisieren und in 800Pixel * 600Pixel Dimensionen ohne Vollbild starten
	game->init("Facharbeit Test Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	//Solange die Methode "running" der "Game"-Klasse true zurückgibt, die Hauptmethoden des Spiels ausführen
	while (game->running()) {

		//Bildschirmupdate start setzen
		game->setFrameStart();

		//Interne SDL-Events, wie zum Beispiel schließen des Fensters verarbeiten
		game->handleEvents();

		//Den internen Updatezyklus des Spiels ausführen
		game->update();

		//Texturen und Sprites, auf den Bildschirm zeichnen
		game->render();

		//Frametime, die dauer des momentane Updatezyklus berechnen
		game->computeFrameTime();

		//Dafür sorgen, dass Updatezyklen durchschnittlich 60 Bilder pro Sekunde betragen (FPS)
		game->runFrameDelay();
	}

	SDL_Log("Game quitting");

	//Wenn die Methode "running" der "Game"-Klasse nicht mehr true zurückgibt,
	//Das SDL-Fenster schließen und den SDL-Renderer löschen, danach die Anwendung schließen
	game->clean();

	exit(0);
	return 0;
}