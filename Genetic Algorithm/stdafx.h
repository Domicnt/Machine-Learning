#pragma once

#include "SDL.h"
#undef main
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <vector>
#include <string>
#include <thread>

//width and height for window
const static auto W = 960, H = 540;

#include "SDLWrapper.h"
#include "net.h"
#include "exampleGame.h"
#include "population.h"