#include "MasterHeader.h"



void printError(int line, std::string file);

bool initSDL(psuedoGlobals &globals);

bool loadMediaSDL(psuedoGlobals & globals);

void closeSDL(psuedoGlobals & globals);

void select(psuedoGlobals &globals,unsigned int x,unsigned int y);

void deselect(psuedoGlobals &globals,unsigned int x,unsigned int y);

void move(psuedoGlobals &globals, unsigned int x, unsigned int y);

void sortCoors(psuedoGlobals &globals);//sorts the coors vector in ascencing order of variable axis

void setPotentials(psuedoGlobals & globals);

int main(int argc, char *argv[])
{
	psuedoGlobals globals;

	initSDL(globals);
	loadMediaSDL(globals);

	SDL_Event event;
	bool quit{ false };

	//background coour white
	SDL_SetRenderDrawColor(globals.renderer, 255, 255, 255, 255);

	//initalize coordinate vector and isSelected array
	for (int x{}; x < 5; ++x)
	{
		for (int y{}; y < 5; ++y)
		{
			globals.gridSquares[x][y].destRender.x = (x * 200) + 50;
			globals.gridSquares[x][y].destRender.y = (y * 200) + 50;
			globals.gridSquares[x][y].coors.x = x * 200;
			globals.gridSquares[x][y].coors.y = y * 200;

			globals.selected.isSelected[x][y] = false;//ensure all squares are deselected;
		}
	}

	globals.selected.coors.resize(0);
	globals.gridSquares[2][2].state = renderState::OCCUPIED;
	globals.gridSquares[2][3].state = renderState::OCCUPIED;
	globals.gridSquares[3][2].state = renderState::OCCUPIED;
	globals.gridSquares[0][1].state = renderState::OCCUPIED;
	globals.gridSquares[2][1].state = renderState::OCCUPIED;
	globals.gridSquares[3][3].state = renderState::OCCUPIED;

	
	

	while (!quit)
	{
		while (SDL_PollEvent(&event) != NULL)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				switch (globals.gridSquares[event.button.x/200][event.button.y/200].state)
				{
				case renderState::OCCUPIED:
					select(globals, event.button.x / 200, event.button.y / 200);
					if (globals.selected.coors.size() > 1)
					{
						sortCoors(globals);//sort globals.selected.coors;
					}
					break;
				case renderState::SELECTED:
					deselect(globals, event.button.x / 200, event.button.y / 200);
					break;
				case renderState::POTENTIAL:
					move(globals, event.button.x / 200, event.button.y / 200);
					break;
				case renderState::EMPTY:
					break;
				}
			}
		}

		globals.selected.clearDown = true;
		globals.selected.clearLeft = true;
		globals.selected.clearRight = true;
		globals.selected.clearUp = true;
		globals.selected.clearBack = true;
		globals.selected.clearFront = true;

		//clear last cycle potentials:
		for (int x{}; x < 5; ++x)
		{
			for (int y{}; y < 5; ++y)
			{
				if (globals.gridSquares[x][y].state == renderState::POTENTIAL)
				{
					globals.gridSquares[x][y].state = renderState::EMPTY;
				}
			}
		}

	
		setPotentials(globals);


		SDL_RenderClear(globals.renderer);

		//render game grid
		globals.textures.at(Texture::TEXTURE_GAMEGRID).render(globals, NULL);

		//render squares appropriate to state
		for (int x{}; x < 5; ++x)
		{
			for (int y{}; y < 5; ++y)
			{
				switch (globals.gridSquares[x][y].state)
				{
				case renderState::OCCUPIED:
					globals.textures.at(Texture::TEXTURE_PEBBLE).render(globals, &globals.gridSquares[x][y].destRender);
					break;
				case renderState::SELECTED:
					globals.textures.at(Texture::TEXTURE_PEBBLE_SELECT).render(globals, &globals.gridSquares[x][y].destRender);
					break;
				case renderState::POTENTIAL:
					globals.textures.at(Texture::TEXTURE_PEBBLE_POTENTIAL).render(globals, &globals.gridSquares[x][y].destRender);
					break;
				case renderState::EMPTY:
					break;
				}
			}
		}


		
		
		SDL_RenderPresent(globals.renderer);

	}



	closeSDL(globals);
	
	return 0;
}

void printError(int line, std::string file)
{
	std::cout << "Error occured at line: " << line << " ,in file : " << file <<
		"\nSDL Error: " << SDL_GetError() << '\n';
}

