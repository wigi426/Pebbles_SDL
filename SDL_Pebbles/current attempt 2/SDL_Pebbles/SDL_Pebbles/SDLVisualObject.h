#pragma once
/*
	Wrapper for a visual object intented to be rendered by sdl
	intended interface:
	user give object size and position for render
	user gives image file origin if loading image
	user specifys the object type (texture, rectangle, point)
	user can tell the object to render to current target
*/
class SDLVisualObject
{
public:
	static SDL_Event event;

	SDLVisualObject();
	SDLVisualObject(SDL_Rect destRect, std::string file);// texture
	SDLVisualObject(SDL_Rect destRect);//rectangle

	~SDLVisualObject();

	static void setScreenDimensions(int h, int w);
	static void getScreenDimensions(int &h, int &w);


	static bool initSDL();

	static void closeSDL();

	static void renderClearSDL();

	static void renderPresentSDL();

	void copyRender(int newX = -1, int newY = -1);

	enum Type
	{
		TYPE_TEXTURE,
		TYPE_POINT,
		TYPE_RECT,
	};

private:
	Type m_type;
	SDL_Rect m_destRect;
	SDL_Texture* m_texture;

	static SDL_Window* m_window;
	static SDL_Renderer* m_renderer;
	static int SCREEN_HEIGHT;
	static int SCREEN_WIDTH;

	
};

