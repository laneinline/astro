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
	void updade();
	void draw();
	
	void run();

	void loadImage(std::string path);

	void crAsteroid(int size);
	void crSpaceship();
	void crBullet();
	

private:
	
	SDL_Rect winRect;
	SDL_Window* window;
	SDL_Surface* winSurface;
	SDL_Texture* winTexture;
	SDL_Renderer* winRenderer;
	SDL_Event ev;
	bool isRunning;

	SpaceObj asteroid1;
};

