#pragma once
class GridSquare
{
public:
	GridSquare();
	~GridSquare();
	
	//initalizes the squares vector with x by y elements
	static void intiSquaresVector(int x, int y);

	static void gridClicked(int mouseX, int mouseY);

	static void setStartPebbles(const std::vector<int> &startIndexes);

	static void renderGrid(std::vector<SDLVisualObject> &textures);

	

private:
	static std::vector<std::vector<GridSquare>> sm_squares;

	enum renderState
	{
		OCCUPIED,
		SELECTED,
		POTENTIAL,
		EMPTY,
		TOTAL,
	};

	enum axis
	{
		X,
		Y,
	};

	struct Coordinates
	{
		int x;
		int y;
	};

	struct Selection
	{
		axis flatAxis;
		std::vector<Coordinates> selectedIndex;
	};

	

	Selection m_selection;
	renderState m_state{ EMPTY }; //represents how the state that will be passed on to the user
	int m_i_potentialFor{}; //index to element in squares index

	void select(int thisX, int thisY);
	void deselect();
	void moveTo();
};

