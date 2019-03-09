#pragma once
class GridSquare
{
public:
	GridSquare();
	~GridSquare();
	
	//initalizes the squares vector with x by y elements
	void intiSquaresVector(int x, int y);


private:
	static std::vector<std::vector<GridSquare>> m_squares;

	enum renderState
	{
		OCCUPIED,
		SELECTED,
		POTENTIAL,
		EMPTY,
		TOTAL,
	};

	renderState state{ EMPTY };
};