bool initSDL(psuedoGlobals &globals)
{
	bool successFlag{ true };

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printError(__LINE__, __FILE__);
		successFlag = false;
	}
	else
	{
		globals.window = SDL_CreateWindow("SDL_Pebbles_Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, globals.windowWidth, globals.windowHeight, NULL);
		if (globals.window == NULL)
		{
			printError(__LINE__, __FILE__);
			successFlag = false;
		}
		else
		{
			globals.renderer = SDL_CreateRenderer(globals.window, -1, SDL_RENDERER_ACCELERATED);
			if (globals.renderer == NULL)
			{
				printError(__LINE__, __FILE__);
				successFlag = false;
			}
			else
			{
				int imgFlags = IMG_INIT_JPG || IMG_INIT_PNG;
				if ((IMG_Init(imgFlags) & imgFlags) != imgFlags)
				{
					printError(__LINE__, __FILE__);
					successFlag = false;
				}

				if (TTF_Init() < 0)
				{
					printError(__LINE__, __FILE__);
					successFlag = false;
				}
			}
		}
	}
	return successFlag;
}

bool loadMediaSDL(psuedoGlobals &globals)
{
	bool successFlag{ true };

	globals.textures.resize(Texture::TOTAL_TEXTURES);

	globals.textures.at(Texture::TEXTURE_GAMEGRID).loadFromFile(globals, "images/gameGrid.png");
	globals.textures.at(Texture::TEXTURE_GAMEGRID).setDefaultDest(0, 0, 1000, 1000);

	globals.textures.at(Texture::TEXTURE_PEBBLE).loadFromFile(globals, "images/pebble.png");

	globals.textures.at(Texture::TEXTURE_SQUARE).loadFromFile(globals, "images/square.png");

	globals.textures.at(Texture::TEXTURE_PENTAGON).loadFromFile(globals, "images/pentagon.png");

	globals.textures.at(Texture::TEXTURE_TRIANGLE).loadFromFile(globals, "images/triangle.png");

	globals.textures.at(Texture::TEXTURE_PEBBLE_MASTER).loadFromFile(globals, "images/pebbleMaster.png");

	globals.textures.at(Texture::TEXTURE_PEBBLE_SELECT).loadFromFile(globals, "images/pebbleSelect.png");

	globals.textures.at(Texture::TEXTURE_PEBBLE_POTENTIAL).loadFromFile(globals, "images/pebblePotential.png");

	return successFlag;
}

void closeSDL(psuedoGlobals &globals)
{
	SDL_DestroyRenderer(globals.renderer);
	globals.renderer = NULL;

	SDL_DestroyWindow(globals.window);
	globals.window = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

}

void select(psuedoGlobals & globals, unsigned int x, unsigned int y)
{
	if (globals.selected.selectedCount == 0) // if this there are no other selections
	{
		globals.gridSquares[x][y].state = renderState::SELECTED;
		globals.selected.isSelected[x][y] = true;
		globals.selected.selectedCount += 1;
		globals.selected.coors.push_back(coordinates{ x, y });
	}
	else//if this is the 2nd/3rd/4th/5th selection
	{
		bool isInline{ false };
		if (globals.selected.selectedCount == 1)
		{
			if (globals.selected.coors[0].x == x)
			{
				isInline = true;
				globals.selected.flatAxis = axis::X;
			}
			else if (globals.selected.coors[0].y == y)
			{
				isInline = true;
				globals.selected.flatAxis = axis::Y;
			}
		}
		else
		{
			if (globals.selected.coors[0].x == x && globals.selected.flatAxis == axis::X)
			{
				isInline = true;
			}
			else if (globals.selected.coors[0].y == y && globals.selected.flatAxis == axis::Y)
			{
				isInline = true;
			}
		}

		if (isInline)
		{
			globals.gridSquares[x][y].state = renderState::SELECTED;
			globals.selected.coors.push_back(coordinates{ x, y });
			globals.selected.isSelected[x][y] = true;
			globals.selected.selectedCount += 1;
		}
	}
}

