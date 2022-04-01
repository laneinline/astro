#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class SpaceObj
{
public:
	SpaceObj();
	SpaceObj(SDL_Renderer* renderer, int x, int y, std::string path);
	~SpaceObj();


	SDL_Texture* getTexture();
	
	void loadTexture(SDL_Renderer* renderer);


	SDL_Rect getPosRect();
	int getAngle();
	void setAngle(int ang);
	
	int getSpeed();

	void move(SDL_Rect boundary);


private:

	std::string path2img;

	SDL_Surface *surface;
	SDL_Texture *texture;

	SDL_Rect posRect;
	int angle;
	int velocity;

};

