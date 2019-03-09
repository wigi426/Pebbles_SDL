#include "MasterHeader.h"

std::vector<std::vector<GridSquare>> GridSquare::m_squares;

GridSquare::GridSquare()
{
}


GridSquare::~GridSquare()
{
}

void GridSquare::intiSquaresVector(int x, int y)
{
	m_squares.resize(x);
	for (int i{}; i < x; ++i)
	{
		m_squares.at(i).resize(y);
	}
	for()
}




