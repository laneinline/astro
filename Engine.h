#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Engine
{
public: 
	Engine();
	~Engine();
	void init();
	void processInput();
	void updade();
	void draw();
private:
	
	SDL_Rect winRect;
	SDL_Window* window;
	SDL_Surface* winSurface;
	SDL_Event ev;
	bool isRunning;
};

