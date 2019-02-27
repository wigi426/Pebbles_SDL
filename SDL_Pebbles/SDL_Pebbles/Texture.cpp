#include "Includes.h"

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
		
		m_texture = SDL_CreateTextureFromSurface(globals.renderer, tempSurface);
	}

	return successFlag;                                                                
}





void Texture::render(psuedoGlobals &globals, SDL_Rect* destRect)
{
	SDL_RenderCopy(globals.renderer, m_texture, NULL, destRect);
}


