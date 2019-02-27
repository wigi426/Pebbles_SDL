#pragma once

struct psuedoGlobals;

/*
encapsulates SDL_Textures
*/
class Texture
{
public:
	Texture();
	~Texture();

	//"destroys" the previous texture
	//prevents memory leak when we point m_texture at a new texture
	void free();

	//loads an image from file and converts it to a texture which is
	//saved in m_texture
	bool loadFromFile(psuedoGlobals &globals, const std::string &path);

	//copy renders the texture
	void render(psuedoGlobals &globals, SDL_Rect* destRect);

	enum TextureNames
	{
		TEXTURE_CONFIG1,
		TEXTURE_GAMEBOARD,
		TEXTUER_PEBBLE,
		TOTAL_TEXTURES,
	};

private:

	SDL_Texture* m_texture;
};


