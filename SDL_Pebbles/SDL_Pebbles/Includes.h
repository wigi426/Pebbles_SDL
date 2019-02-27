#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Texture.h"
#include "Pebble.h"

struct psuedoGlobals
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	int windowHeight{1250};
	int windowWidth{1000};
	std::vector<Texture> textures;
	std::vector<Pebble> pebbles;
};














