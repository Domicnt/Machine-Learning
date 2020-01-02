#include "stdafx.h"

SDLWrapper::SDLWrapper()
{
	//initialize and set up sdl as well as sdl variables, such as renderer and event
	SDL_Init(SDL_INIT_EVENTS);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	window = SDL_CreateWindow("Program", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);// SDL_RENDERER_PRESENTVSYNC); // v-sync
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	quit = false;
}

void SDLWrapper::update()
{
	SDL_PumpEvents();//push up new events
	SDL_GetMouseState(&mX, &mY);//update the mouse pos
	leftClick = false;
	rightClick = false;
	while (SDL_PollEvent(&e) != 0) {//while there are events yet to be processed
		switch (e.type) {
		case SDL_QUIT://user quits the program
			quit = true;
			return;
		case SDL_MOUSEBUTTONDOWN:
			SDL_PumpEvents();
			switch (e.button.button) {
			case SDL_BUTTON_LEFT:
				leftClick = true;
				m1 = true;
				break;
			case SDL_BUTTON_RIGHT:
				rightClick = true;
				m2 = true;
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			SDL_PumpEvents();
			switch (e.button.button) {
			case SDL_BUTTON_LEFT:
				m1 = false;
				break;
			case SDL_BUTTON_RIGHT:
				m2 = false;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

bool SDLWrapper::testKey(std::string const& key)
{
	keyboardArray = SDL_GetKeyboardState(nullptr);
	if (key == " " && keyboardArray[SDL_SCANCODE_SPACE]) return true;
	if (key == "a" && keyboardArray[SDL_SCANCODE_A]) return true;
	if (key == "b" && keyboardArray[SDL_SCANCODE_B]) return true;
	if (key == "c" && keyboardArray[SDL_SCANCODE_C]) return true;
	if (key == "d" && keyboardArray[SDL_SCANCODE_D]) return true;
	if (key == "e" && keyboardArray[SDL_SCANCODE_E]) return true;
	if (key == "f" && keyboardArray[SDL_SCANCODE_F]) return true;
	if (key == "g" && keyboardArray[SDL_SCANCODE_G]) return true;
	if (key == "h" && keyboardArray[SDL_SCANCODE_H]) return true;
	if (key == "i" && keyboardArray[SDL_SCANCODE_I]) return true;
	if (key == "j" && keyboardArray[SDL_SCANCODE_J]) return true;
	if (key == "k" && keyboardArray[SDL_SCANCODE_K]) return true;
	if (key == "l" && keyboardArray[SDL_SCANCODE_L]) return true;
	if (key == "m" && keyboardArray[SDL_SCANCODE_M]) return true;
	if (key == "n" && keyboardArray[SDL_SCANCODE_N]) return true;
	if (key == "o" && keyboardArray[SDL_SCANCODE_O]) return true;
	if (key == "p" && keyboardArray[SDL_SCANCODE_P]) return true;
	if (key == "q" && keyboardArray[SDL_SCANCODE_Q]) return true;
	if (key == "r" && keyboardArray[SDL_SCANCODE_R]) return true;
	if (key == "s" && keyboardArray[SDL_SCANCODE_S]) return true;
	if (key == "t" && keyboardArray[SDL_SCANCODE_T]) return true;
	if (key == "u" && keyboardArray[SDL_SCANCODE_U]) return true;
	if (key == "v" && keyboardArray[SDL_SCANCODE_V]) return true;
	if (key == "w" && keyboardArray[SDL_SCANCODE_W]) return true;
	if (key == "x" && keyboardArray[SDL_SCANCODE_X]) return true;
	if (key == "y" && keyboardArray[SDL_SCANCODE_Y]) return true;
	if (key == "z" && keyboardArray[SDL_SCANCODE_Z]) return true;
	if (key == "0" && keyboardArray[SDL_SCANCODE_0]) return true;
	if (key == "1" && keyboardArray[SDL_SCANCODE_1]) return true;
	if (key == "2" && keyboardArray[SDL_SCANCODE_2]) return true;
	if (key == "3" && keyboardArray[SDL_SCANCODE_3]) return true;
	if (key == "4" && keyboardArray[SDL_SCANCODE_4]) return true;
	if (key == "5" && keyboardArray[SDL_SCANCODE_5]) return true;
	if (key == "6" && keyboardArray[SDL_SCANCODE_6]) return true;
	if (key == "7" && keyboardArray[SDL_SCANCODE_7]) return true;
	if (key == "8" && keyboardArray[SDL_SCANCODE_8]) return true;
	if (key == "9" && keyboardArray[SDL_SCANCODE_9]) return true;
	if (key == "," && keyboardArray[SDLK_COMMA]) return true;
	if (key == "." && keyboardArray[SDLK_PERIOD]) return true;
	if (key == "UP" && keyboardArray[SDL_SCANCODE_UP]) return true;
	if (key == "DOWN" && keyboardArray[SDL_SCANCODE_DOWN]) return true;
	if (key == "LEFT" && keyboardArray[SDL_SCANCODE_LEFT]) return true;
	if (key == "RIGHT" && keyboardArray[SDL_SCANCODE_RIGHT]) return true;
	return false;
}

void SDLWrapper::renderSurface(SDL_Surface* surface, const SDL_Rect dstrect)
{
	if (texture != nullptr) 
		SDL_DestroyTexture(texture);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, nullptr, &dstrect);
}

void SDLWrapper::draw()
{
	//render whatever was drawn to the renderer
	SDL_RenderPresent(renderer);
	//clear the renderer
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}