#include "MasterHeader.h"

//this function should rotate the board, the two arguments tell the function which direction to 
//rotate and how many roations of 90 degrees to do
void rotateBoard(Rotation direction, int quarterSpinCount);

int main(int argc, char *argv[])
{
	SDLVisualObject::setScreenDimensions(500, 500);
	
	SDLVisualObject::initSDL();

	std::vector<SDLVisualObject> textures;
	textures.resize(TEXTURE_TOTAL);
	
	SDLVisualObject gameGrid(SDL_Rect{ NULL }, "images/gameGrid.png");
	SDLVisualObject pebbleOccupied(SDL_Rect{ 0, 0, 50, 50 }, "images/pebble.png");
	SDLVisualObject pebbleSelected(SDL_Rect{ 0, 0, 50, 50 }, "images/pebbleSelect.png");
	SDLVisualObject pebblePotential(SDL_Rect{ 0, 0, 50, 50 }, "images/pebblePotential.png");

	textures.at(TEXTURE_OCCUPIED) = pebbleOccupied;
	textures.at(TEXTURE_SELECTED) = pebbleSelected;
	textures.at(TEXTURE_POTENTIAL) = pebblePotential;


	GridSquare::intiSquaresVector(5, 5);

	//these numbers each represent a single grid square counting up from left to right
	//and then from top to bottom, 4 is the top right, 24 the bottom right, 12 the middle
	std::vector<int> startIndexes{ 0, 12, 1, 2, 5, 11, 23, 10 };

	GridSquare::setStartPebbles(startIndexes);


	bool quit{ false };
	while (!quit)
	{

		while (SDL_PollEvent(&SDLVisualObject::event) != NULL)
		{
			if (SDLVisualObject::event.type == SDL_QUIT)
			{
				quit = true;
			}
			if (SDLVisualObject::event.type == SDL_MOUSEBUTTONDOWN)
			{
				GridSquare::gridClicked(SDLVisualObject::event.button.x, SDLVisualObject::event.button.y);
			}
		}


		SDLVisualObject::renderClearSDL();

		gameGrid.copyRender(0, 0, GridSquare::boardAngle);
		GridSquare::renderGrid(textures);

		SDLVisualObject::renderPresentSDL();

	}

	SDLVisualObject::closeSDL();

	return 0;
}


