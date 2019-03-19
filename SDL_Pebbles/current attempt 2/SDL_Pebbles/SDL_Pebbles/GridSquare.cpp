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
		sm_squares.at(gridX).at(gridY).select(gridX, gridY);
		break;
	case POTENTIAL:
		//sm_squares.at(gridX).at(gridY).moveTo();
		break;
	case EMPTY:
		break;
	}
	clearPotentials();
	assignPotentials();

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
	//instead, allow the user to select the master then select another if that other is in line and has connections between it
	//and the master, then auto select all pebbles inbetween, if the user attempts to select again the selections will be cleared
	//and the new selection will be the master
	if (sm_selection.selectedIndex.size() > 0)
	{
		if (sm_selection.selectedIndex.size() == 1)
		{
			if (sm_selection.selectedIndex.at(0).x == thisX && sm_selection.selectedIndex.at(0).y == thisY)
			{
				sm_selection.selectedIndex.pop_back();
				m_state = OCCUPIED;
				return;
			}
			//select second selection if it is inline and has other pebbles bridging the connection
			//also select the bridging pebbles
			if (sm_selection.selectedIndex.at(0).x == thisX)
			{
				sm_selection.flatAxis = X;
				int ySeperation{ std::abs(sm_selection.selectedIndex.at(0).y - thisY ) + 1}; //represents the number of y coordinates involved 2 means they are next to each other
				bool bridge{ true };// true if the master and second selection have bridging pebbles
				if (thisY < sm_selection.selectedIndex.at(0).y)
				{
					for (int i{ 0 }; i < ySeperation - 1; ++i)
					{
						if (sm_squares.at(thisX).at(thisY + i).m_state != OCCUPIED)
							bridge = false;
					}
					if (bridge == true)
					{
						for (int i{ 0 }; i < ySeperation - 1; ++i)
						{
							sm_squares.at(thisX).at(thisY + i).m_state = SELECTED;
							sm_selection.selectedIndex.push_back(Coordinates{ thisX, thisY + i });
						}
					}
				}
				else
				{
					for (int i{ 1 }; i < ySeperation; ++i)
					{
						if (sm_squares.at(thisX).at(sm_selection.selectedIndex.at(0).y + i).m_state != OCCUPIED)
							bridge = false;
					}
					if (bridge == true)
					{
						for (int i{ 1 }; i < ySeperation; ++i)
						{
							sm_squares.at(thisX).at(sm_selection.selectedIndex.at(0).y + i).m_state = SELECTED;
							sm_selection.selectedIndex.push_back(Coordinates{ thisX, sm_selection.selectedIndex.at(0).y + i });
						}
					}
				}
			}
			else if (sm_selection.selectedIndex.at(0).y == thisY)
			{
				sm_selection.flatAxis = Y;
				int xSeperation{ std::abs(sm_selection.selectedIndex.at(0).x - thisX) + 1}; //represents the number of x coordinates involved 2 means they are next to each other
				bool bridge{ true };// true if the master and second selection have bridging pebbles
				if (thisX < sm_selection.selectedIndex.at(0).x)
				{
					for (int i{ 0 }; i < xSeperation - 1; ++i)
					{
						if (sm_squares.at(thisX + i).at(thisY).m_state != OCCUPIED)
							bridge = false;
					}
					if (bridge == true)
					{
						for (int i{ 0 }; i < xSeperation - 1; ++i)
						{
							sm_squares.at(thisX + i).at(thisY).m_state = SELECTED;
							sm_selection.selectedIndex.push_back(Coordinates{ thisX + i, thisY});
						}
					}
				}
				else
				{
					for (int i{ 1 }; i < xSeperation; ++i)
					{
						if (sm_squares.at(sm_selection.selectedIndex.at(0).x + i).at(thisY).m_state != OCCUPIED)
							bridge = false;
					}
					if (bridge == true)
					{
						for (int i{ 1 }; i < xSeperation; ++i)
						{
							sm_squares.at(sm_selection.selectedIndex.at(0).x + i).at(thisY).m_state = SELECTED;
							sm_selection.selectedIndex.push_back(Coordinates{ sm_selection.selectedIndex.at(0).x + i , thisY });
						}
					}
				}
			}
			//nothing will happen if they dont share at one axis value
		}
		else
		{
			//clear salections set new clicked as master select
			for (const auto &element : sm_selection.selectedIndex)
			{
				sm_squares.at(element.x).at(element.y).m_state = OCCUPIED;
			}
			sm_selection.selectedIndex.clear();
			m_state = SELECTED;
			sm_selection.selectedIndex.push_back(Coordinates{ thisX, thisY });
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


void GridSquare::assignPotentials()
{
	if (sm_selection.selectedIndex.size() == 1)// only one selectoin
	{
		Coordinates select{ sm_selection.selectedIndex.at(0) };
		if (select.y - 1 >= 0 ? sm_squares.at(select.x).at(select.y - 1).m_state == EMPTY : false) // above
		{
			sm_squares.at(select.x).at(select.y - 1).m_state = POTENTIAL;
			sm_squares.at(select.x).at(select.y - 1).m_i_potentialFor = select;
		}
		if (select.y + 1 < 5 ? sm_squares.at(select.x).at(select.y + 1).m_state == EMPTY : false) // below
		{
			sm_squares.at(select.x).at(select.y + 1).m_state = POTENTIAL;
			sm_squares.at(select.x).at(select.y + 1).m_i_potentialFor = select;
		}
		if (select.x - 1 >= 0 ? sm_squares.at(select.x - 1).at(select.y).m_state == EMPTY : false) // left
		{
			sm_squares.at(select.x - 1).at(select.y).m_state = POTENTIAL;
			sm_squares.at(select.x - 1).at(select.y).m_i_potentialFor = select;
		}
		if (select.x + 1 < 5 ? sm_squares.at(select.x + 1).at(select.y).m_state == EMPTY : false) // right
		{
			sm_squares.at(select.x + 1).at(select.y).m_state = POTENTIAL;
			sm_squares.at(select.x + 1).at(select.y).m_i_potentialFor = select;
		}
	}
	else if (sm_selection.selectedIndex.size() > 1)
	{
		const std::vector<Coordinates> &index{ sm_selection.selectedIndex }; // reference to make code visually simpler
		if (sm_selection.flatAxis == X) //vertical line
		{
			if (index.front().y - 1 >= 0 ? sm_squares.at(index.front().x).at(index.front().y - 1).m_state == EMPTY : false)//above
			{
				sm_squares.at(index.front().x).at(index.front().y - 1).m_state = POTENTIAL;
				sm_squares.at(index.front().x).at(index.front().y - 1).m_i_potentialFor = index.front();
			}
			if (index.back().y + 1 < 5 ? sm_squares.at(index.back().x).at(index.back().y + 1).m_state == EMPTY : false) //below
			{
				sm_squares.at(index.back().x).at(index.back().y + 1).m_state = POTENTIAL;
				sm_squares.at(index.back().x).at(index.back().y + 1).m_i_potentialFor = index.back();
			}

			bool clear{ true };
			for (const auto &element : index)// left clear?
			{
				
				if (element.x - 1 >= 0 ? sm_squares.at(element.x - 1).at(element.y).m_state != EMPTY : true)
					clear = false;
			}
			if (clear) // set left
			{
				for (const auto &element : index)
				{
					sm_squares.at(element.x - 1).at(element.y).m_state = POTENTIAL;
					sm_squares.at(element.x - 1).at(element.y).m_i_potentialFor = element;
				}
			}
			
			clear = true;
			for (const auto &element : index)// right clear?
			{

				if (element.x + 1 < 5 ? sm_squares.at(element.x + 1).at(element.y).m_state != EMPTY : true)
					clear = false;
			}
			if (clear) // set right
			{
				for (const auto &element : index)
				{
					sm_squares.at(element.x + 1).at(element.y).m_state = POTENTIAL;
					sm_squares.at(element.x + 1).at(element.y).m_i_potentialFor = element;
				}
			}

		}
		else //horizontal line
		{
			if (index.front().x - 1 >= 0 ? sm_squares.at(index.front().x - 1).at(index.front().y).m_state == EMPTY : false)//left
			{
				sm_squares.at(index.front().x - 1).at(index.front().y).m_state = POTENTIAL;
				sm_squares.at(index.front().x - 1).at(index.front().y).m_i_potentialFor = index.front();
			}
			if (index.back().x + 1 < 5 ? sm_squares.at(index.back().x + 1).at(index.back().y).m_state == EMPTY : false) //right
			{
				sm_squares.at(index.back().x + 1).at(index.back().y ).m_state = POTENTIAL;
				sm_squares.at(index.back().x + 1).at(index.back().y).m_i_potentialFor = index.back();
			}

			bool clear{ true };
			for (const auto &element : index)// above clear?
			{

				if (element.y - 1 >= 0 ? sm_squares.at(element.x).at(element.y - 1).m_state != EMPTY : true)
					clear = false;
			}
			if (clear) // set above
			{
				for (const auto &element : index)
				{
					sm_squares.at(element.x).at(element.y - 1).m_state = POTENTIAL;
					sm_squares.at(element.x).at(element.y - 1).m_i_potentialFor = element;
				}
			}

			clear = true;
			for (const auto &element : index)// below clear?
			{

				if (element.y + 1 < 5 ? sm_squares.at(element.x).at(element.y + 1).m_state != EMPTY : true)
					clear = false;
			}
			if (clear) // set below
			{
				for (const auto &element : index)
				{
					sm_squares.at(element.x).at(element.y + 1).m_state = POTENTIAL;
					sm_squares.at(element.x).at(element.y + 1).m_i_potentialFor = element;
				}
			}
		}
	}
}

void GridSquare::clearPotentials()
{
	for (int x{ 0 }; x < sm_squares.size(); ++x)
	{
		for (int y{ 0 }; y < sm_squares.front().size(); ++y)
		{
			if (sm_squares.at(x).at(y).m_state == POTENTIAL)
				sm_squares.at(x).at(y).m_state = EMPTY;
		}
	}
}