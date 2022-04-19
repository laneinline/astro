#include "Bullet.h"

Bullet::Bullet():SpaceObj() {}


Bullet::Bullet(SDL_Renderer* renderer, int x, int y, std::string path) : SpaceObj(renderer,  x, y,  path) 
{
	
}



void Bullet::move(SDL_Rect boundary)
{
	posRect.x += velocity * cos(angle * 3.1415 / 180); //cpp cosinus in RADIANS
	if (posRect.x + posRect.w > boundary.w) {
		exist = false;
	}
	if (posRect.x < boundary.x) {
		exist = false;
	}
	//std::cout << " angle : " << angle << " cos(angle) " << cos(angle) << std::endl;
	posRect.y += velocity * sin(angle * 3.1415 / 180);

	//std::cout << "posRect.y " << posRect.y << " boundary.y " << boundary.y << std::endl;// y - top left corner
	//std::cout << "posRect.h " << posRect.h << " boundary.h " << boundary.h << std::endl;// y - top left corner
	if (posRect.y < boundary.y) {
		exist = false;
	}
	if ((posRect.y + posRect.h) > boundary.h) {
		exist = false;
	}
}