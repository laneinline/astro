#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Engine
{
public: 
	Engine();
	~Engine();
	void init();
	void processInput();
	void updade();
	void draw();
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

