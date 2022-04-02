#include "SpaceObj.h"
#include <iostream>
#include <cmath>

SpaceObj::SpaceObj()
{
}

SpaceObj::SpaceObj(SDL_Renderer *renderer, int x, int y, std::string path)
{
	//TODO add checks & handlers
	exist = true;

	path2img = path;
	
	posRect.x = x;
	posRect.y = y;

	angle = 0;
	velocity = 5;


	loadTexture(renderer);
	SDL_QueryTexture(texture,NULL,NULL,&posRect.w,&posRect.h);

	radius = posRect.w /2;

	std::cout  << std::endl;

	std::cout << typeid(this).name() << "posRect x: " << posRect.x << " y: " << posRect.y << " w: " << posRect.w << " h: " << posRect.h << " Radius : " << radius << std::endl;
}

SpaceObj::~SpaceObj()
{
	//SDL_DestroyTexture(texture);
	//texture = nullptr;
	//SDL_FreeSurface(surface);
	//surface = nullptr;

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

SDL_Rect SpaceObj::getPosRect()
{
	return posRect;
}

int SpaceObj::getAngle()
{
	return angle;
}

void SpaceObj::setAngle(int ang)
{	
	angle = ang%360;
	//std::cout << "angle : " << angle << " ang: " << ang << std::endl;	
}

int SpaceObj::getVelocity()
{
	return velocity;
}

int SpaceObj::getRadius()
{
	return radius;
}

void SpaceObj::move(SDL_Rect boundary)
{
	posRect.x += velocity * cos(angle * 3.1415 / 180); //cpp cosinus in RADIANS
	if (posRect.x + posRect.w > boundary.w) {
		posRect.x = 0;
	}
	if (posRect.x < boundary.x) {
		posRect.x = boundary.w - posRect.w;
	}
	//std::cout << " angle : " << angle << " cos(angle) " << cos(angle) << std::endl;
	posRect.y += velocity * sin(angle * 3.1415 / 180);

	//std::cout << "posRect.y " << posRect.y << " boundary.y " << boundary.y << std::endl;// y - top left corner
	//std::cout << "posRect.h " << posRect.h << " boundary.h " << boundary.h << std::endl;// y - top left corner
	if (posRect.y < boundary.y) {
		posRect.y = boundary.h - posRect.h;
	}
	if ((posRect.y + posRect.h) > boundary.h) {
		posRect.y = 0;
	}

}

bool SpaceObj::isIntersect(int x ,int y, int  collisionTargetRadius)
{
	bool intersect;
	centrX = getCentrX(); 
	centrY = getCentrY();

	//std::cout << " centrX: " << centrX << " centrY: " << centrY  << std::endl;
	// a^2 +b^2 = c^2 (c = radius my +  radiu target)
	if (
		((centrX - x) * (centrX - x))  // x size lenth^2
		+ ((centrY - y) * (centrY - y)) //y size lenth^2
		<= (radius * radius //radius my
			+ collisionTargetRadius * collisionTargetRadius) //radius target
		) {
		SDL_SetTextureColorMod(texture, 255, 0, 0);
		//angle *= -1;
		intersect = true;
	}
	else {
		intersect = false;
		//SDL_SetTextureColorMod(texture, 255, 255, 255);
	}
	return intersect;
}

int SpaceObj::getCentrX()
{
	return posRect.x + radius;
}

int SpaceObj::getCentrY()
{
	return posRect.y + radius;
}

void SpaceObj::clearTexture()
{
	SDL_SetTextureColorMod(texture, 255, 255, 255);
}

bool SpaceObj::exists()
{
	return exist;
}

void SpaceObj::destroy()
{
	exist = false;
}



