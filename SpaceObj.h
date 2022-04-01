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

	int getPosX();
	int getPosY();
	SDL_Texture* getTexture();
	
	void loadTexture(SDL_Renderer* renderer);

	SDL_Rect posRect;

private:

	std::string path2img;

	SDL_Surface *surface;
	SDL_Texture *texture;

	int posX;
	int	posY;


};

