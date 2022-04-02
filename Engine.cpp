#include "Engine.h"
#include "SpaceObj.h"
#include <iostream>

// copy SDL2 directory into project folder
// create everything in the following order:
// Initialize SDL by exeuting SDL_Init(); 
// Create the SDL window by executing SDL_CreateWindow();
// Create the SDL renderer by executing SDL_CreateRenderer(); 
// Create the texture… 

Engine::Engine(int width, int height)
{
	preInit(width,height); // load window size, timers =0 etc....
	init(); // SDL window initialization and basic Error checks
	
	



	background = SpaceObj(winRenderer, 0, 0, "img/background.png");
		
	asteroidQuant = sizeof(asteroid)/sizeof(asteroid[0]);
	std::cout << "asteroidquant: " << asteroidQuant;
	for (int i = 0; i < asteroidQuant; i++) {
		int randPos = rand() % 240 - rand() % 100;
		asteroid[i] = SpaceObj(winRenderer, randPos, randPos, "img/big_asteroid.png");
		asteroid[i].setAngle(rand()%360);
	}
	
	spaceship = SpaceObj(winRenderer, winRect.w / 2, winRect.h / 2, "img/spaceship.png");

	bulletQuant = sizeof(bullet) / sizeof(bullet[0]);
	std::cout << "bulletquant : " << bulletQuant;
	for (int i = 0; i < bulletQuant; i++) {
		bullet[i] =  Bullet(winRenderer, spaceship.getPosRect().x, spaceship.getPosRect().y, "img/bullet.png");
		bullet[i].destroy();
	}






}

Engine::~Engine()
{
	isRunning = false; //TODO LEAKS here , do something

	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void Engine::preInit(int width, int height)
{
	isRunning = true;

	winRect.x = 0; //window dimensions
	winRect.y = 0;
	winRect.w = 640;
	winRect.h = 480;
	if (width >= 320 && width < 8500) winRect.w = width;
	else { std::cout << "Error creating window: window width is not supported" << std::endl; }
	if (height >= 240 && height < 4500) winRect.h = height;
	else { std::cout << "Error creating window: window height is not supported" << std::endl; }

	prevTime = 0;
	currentTime = 0;
	deltaTime = 0;
}

void Engine::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { std::cout << " Error Video initialization " << SDL_GetError() << std::endl; }
	else {
		std::cout << "Video initialized sucessfully" << std::endl;

		window = SDL_CreateWindow("That is asteroids game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winRect.w, winRect.h, SDL_WINDOW_SHOWN);
		//std::cout << winRect.w<< " winrect h " << winRect.h;
		if (window == NULL) { std::cout << " Error Windwow creation" << SDL_GetError() << std::endl; }
		else {
			std::cout << "Window created, size: w: " << winRect.w << " h: " << winRect.h << std::endl;

			winRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);// | SDL_RENDERER_PRESENTVSYNC); // TODO vsync is slow  deletete it  after timer realization
			if (winRenderer == NULL) { std::cout << "Error Renderer creation " << std::endl; }
			else {
				std::cout << "Renderer created sucessfully" << std::endl;

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

		if (ev.type == SDL_MOUSEBUTTONDOWN) { //TODO  store mouse position  and move it to update()  somewhere here mouse click locks program move
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

}

void Engine::update()
{
	int ang; 
	for (int i = 0; i < asteroidQuant; i++) {
		asteroid[i].clearTexture();
		for (int y = 0; y < asteroidQuant; y++) {
			if (i != y) { 
				if (asteroid[i].isIntersect(asteroid[y].getCentrX(), asteroid[y].getCentrY(), asteroid[y].getRadius())) {
					
					//brownian movement
					ang = asteroid[y].getAngle();
					asteroid[y].setAngle(-1 * ang);
					ang = asteroid[i].getAngle();
					asteroid[i].setAngle(-1 * ang);
				}
			}

		}

		asteroid[i].isIntersect(spaceship.getCentrX(), spaceship.getCentrY(), spaceship.getRadius());
		//asteroid[i].isIntersect(asteroid[i+1].getCentrX(), asteroid[i + 1].getCentrY(), asteroid[i + 1].getRadius());
		asteroid[i].move(winRect);
	}

	spaceship.clearTexture();
	for (int i = 0; i < asteroidQuant; i++) {

		if (spaceship.isIntersect(asteroid[i].getCentrX(), asteroid[i].getCentrY(), asteroid[i].getRadius())) {
			asteroid[i].destroy();
		}
		
	}

	for (int i = 0; i < bulletQuant; i++) {
		if (bullet[i].exists()) {
			bullet[i].moveDestroy(winRect);
		}
	
	}
	
	//std::cout << "Calculating objects in world..." << std::endl;
	if (keyState[SDL_SCANCODE_UP]) {
		spaceship.move(winRect);

		std::cout << " Up " << std::endl;
	}

	if (keyState[SDL_SCANCODE_DOWN]) {
		
		std::cout << " Down " << std::endl;
	}

	if (keyState[SDL_SCANCODE_LEFT]) {
		spaceship.setAngle(spaceship.getAngle() - 5);
		std::cout << " Left " << std::endl;
	}

	if (keyState[SDL_SCANCODE_RIGHT]) {
		spaceship.setAngle(spaceship.getAngle() + 5);
		std::cout << " Right " << std::endl;
	}

	if (keyState[SDL_SCANCODE_SPACE]) {
		//spaceship.setAngle(spaceship.getAngle() + 5);

		//bullet shoot
		for (int i = 0; i < bulletQuant; i++) {
			if (! bullet[i].exists()) {
				bullet[i].create();
				bullet[i].setAngle(spaceship.getAngle());
				bullet[i].setPosX(spaceship.getPosRect().x);
				bullet[i].setPosY(spaceship.getPosRect().y);
				break;
			}
		}


		std::cout << " Space " << std::endl;
	}




}

void Engine::draw()
{
	//std::cout << "Render everything and out to display ..." << std::endl;

	SDL_RenderClear(winRenderer);

	SDL_RenderCopy(winRenderer, background.getTexture(), NULL, NULL);



	for (int i = 0; i < asteroidQuant; i++) {
		if (asteroid[i].exists()) {
			renderRect = asteroid[i].getPosRect();
			SDL_RenderCopy(winRenderer, asteroid[i].getTexture(), NULL, &renderRect);
		}

	}


	renderRect = spaceship.getPosRect();
	SDL_RenderCopyEx(winRenderer, spaceship.getTexture(), NULL, &renderRect, (double)(spaceship.getAngle() + 90), NULL, SDL_FLIP_NONE);


	for (int i = 0; i < bulletQuant; i++) {
		if (bullet[i].exists()) {
			renderRect = bullet[i].getPosRect();
			//SDL_Texture* tex = bullet[i].getTexture();
			//std::cout <<"still here" << " : " << renderRect.x << " : " << renderRect.y << " : " << renderRect.w << " : "<< renderRect.h;
			SDL_RenderCopy(winRenderer, bullet[i].getTexture(), NULL, &renderRect);

		}
	}



	SDL_RenderPresent(winRenderer);
	

}

void Engine::run()
{
	int lag = 0;

	while (isRunning) {//start of main loop
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = currentTime - prevTime;
		//std::cout << " delta time " << deltaTime << std::endl;
		
		lag += deltaTime;

		int millisecPerUpdate = 17;

		processInput();

		while (lag >= millisecPerUpdate) { //time loop  wait
			update();
			lag -= millisecPerUpdate;
		}		

		draw();





	}//end of main loop


}

