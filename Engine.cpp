#include "Engine.h"
#include <iostream>

// copy SDL2 directory into project folder
// create everything in the following order:
// Initialize SDL by exeuting SDL_Init(); 
// Create the SDL window by executing SDL_CreateWindow();
// Create the SDL renderer by executing SDL_CreateRenderer(); 
// Create the texture… 

Engine::Engine()
{
	//SDL_Window* window = nullptr;
	//SDL_Surface* winSurface = nullptr;
	//window = nullptr;
	//winSurface = nullptr;
	isRunning = true;


	if (SDL_Init(SDL_INIT_VIDEO) < 0) { std::cout << "Video initialization Error" << SDL_GetError() << std::endl; }
	else {
		window = SDL_CreateWindow("that is window title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
		if (window == NULL) { std::cout << "Windwow creation error" << SDL_GetError() << std::endl; }
		else {
			winSurface = SDL_GetWindowSurface(window);// window created
			while (isRunning) {//start of main loop
				while (SDL_PollEvent(&ev)) {//handle  window close button
					if (ev.type == SDL_QUIT) { isRunning = false; };
				}
				SDL_UpdateWindowSurface(window);
			}//end of main loop
		}
	}

}

Engine::~Engine()
{
	SDL_FreeSurface(winSurface);
	winSurface = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}
