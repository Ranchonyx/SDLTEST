#ifndef Game_hpp
#define Game_hpp

#define AutoString(s) std::string s = #s

#include <stdio.h>
#include <iostream>
#include "SDL.h"
#include "Timer.hpp"

class Game {
public:

	static SDL_Renderer* renderer;
	static SDL_Event event;

	Game();
	~Game();

	void init(const char* title, int x, int y, int w, int h, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	void setFrameStart();
	void runFrameDelay();
	void computeFrameTime();
	int computeFps();

	bool running() {
		return isRunning;
	}

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