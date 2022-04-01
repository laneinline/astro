#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "SpaceObj.h"

class Engine
{
public: 
	Engine(int width, int height);
	~Engine();

	void preInit(int width, int height);
	void init();
	
	void processInput();
	void update();
	void draw();
	
	void run();

	void crAsteroid(int size);
	void crSpaceship();
	void crBullet();
	

private:
	
	SDL_Rect winRect;
	SDL_Window* window;
	SDL_Renderer* winRenderer;
	SDL_Event ev;

	const Uint8* keyState;
	SDL_Point mousePos;

	bool isRunning;

	SpaceObj asteroid1;
	SpaceObj background;

};

