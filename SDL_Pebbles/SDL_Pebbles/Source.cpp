#include "Includes.h"

bool initSDL(psuedoGlobals &globals);

bool loadMediaSDL(psuedoGlobals &globals);

void closeSDL(psuedoGlobals &globals);

void printError(int line, std::string file);


int main(int argc, char *argv[])
{
	psuedoGlobals globals;

	if (initSDL(globals) && loadMediaSDL(globals))
	{
		bool quit{ false };
		bool play{ false };
		SDL_Event event;
		SDL_Rect gameBoardViewport{ 0, 0, 1000, 1000 };
		SDL_Rect configCardViewport{ 0, 1000, 1000, 250 };

		SDL_Rect config1Dest{ 0, 0, 250, 250 };

		globals.pebbles.resize(10);

		while (!quit)
		{
			while (SDL_PollEvent(&event) != NULL)
			{
				if (event.type == SDL_QUIT)
				{
					quit = true;
				}

			}
			

			SDL_RenderClear(globals.renderer);
			SDL_RenderSetViewport(globals.renderer, &gameBoardViewport);

			//render game board
			globals.textures.at(Texture::TEXTURE_GAMEBOARD).render(globals, NULL);

			//render a pebble
			globals.pebbles.at(0).render(globals);

			SDL_RenderSetViewport(globals.renderer, &configCardViewport);

			//render config card:
			
			globals.textures.at(Texture::TEXTURE_CONFIG1).render(globals, &config1Dest);

			SDL_RenderPresent(globals.renderer);

		}

		closeSDL(globals);

	}
	else
	{
		std::cout << "program has exited due to SDL initialization issues\n";
	}

	return 0;
}


void printError(int line, std::string file)
{
	std::cout << "error at line: " << line << " in file: " << file << '\n'
		<< "SDL_GetError = " << SDL_GetError() << '\n';
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

	globals.textures.at(Texture::TEXTURE_CONFIG1).loadFromFile(globals, "images/config1.png");

	globals.textures.at(Texture::TEXTURE_GAMEBOARD).loadFromFile(globals, "images/gameBoard.png");

	globals.textures.at(Texture::TEXTUER_PEBBLE).loadFromFile(globals, "images/pebble.png");

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

