#include "MasterHeader.h"

int main(int argc, char *argv[])
{
	
	SDLVisualObject::initSDL();

	SDLVisualObject marbles( SDL_Rect{ 0, 0, 900, 900 }, "images/marbles.bmp");


	std::vector<std::vector<int>> twoDvector;

	twoDvector.resize(5);

	for (int x{}; x < 5; ++x)
	{	
		twoDvector.at(x).resize(5);
		for (int y{}; y < 5; ++y)
		{
			twoDvector.at(x).at(y) = x * y;
			std::cout << "[" << x << "][" << y << "] = " << twoDvector.at(x).at(y);
		}
		std::cout << "\n";
	}

	std::cout << twoDvector.size();


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

			}
		}


		SDLVisualObject::renderClearSDL();

		marbles.copyRender();

		SDLVisualObject::renderPresentSDL();

	}

	SDLVisualObject::closeSDL();

	return 0;
}