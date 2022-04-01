#include <SDL.h>
#include <iostream>
#include "Engine.h"


int main(int args, char *argv[]) {

	Engine engine = Engine(800,600);
	engine.run();

	Engine engine1 = Engine(800, 600);
	engine.run();
	

	return 0;
}