void deselect(psuedoGlobals & globals,unsigned int x,unsigned int y)
{

	if (globals.selected.selectedCount > 1)
	{
		for (int i{}; i < globals.selected.coors.size(); ++i)
		{
			if (globals.selected.coors.at(i).x == x && globals.selected.coors.at(i).y == y)
			{
				//put deselected value at back
				coordinates swapTemp{};
				swapTemp = globals.selected.coors.at(i);
				globals.selected.coors.at(i) = globals.selected.coors.back();
				globals.selected.coors.back() = swapTemp;

				//now pop of the last element
				globals.selected.coors.pop_back();
			}

		}
	}
	else
		globals.selected.coors.pop_back();

	globals.selected.isSelected[x][y] = false;
	globals.selected.selectedCount -= 1;

	globals.gridSquares[x][y].state = renderState::OCCUPIED;


}

void move(psuedoGlobals & globals,unsigned int x,unsigned int y)
{
	if (globals.gridSquares[x][y].potenitalFor.x - 1 == x)//if left of potentialFor (moving left)
	{
		for (int i{}; i < globals.selected.coors.size(); ++i)
		{
			globals.gridSquares[globals.selected.coors.at(i).x - 1][globals.selected.coors.at(i).y].state = renderState::OCCUPIED; //occupy new position
			globals.gridSquares[globals.selected.coors.at(i).x][globals.selected.coors.at(i).y].state = renderState::EMPTY; //clear old position
		}
	}
	else if (globals.gridSquares[x][y].potenitalFor.x + 1 == x)//if right of potentialFor (moving right)
	{
		for (int i{}; i < globals.selected.coors.size(); ++i)
		{
			globals.gridSquares[globals.selected.coors.at(i).x + 1][globals.selected.coors.at(i).y].state = renderState::OCCUPIED; //occupy new position
			globals.gridSquares[globals.selected.coors.at(i).x][globals.selected.coors.at(i).y].state = renderState::EMPTY; //clear old position
		}
	}
	else if (globals.gridSquares[x][y].potenitalFor.y - 1 == y)//if abvoe pootential for (moving up)
	{
		for (int i{}; i < globals.selected.coors.size(); ++i)
		{
			globals.gridSquares[globals.selected.coors.at(i).x][globals.selected.coors.at(i).y - 1].state = renderState::OCCUPIED; //occupy new position
			globals.gridSquares[globals.selected.coors.at(i).x][globals.selected.coors.at(i).y].state = renderState::EMPTY; //clear old position
		}
	}
	else if (globals.gridSquares[x][y].potenitalFor.y + 1 == y)//if below potential for (moving down)
	{
		for (int i{}; i < globals.selected.coors.size(); ++i)
		{
			globals.gridSquares[globals.selected.coors.at(i).x][globals.selected.coors.at(i).y + 1].state = renderState::OCCUPIED; //occupy new position
			globals.gridSquares[globals.selected.coors.at(i).x][globals.selected.coors.at(i).y].state = renderState::EMPTY; //clear old position
		}
	}

	globals.selected.coors.clear();
	globals.selected.selectedCount = 0;
	for (int x{}; x < 5; ++x)
	{
		for (int y{}; y < 5; ++y)
		{
			globals.selected.isSelected[x][y] = false;
		}
	}

}

void sortCoors(psuedoGlobals & globals)
{
	if (globals.selected.flatAxis == axis::X)//in ascending y coors
	{
		for (int i{}; i < globals.selected.coors.size(); ++i)
		{
			for (int j{}; j < globals.selected.coors.size()-1; ++j)
			{
				if (globals.selected.coors.at(j).y > globals.selected.coors.at(j + 1).y)
				{
					std::swap(globals.selected.coors.at(j), globals.selected.coors.at(j + 1));
				}
			}
		}
	}
	else //in ascending x coors
	{
		for (int i{}; i < globals.selected.coors.size(); ++i)
		{
			for (int j{}; j < globals.selected.coors.size()-1; ++j)
			{
				if (globals.selected.coors.at(j).x > globals.selected.coors.at(j + 1).x)
				{
					std::swap(globals.selected.coors.at(j), globals.selected.coors.at(j + 1));
				}
			}
		}
	}
}

