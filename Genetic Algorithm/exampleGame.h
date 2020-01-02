#pragma once
#include "stdafx.h"

class Game
{
public:
	SDLWrapper* sdl;
	
	SDL_Rect player;
	double playerY;
	
	SDL_Rect ball;
	double ballY;
	double ballX;
	double ballVelY;
	double ballVelX;

	double speed;

	int steps;

	Game(SDLWrapper* SDL, int Speed);
	void reset();
	bool step(Net &net);
	void run(Net &net, bool drawing, int amount);//runs game
	std::thread thread(Net& net, int amount);
	
	void draw(Net net);
};