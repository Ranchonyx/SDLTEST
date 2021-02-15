#ifndef Game_hpp
#define Game_hpp

#include "SDL.h"
#include "SDL_opengl.h"
#include "Timer.hpp"
#include <stdio.h>
#include <iostream>

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int x, int y, int w, int h, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	static SDL_Renderer* renderer;

	void setFrameStart();
	void runFrameDelay();
	void computeFrameTime();
	int computeFps();

	bool running() { printf("Called running"); return isRunning; }

private:
	const int __GLOBAL__FPS__ = 60;
	const int __GLOBAL__FRAME__DELAY__ = (1000 / __GLOBAL__FPS__);
	int count = 0;
	int frameTime;
	bool isRunning;

	Timer fps;
	Timer secondTimer;
	Uint32 frameStart;
	SDL_Window* window;

protected:
};

#endif // !Game_hpp