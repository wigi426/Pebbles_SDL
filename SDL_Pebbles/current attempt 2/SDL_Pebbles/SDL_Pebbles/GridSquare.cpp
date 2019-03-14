#include "MasterHeader.h"

std::vector<std::vector<GridSquare>> GridSquare::sm_squares;
GridSquare::Selection GridSquare::sm_selection;

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

void GridSquare::printSelectionIndex()
{
	std::cout << "selection Index:\n";
	for (auto element : sm_selection.selectedIndex)
	{
		std::cout << "{ " << element.x << ", " << element.y << "}\n";
	}
}

void GridSquare::sortSelectionIndex()
{
	if (sm_selection.flatAxis == X)
	{
		for (int i{}; i < sm_selection.selectedIndex.size(); ++i)
		{
			for (int j{}; j < sm_selection.selectedIndex.size() - 1; ++j)
			{
				if (sm_selection.selectedIndex.at(j).y > sm_selection.selectedIndex.at(j+1).y)
				{
					std::swap(sm_selection.selectedIndex.at(j), sm_selection.selectedIndex.at(j+1));	
					
				}
			}
		}
	}
	else
	{
		for (int i{}; i < sm_selection.selectedIndex.size(); ++i)
		{
			for (int j{}; j < sm_selection.selectedIndex.size() - 1; ++j)
			{
				if (sm_selection.selectedIndex.at(j).x > sm_selection.selectedIndex.at(j+1).x)
				{
					std::swap(sm_selection.selectedIndex.at(j), sm_selection.selectedIndex.at(j+1));
				}
			}
		}
	}

}

void GridSquare::select( int thisX, int thisY)
{
	if (sm_selection.selectedIndex.size() > 0)
	{
		if (sm_selection.selectedIndex.size() < 2)
		{
			if (sm_selection.selectedIndex.at(0).x == thisX && 
					(sm_selection.selectedIndex.at(0).y +1 == thisY ||
					sm_selection.selectedIndex.at(0).y -1 == thisY) )
			{
				sm_selection.flatAxis = X;
				sm_selection.selectedIndex.push_back(Coordinates{ thisX, thisY });
				m_state = SELECTED;
			}
			else if( sm_selection.selectedIndex.at(0).y == thisY &&
					(sm_selection.selectedIndex.at(0).x +1 == thisX ||
					sm_selection.selectedIndex.at(0).x -1 == thisX) )
			{
				sm_selection.flatAxis = Y;
				sm_selection.selectedIndex.push_back(Coordinates{ thisX, thisY });
				m_state = SELECTED;
			}
		}
		else
		{
			if (sm_selection.flatAxis == X && thisX == sm_selection.selectedIndex.at(0).x &&
					(sm_selection.selectedIndex.front().y +1 == thisY ||
					sm_selection.selectedIndex.back().y -1 == thisY) )
			{
				sm_selection.selectedIndex.push_back(Coordinates{ thisX, thisY });
				m_state = SELECTED;
			}
			else if (sm_selection.flatAxis == Y && thisY == sm_selection.selectedIndex.at(0).y &&
					(sm_selection.selectedIndex.front().x +1 == thisX ||
					sm_selection.selectedIndex.back().x -1 == thisX) )
			{
				sm_selection.selectedIndex.push_back(Coordinates{ thisX, thisY });
				m_state = SELECTED;
			}
		}
		sortSelectionIndex();
	}
	else
	{
		m_state = SELECTED;
		sm_selection.selectedIndex.push_back(Coordinates{ thisX, thisY });
	}
	printSelectionIndex();
}

void GridSquare::deselect(int thisX, int thisY)
{
	if (sm_selection.selectedIndex.front().x == thisX && sm_selection.selectedIndex.front().y == thisY)
	{
		m_state = OCCUPIED;
		sm_selection.selectedIndex.erase(0);
	}
}

