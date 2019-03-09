#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Texture.h"


enum class renderState
{
	OCCUPIED,
	SELECTED,
	POTENTIAL,
	EMPTY,
	TOTAL,
};

struct coordinates
{
	unsigned int x;
	unsigned int y;
};

enum class axis
{
	X,
	Y,
};

struct groupSelect
{
	axis flatAxis;
	std::vector<coordinates> coors;//the first value is always the master
	bool isSelected[5][5];
	int selectedCount{0};
	bool clearRight{ true };
	bool clearLeft{ true };
	bool clearDown{ true };
	bool clearUp{ true };
	bool clearBack{ true }; //clear at the back of the coors array to move down or right
	bool clearFront{ true }; //clear at the front of the coors arary to move up or left
};

struct squares
{
	coordinates coors;
	SDL_Rect destRender{ 0, 0, 100, 100 };//100 is the h and w of pebble textures
	renderState state{ renderState::EMPTY };
	coordinates potenitalFor;
};

struct psuedoGlobals
{
	const int windowHeight{ 1000 };
	const int windowWidth{ 1000 };
	SDL_Window *window;
	SDL_Renderer *renderer;
	std::vector<Texture> textures;
	squares gridSquares[5][5]; //coordinates of each grid squre of game grid
	groupSelect selected;
};



