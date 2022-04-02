#pragma once
#include "SpaceObj.h"

class Bullet :virtual public SpaceObj
{
public:
    //Bullet(void);
    Bullet(SDL_Renderer* renderer, int x, int y, std::string path) ;

    void move(SDL_Rect boundary) ;



};

