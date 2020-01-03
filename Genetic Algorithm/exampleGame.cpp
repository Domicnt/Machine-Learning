#include "stdafx.h"

Game::Game(SDLWrapper* SDL, int Speed)
{
	sdl = SDL;
	
	player = {0, H / 2 - H / 10, W / 42, H / 10};
	playerY = player.y;

	speed = Speed;

	steps = 0;
	
	ball = { W / 2,H / 2,10,10 };
	ballX = ball.x;
	ballY = ball.y;
	double angle = fmod(rand(), .4 * M_PI) - M_PI * .45;
	ballVelX = 1;//(rand() % 2 * 2 - 1) * cos(angle);
	ballVelY = (rand() % 2 * 2 - 1) * sin(angle);
}

void Game::reset()
{
	player = { 0, H / 2 - H / 10, W / 42, H / 10 };
	playerY = player.y;

	steps = 0;
	
	ball = { W / 2,H / 2,10,10 };
	ballX = ball.x;
	ballY = ball.y;
	double angle = fmod(rand(), .4 * M_PI) - M_PI * .45;
	ballVelX = 1;// (rand() % 2 * 2 - 1)* cos(angle);
	ballVelY = (rand() % 2 * 2 - 1) * sin(angle);
}

bool Game::step(Net &net)
{
	net.neurons[0] = { double(playerY + player.h / 2), double(ballY + ball.h) };
	net.calculate();
	auto vel = (net.neurons[std::size(net.neurons) - 1][0] - .5) * 2 * speed;
	playerY += vel;
	player.y = int(playerY);

	if (player.y + player.h > H)
	{
		player.y = H - player.h;
		playerY = H - player.h;
	}
	else if (player.y < 0)
	{
		player.y = 0;
		playerY = 0;
	}
	
	ballX += ballVelX * speed;
	ballY += ballVelY * speed;
	if (ballX + ball.w > W)
	{
		ballVelX *= -1;
		ballX = W - ball.w;
	}
	else if (ballX < player.w)
	{
		if (player.y < ballY + ball.h && player.y + player.h > ballY )
		{
			ballX = player.w;
			ballVelX *= -1;
			steps++;
			net.fitness++;
		}
		else 
		{
			net.fitness -= abs(playerY + player.h/2 - (ballY + ball.h/2)) / H;
			return false;
		}
	}
	if (ballY + ball.h > H)
	{
		ballVelY *= -1;
		ballY = H - ball.h;
	}
	else if (ballY < 0)
	{
		ballVelY *= -1;
		ballY = 0;
	}

	/*
	if (playerY + player.h / 2 > ballY + ball.h / 2 && vel < 0)
		net.fitness++;
	else if (playerY + player.h / 2 < ballY + ball.h / 2 && vel > 0)
		net.fitness++;
	else
		net.fitness--;
	*/
	
	ball.x = ballX;
	ball.y = ballY;
	
	if (steps > 25) return false;//so the game cannot go infinitely
	return true;
}

void Game::run(Net &net, bool drawing, int amount)
{
	auto const temp = speed;
	if (drawing)
		speed = 5;
	float sum = 0;
	for (auto i = 0; i < amount; i++) {
		net.fitness = 0;
		reset();
		while (step(net))
		{
			if (drawing)
			{
				draw(net);
			}
		}
		sum += net.fitness / amount;
	}
	net.fitness = sum;
	if (drawing)
		speed = temp;
}

std::thread Game::thread(Net& net, int amount)
{
	return std::thread(&Game::run, this, std::ref(net), false, std::ref(amount));
}

void Game::draw(Net net)
{
	SDL_Rect dstrect = { W / 4, 0, W / 2, H / 3 };
	net.drawNet(*sdl, dstrect);
	
	SDL_RenderDrawRect(sdl->renderer, &player);
	SDL_RenderDrawRect(sdl->renderer, &ball);
	
	sdl->draw();
}