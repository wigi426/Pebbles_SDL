#include "MasterHeader.h"



SDL_Renderer* SDLVisualObject::m_renderer = NULL;
SDL_Window* SDLVisualObject::m_window = NULL;
int SDLVisualObject::SCREEN_HEIGHT = 1000;
int SDLVisualObject::SCREEN_WIDTH = 1000;
SDL_Event SDLVisualObject::event;



SDLVisualObject::SDLVisualObject()
{
}


SDLVisualObject::SDLVisualObject(SDL_Rect destRect, std::string file)
{
	m_destRect = destRect;
	m_type = TYPE_TEXTURE;
	SDL_Surface* tempSurface = IMG_Load(file.c_str());
	if (tempSurface == NULL)
	{
		std::cout << SDL_GetError();
	}
	else
	{
		m_texture = SDL_CreateTextureFromSurface(m_renderer, tempSurface);
		if (m_texture == NULL)
		{
			std::cout << SDL_GetError();
		}
	}
}

SDLVisualObject::SDLVisualObject(SDL_Rect destRect)
{
	m_destRect = destRect;
	m_type = TYPE_RECT;
}


SDLVisualObject::~SDLVisualObject()
{
	if(m_texture != NULL)
		SDL_DestroyTexture(m_texture);
}

void SDLVisualObject::setScreenDimensions(int h, int w)
{
	SCREEN_HEIGHT = h;
	SCREEN_WIDTH = w;
}

void SDLVisualObject::getScreenDimensions(int & h, int & w)
{
	h = SCREEN_HEIGHT;
	w = SCREEN_WIDTH;
}

bool SDLVisualObject::initSDL()
{
	bool successFlag{ true };
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << SDL_GetError() << std::endl;
		successFlag = false;
	}
	else
	{
		m_window = SDL_CreateWindow("SDL Chess Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		if (m_window == NULL)
		{
			std::cout << SDL_GetError() << std::endl;
			successFlag = false;
		}
		else
		{
			m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
			if (m_renderer == NULL)
			{
				std::cout << SDL_GetError() << std::endl;
				successFlag = false;
			}
			else
			{
				int imageFlags{ IMG_INIT_JPG | IMG_INIT_JPG };
				if ((IMG_Init(imageFlags) & imageFlags) != imageFlags)
				{
					std::cout << SDL_GetError() << std::endl;
					successFlag = false;
				}
			}
		}	
	}
	return successFlag;
}

void SDLVisualObject::closeSDL()
{
	SDL_DestroyWindow(m_window);
	m_window = NULL;
	SDL_DestroyRenderer(m_renderer);
	m_renderer = NULL;
	SDL_Quit();
}

void SDLVisualObject::renderClearSDL()
{
	SDL_RenderClear(m_renderer);
}

void SDLVisualObject::renderPresentSDL()
{
	SDL_RenderPresent(m_renderer);
}

void SDLVisualObject::copyRender(int newX, int newY)
{
	if (newX >= 0 && newY >= 0)
	{
		m_destRect.x = newX;
		m_destRect.y = newY;
	}
	switch (m_type)
	{
	case SDLVisualObject::TYPE_TEXTURE:
		if (m_destRect.h == NULL)
		{
			SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
		}
		else
			SDL_RenderCopy(m_renderer, m_texture, NULL, &m_destRect);
		break;
	case SDLVisualObject::TYPE_POINT:
		break;
	case SDLVisualObject::TYPE_RECT:
		break;
	default:
		break;
	}
}

