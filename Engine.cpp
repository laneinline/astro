#include "Engine.h"
#include "Asteroid.h"
#include <iostream>

// copy SDL2 directory into project folder
// create everything in the following order:
// Initialize SDL by exeuting SDL_Init(); 
// Create the SDL window by executing SDL_CreateWindow();
// Create the SDL renderer by executing SDL_CreateRenderer(); 
// Create the texture… 

Engine::Engine(int width, int height)
{
	isRunning = true;
	
	preInit(width,height);
	init();
	background = SpaceObj(winRenderer, 0, 0, "img/background.png");
	asteroid1 = SpaceObj(winRenderer, 100,100, "img/big_asteroid.png");
	

}

Engine::~Engine()
{
	isRunning = false;


	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void Engine::preInit(int width, int height)
{
	winRect.x = 0; //window dimensions
	winRect.y = 0;
	winRect.w = 640;
	winRect.h = 480;
	if (width >= 320 && width < 8500) winRect.w = width;
	else { std::cout << "Error creating window: window width is not supported" << std::endl; }
	if (height >= 240 && height < 4500) winRect.h = height;
	else { std::cout << "Error creating window: window height is not supported" << std::endl; }

}

void Engine::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { std::cout << "Video initialization Error" << SDL_GetError() << std::endl; }
	else {
		window = SDL_CreateWindow("that is window title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winRect.w, winRect.h, SDL_WINDOW_SHOWN);
		if (window == NULL) { std::cout << "Windwow creation error" << SDL_GetError() << std::endl; }
		else {
			std::cout << "Window created, size: w: " << winRect.w << " h: " << winRect.h << std::endl;

			winRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (winRenderer == NULL) { std::cout << "Error creating Renderer" << std::endl;; }
			else {
				std::cout << "Renderer created sucessfully" << std::endl;;

			}//end of renderer
		}// end of window
	}//end of Init
}


void Engine::processInput()
{
	//std::cout << "Processing input..." << std::endl;
	
	while (SDL_PollEvent(&ev)) {//handle  window close button
		if (ev.type == SDL_QUIT) {
			isRunning = false; };

		if (ev.type == SDL_MOUSEBUTTONDOWN) { //TODO somewhere here mouse click locks program
			SDL_GetMouseState(&mousePos.x, &mousePos.y);

			if (ev.button.button == SDL_BUTTON_LEFT) {
				std::cout << " Left mouse button down at: " << mousePos.x << " x " << mousePos.y << std::endl;
			}
			else if (ev.button.button == SDL_BUTTON_MIDDLE) {
				std::cout << " Middle mouse button down at: " << mousePos.x << " x " << mousePos.y << std::endl;
			}
			else if (ev.button.button == SDL_BUTTON_RIGHT) {
				std::cout << " Right mouse button down at: " << mousePos.x << " x " << mousePos.y << std::endl;
			}

		}
		
	}

	keyState = SDL_GetKeyboardState(NULL);

	if (keyState[SDL_SCANCODE_UP]) {
		std::cout << " Up " << std::endl;
	}

	if (keyState[SDL_SCANCODE_DOWN]) {
		std::cout << " Down " << std::endl;
	}

	if (keyState[SDL_SCANCODE_LEFT]) {
		std::cout << " Left " << std::endl;
	}

	if (keyState[SDL_SCANCODE_RIGHT]) {
		std::cout << " Right " << std::endl;
	}
		

}

void Engine::update()
{
	//std::cout << "Calculating objects in world..." << std::endl;
}

void Engine::draw()
{
	//std::cout << "Render everything and out to display ..." << std::endl;

	SDL_RenderClear(winRenderer);

	SDL_RenderCopy(winRenderer, background.getTexture(), NULL, NULL);
	SDL_RenderCopy(winRenderer, asteroid1.getTexture(),NULL, &asteroid1.posRect);

	SDL_RenderPresent(winRenderer);

}

void Engine::run()
{
	while (isRunning) {//start of main loop
		processInput();
		update();
		draw();
	}//end of main loop



}
