#include "SpaceObj.h"
#include <iostream>

SpaceObj::SpaceObj()
{
}

SpaceObj::SpaceObj(SDL_Renderer *renderer, int x, int y, std::string path)
{
	//TODO add checks & handlers
	path2img = path;
	
	posRect.x = x;
	
	posRect.y = y;

	loadTexture(renderer);
	SDL_QueryTexture(texture,NULL,NULL,&posRect.w,&posRect.h);

	std::cout << typeid(this).name() << "posRect x: " << posRect.x << " y: " << posRect.y << " w: " << posRect.w << " h: " << posRect.h << std::endl;
}

SpaceObj::~SpaceObj()
{
	//SDL_DestroyTexture(texture);
	//texture = nullptr;
	//SDL_FreeSurface(surface);
	//surface = nullptr;

}



int SpaceObj::getPosX()
{
	return posX;
}

int SpaceObj::getPosY()
{
	return posY;
}

SDL_Texture* SpaceObj::getTexture()
{
	return texture;
}

void SpaceObj::loadTexture(SDL_Renderer* renderer)
{
		surface = IMG_Load(path2img.c_str());
		if (surface == NULL) {
			std::cout << typeid(this).name() << " SpaceObj Error loading image to surface" << IMG_GetError() << std::endl;
		}
		else {
			std::cout << typeid(this).name() << " SpaceObj Image loaded to surface sucessfully" << std::endl;
		}

		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL) {
			std::cout << typeid(this).name() << "Error loading surface to texture" << IMG_GetError() << std::endl;
		}
		else {
			std::cout << typeid(this).name() << " Texture created from surface sucessfully" << std::endl;
		}
		//SDL_FreeSurface(winSurface);

}


