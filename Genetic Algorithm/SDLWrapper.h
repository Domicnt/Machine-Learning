#pragma once
#include "stdafx.h"

class SDLWrapper
{
public:
	bool quit;
	
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event e;

	SDL_Texture* texture;

	const Uint8* keyboardArray;//holds keyboard presses
	bool leftClick, rightClick;//if the mouse was clicked
	bool m1, m2;//if the mouse is held down
	int mX, mY;//mouse pos

	SDLWrapper();

	void update();
	bool testKey(std::string const& key);//tests if a key is pressed
	
	void renderSurface(SDL_Surface* surface, const SDL_Rect dstrect);
	void draw();
};