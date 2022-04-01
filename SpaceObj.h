#pragma once

#include <SDL.h>
#include <SDL_image.h>

class SpaceObj
{
public:
	int getPosX();
	int getPosY();

private:
	SDL_Rect posRect;
	int posX;
	int	posY;
	int velocity;

};

