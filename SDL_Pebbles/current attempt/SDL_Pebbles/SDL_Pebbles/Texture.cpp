#include "MasterHeader.h"

extern void printError(int line, std::string file);

Texture::Texture()
{
	m_texture = NULL;
}

Texture::~Texture()
{
}


void Texture::free()
{
	SDL_DestroyTexture(m_texture);
	m_texture = NULL;
}

bool Texture::loadFromFile(psuedoGlobals &globals, const std::string &path)
{
	bool successFlag{ true };
	free();

	SDL_Surface* tempSurface;
	tempSurface = IMG_Load(path.c_str());
	if (tempSurface == NULL)
	{
		printError(__LINE__, __FILE__);
		successFlag = false;
	}
	else
	{
		SDL_SetColorKey(tempSurface, 1, SDL_MapRGB(tempSurface->format, 255, 255, 255));
		m_texture = SDL_CreateTextureFromSurface(globals.renderer, tempSurface);
	}

	return successFlag;                                                                
}


void Texture::render(psuedoGlobals &globals, SDL_Rect *destRect)
{
	if (destRect != NULL)
		SDL_RenderCopy(globals.renderer, m_texture, NULL, destRect);
	else
		SDL_RenderCopy(globals.renderer, m_texture, NULL, &m_defaultDest);
}



void Texture::setDefaultDest(int x, int y, int h, int w)
{
	m_defaultDest.x = x;
	m_defaultDest.y = y;
	m_defaultDest.h = h;
	m_defaultDest.w = w;
}


