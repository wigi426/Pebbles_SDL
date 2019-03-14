#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <algorithm>
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