void setPotentials(psuedoGlobals &globals)
{
	//work out where paths are clear

	if (globals.selected.coors.size() == 0)
		return;

	//clear directions for individual pebbles
	for (int i{}; i < globals.selected.coors.size(); ++i)
	{
		if (globals.selected.coors.at(i).x + 1 > 5 || globals.gridSquares[globals.selected.coors.at(i).x + 1][globals.selected.coors.at(i).y].state != renderState::EMPTY)//right
		{
			globals.selected.clearRight = false;
		}
		if (globals.selected.coors.at(i).x - 1 > 5 || globals.gridSquares[globals.selected.coors.at(i).x - 1][globals.selected.coors.at(i).y].state != renderState::EMPTY)//left
		{
			globals.selected.clearLeft = false;
		}
		if (globals.selected.coors.at(i).y + 1 > 5 || globals.gridSquares[globals.selected.coors.at(i).x][globals.selected.coors.at(i).y + 1].state != renderState::EMPTY)//down
		{
			globals.selected.clearDown = false;
		}
		if (globals.selected.coors.at(i).y - 1 > 5 || globals.gridSquares[globals.selected.coors.at(i).x][globals.selected.coors.at(i).y - 1].state != renderState::EMPTY)//up
		{
			globals.selected.clearUp = false;
		}
	}

	if (globals.selected.coors.size() > 1)//multiple selects
	{
		if (globals.selected.flatAxis == axis::X) // vertical line
		{
			if (globals.selected.coors.front().y - 1 <= 5 && globals.gridSquares[globals.selected.coors.front().x][globals.selected.coors.front().y - 1].state == renderState::EMPTY)// up
			{
				globals.gridSquares[globals.selected.coors.front().x][globals.selected.coors.front().y - 1].state = renderState::POTENTIAL;
				globals.gridSquares[globals.selected.coors.front().x][globals.selected.coors.front().y - 1].potenitalFor = coordinates
				{ globals.selected.coors.front().x, globals.selected.coors.front().y };
			}
			if (globals.selected.coors.front().y + 1 <= 5 && globals.gridSquares[globals.selected.coors.back().x][globals.selected.coors.back().y + 1].state == renderState::EMPTY)// down
			{
				globals.gridSquares[globals.selected.coors.back().x][globals.selected.coors.back().y + 1].state = renderState::POTENTIAL;
				globals.gridSquares[globals.selected.coors.front().x][globals.selected.coors.front().y + 1].potenitalFor = coordinates
				{ globals.selected.coors.front().x, globals.selected.coors.front().y };
			}
		}
		else //horizontal line
		{
			if (globals.selected.coors.front().x - 1 <= 5 && globals.gridSquares[globals.selected.coors.front().x - 1][globals.selected.coors.front().y].state == renderState::EMPTY)// left
			{
				globals.gridSquares[globals.selected.coors.front().x - 1][globals.selected.coors.front().y].state = renderState::POTENTIAL;
				globals.gridSquares[globals.selected.coors.front().x - 1][globals.selected.coors.front().y].potenitalFor = coordinates
				{ globals.selected.coors.front().x, globals.selected.coors.front().y };
			}
			if (globals.selected.coors.front().x + 1 <= 5 && globals.gridSquares[globals.selected.coors.back().x + 1][globals.selected.coors.back().y].state == renderState::EMPTY) // right
			{
				globals.gridSquares[globals.selected.coors.back().x + 1][globals.selected.coors.back().y].state = renderState::POTENTIAL;
				globals.gridSquares[globals.selected.coors.back().x + 1][globals.selected.coors.back().y].potenitalFor = coordinates
				{ globals.selected.coors.back().x, globals.selected.coors.back().y };
			}
		}
	}


	//change render state according the to clearPath bools
	for (unsigned int x{}; x < 5; ++x)
	{
		for (unsigned int y{}; y < 5; ++y)
		{
			if (globals.selected.isSelected[x][y] == true)
			{
				if (globals.selected.clearRight == true && x + 1 <= 5)
				{
					globals.gridSquares[x + 1][y].state = renderState::POTENTIAL;
					globals.gridSquares[x + 1][y].potenitalFor = coordinates{ x, y };
				}
				if (globals.selected.clearLeft == true && x - 1 <= 5)
				{
					globals.gridSquares[x - 1][y].state = renderState::POTENTIAL;
					globals.gridSquares[x - 1][y].potenitalFor = coordinates{ x, y };
				}
				if (globals.selected.clearDown == true && y + 1 <= 5)
				{
					globals.gridSquares[x][y + 1].state = renderState::POTENTIAL;
					globals.gridSquares[x][y + 1].potenitalFor = coordinates{ x, y };
				}
				if (globals.selected.clearUp == true && y - 1 <= 5)
				{
					globals.gridSquares[x][y - 1].state = renderState::POTENTIAL;
					globals.gridSquares[x][y - 1].potenitalFor = coordinates{ x, y };
				}
			}
		}
	}
}
