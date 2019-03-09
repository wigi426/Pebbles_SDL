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
	void render(psuedoGlobals &globals, SDL_Rect *destRect);

	void setDefaultDest(int x, int y, int h, int w);


	enum TextureNames
	{
		TEXTURE_GAMEGRID,
		TEXTURE_PEBBLE,
		TEXTURE_TRIANGLE,
		TEXTURE_SQUARE,
		TEXTURE_PENTAGON,
		TEXTURE_PEBBLE_MASTER,
		TEXTURE_PEBBLE_SELECT,
		TEXTURE_PEBBLE_POTENTIAL,
		TOTAL_TEXTURES,
	};

private:
	SDL_Rect m_defaultDest;
	SDL_Texture* m_texture;
};


