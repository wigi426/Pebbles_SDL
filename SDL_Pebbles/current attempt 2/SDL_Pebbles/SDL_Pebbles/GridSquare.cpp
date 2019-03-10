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
		sm_squares.at(element % 5).at(element / 5).m_state = OCCUPIED;
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
				textures.at(TEXTURE_OCCUPIED).copyRender( (x*(screenW / 5)) + screenH/20, (y*(screenW / 5)) + screenW/20);
				break;
			case SELECTED:
				textures.at(TEXTURE_SELECTED).copyRender((x*(screenW / 5)) + screenH / 20, (y*(screenW / 5)) + screenW / 20);
				break;
			case POTENTIAL:
				textures.at(TEXTURE_POTENTIAL).copyRender((x*(screenW / 5)) + screenH / 20, (y*(screenW / 5)) + screenW / 20);
				break;
			case EMPTY:
				break;
			default:
				break;
			}
		}
	}
}

void GridSquare::gridClicked(int mouseX, int mouseY)
{
	int screenH{};
	int screenW{};
	SDLVisualObject::getScreenDimensions(screenH, screenW);
	int gridX{ mouseX / (screenW / 5) };
	int gridY{ mouseY / (screenH / 5) };
	switch (sm_squares.at(gridX).at(gridY).m_state)
	{
	case OCCUPIED:
		sm_squares.at(gridX).at(gridY).select(gridX, gridY);
		break;
	case SELECTED:
		//sm_squares.at(gridX).at(gridY).deselect();
		break;
	case POTENTIAL:
		//sm_squares.at(gridX).at(gridY).moveTo();
		break;
	case EMPTY:
		break;
	}
}

void GridSquare::select(int thisX, int thisY)
{
	if (m_selection.selectedIndex.size() > 0)
	{
		if (m_selection.selectedIndex.size() < 2)
		{
			if (m_selection.selectedIndex.at(0).x == thisX)
			{
				m_selection.flatAxis = X;
				m_selection.selectedIndex.push_back(Coordinates{ thisX, thisY });
				m_state = SELECTED;
			}
			else if( m_selection.selectedIndex.at(0).y == thisY)
			{
				m_selection.flatAxis = Y;
				m_selection.selectedIndex.push_back(Coordinates{ thisX, thisY });
				m_state = SELECTED;
			}
		}
		else
		{
			if (m_selection.flatAxis == X && thisX == m_selection.selectedIndex.at(0).x)
			{
				m_selection.selectedIndex.push_back(Coordinates{ thisX, thisY });
				m_state = SELECTED;
			}
			else if (m_selection.flatAxis == Y && thisY == m_selection.selectedIndex.at(0).y)
			{
				m_selection.selectedIndex.push_back(Coordinates{ thisX, thisY });
				m_state = SELECTED;
			}
		}
	}
	else
	{
		m_state = SELECTED;
		m_selection.selectedIndex.push_back(Coordinates{ thisX, thisY });
	}
}



