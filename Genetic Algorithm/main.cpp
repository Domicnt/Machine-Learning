#include "stdafx.h"

void show(Net *net, Game game)
{
	while (true)
	{
		if (std::size(net->amount) > 0) {
			auto n = *net;
			game.run(n, true, 1);
		}
	}
}

int main()
{	
	//set up sdl
	SDLWrapper sdl;

	//seed random function
	srand(time(nullptr));
	
	//set up game
	Game game(&sdl, 32);

	//set up algorithm
	static Genetic genetic(100);
	
	//drawing thread
	std::thread thr2(show, &genetic.best, std::ref(game));//make lambda function
	
	//algorithm thread
	std::thread thr1(&Genetic::run, &genetic, game);//algorithm is in another thread so that input can be handled in main thread
	
	//handle sdl in main thread bc it doesn't like multi-threading
	while (!sdl.quit)
	{
		sdl.update();
	}
	return 0;
}