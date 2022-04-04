#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iterator>
#include <map>

#include "SpaceObj.h"
#include "Asteroid.h"
#include "Bullet.h"


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
	

private:

	std::map <std::string, int> keysPressed;
	
	int prevTime;
	int currentTime;
	int deltaTime;
	int lag;

	SDL_Rect winRect;
	SDL_Window* window;
	SDL_Renderer* winRenderer;

	SDL_Rect renderRect; // TODO  handle pointers somehow another, i'm to tired to do it now, that is dumb solution

	SDL_Event ev;

	const Uint8* keyState;
	SDL_Point mousePos;
	double mouseAng;

	bool isRunning;


	SpaceObj asteroid[10];
	int asteroidQuant;

	SpaceObj background;
	SpaceObj spaceship;

	Bullet bullet[250];
	int bulletQuant ;

	SpaceObj crosshair;


};

