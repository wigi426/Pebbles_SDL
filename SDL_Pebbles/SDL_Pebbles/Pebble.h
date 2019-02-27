#pragma once

//This class encapsulates single pebbles
/*
	stores positional information
	renders the pebbles
	manages the movement
*/
class Pebble
{
public:
	enum Direction
	{
		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT,
	};

	Pebble();
	~Pebble();

	void render(psuedoGlobals &globals);

	void setPos(int x, int y);

private:
	SDL_Rect m_position;
};

