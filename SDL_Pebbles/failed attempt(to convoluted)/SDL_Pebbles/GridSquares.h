#pragma once
//encapsulate single grid square
class GridSquares
{
public:
	GridSquares();
	~GridSquares();

	enum squareState
	{
		EMPTY,
		OCCUPIED,
		MASTER_SELECTED,
		SELECTED,
		POTENTIAL,
		TOTAL_STATES
	};

	void setState(squareState newState);

	//returns true if given coordiantes are within the square
	bool posMatch(int x, int y);

	//sets the position of the square
	void setPos(int x, int y);

	void setPotentialFor(int i);

	int getPotentialFor();

	//returns the current state of the square
	squareState getState();

	//renders according to state
	void render(psuedoGlobals &globals);

private:
	int m_topLeftPosX;
	int m_topLeftPosY;
	int m_pebbleRenderPosX;//render coordinates for difference pebble textrues
	int m_pebbleRenderPosY;
	int m_potentialFor;//represents which square this square is a potential for, if it is a potential
	squareState m_state = EMPTY;

	SDL_Rect getPebbleRenderPos();

};

