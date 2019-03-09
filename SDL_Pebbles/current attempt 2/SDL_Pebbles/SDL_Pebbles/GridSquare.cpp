#include "MasterHeader.h"

std::vector<std::vector<GridSquare>> GridSquare::sm_squares;

GridSquare::GridSquare()
{
}


GridSquare::~GridSquare()
{
}

void GridSquare::intiSquaresVector(int x, int y)
{
	sm_squares.resize(x);
	for (int i{}; i < x; ++i)
	{
		sm_squares.at(i).resize(y);
	}
}

void GridSquare::setStartPebbles(const std::vector<int>& startIndexes)
{
	for (const int &element : startIndexes)
	{
		sm_squares.at(4).at(2).m_state = OCCUPIED;
	}
}

void GridSquare::renderGrid(std::vector<SDLVisualObject> &textures) 
{
	int screenH{};
	int screenW{};
	SDLVisualObject::getScreenDimensions(screenH, screenW);
	for (int x{}; x < sm_squares.size(); ++x)
	{
		for (int y{}; y < sm_squares.at(0).size(); ++y)
		{
			switch (sm_squares.at(x).at(y).m_state)
			{
			case OCCUPIED:
				textures.at(TEXTURE_OCCUPIED).copyRender( (x*(screenH / 5)) + screenH/20, (y*(screenW / 5)) + screenW/20);
				break;
			case SELECTED:
				break;
			case POTENTIAL:
				break;
			case EMPTY:
				break;
			default:
				break;
			}
		}
	}
}




