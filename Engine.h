#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

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
	

private:
	
	SDL_Rect winRect;
	SDL_Window* window;
	SDL_Surface* winSurface;
	SDL_Texture* winTexture;
	SDL_Renderer* winRenderer;
	SDL_Event ev;
	bool isRunning;
};

