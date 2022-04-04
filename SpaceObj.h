#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
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
	
	int getVelocity();
	void setVelocity(int vel);
	int getRadius();

	virtual void move(SDL_Rect boundary);

	bool isIntersect(int x, int y, int collisionTargetRadius);

	int getCentrX();
	int getCentrY();
	void clearTexture();


	void setPosX(int x);
	void setPosY(int y);

	void create();
	bool exists();
	void destroy();

protected:

	std::string path2img;

	SDL_Surface *surface;
	SDL_Texture *texture;

	SDL_Rect posRect;

	int radius;
	int centrX;
	int centrY;

	int angle;
	int velocity;

	bool exist;

};

