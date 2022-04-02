#include <SDL.h>
#include <iostream>
#include "Engine.h"


int main(int args, char *argv[]) {

	Engine engine = Engine(640,480);
	engine.run();

	//TODO make timer 

	

	return 0;
}