#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include "SDLVisualObject.h"
#include "GridSquare.h"
#include "selection.h"

enum Textures
{
	TEXTURE_OCCUPIED,
	TEXTURE_SELECTED,
	TEXTURE_POTENTIAL,
	TEXTURE_TOTAL,
};

enum Rotation
{
	COUNTER_CLOCKWISE,
	CLOCKWISE,
};