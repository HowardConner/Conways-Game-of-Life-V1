/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#include "ConwaySolver.hpp"


// --------------------------------------------------------------------------------------------- //
//									PUBLIC Functions
// --------------------------------------------------------------------------------------------- //
/* Function Name: Conway solve one step
* Description: Solves conway board for one step, ie, loops through the board and updates it once
* Inputs: Board to solve, settings to apply to the board
* Preconditions:
* Outputs:
* Returns:
* Postconditions:
*/
void CGOL::solveConwayStep(BoolBoard& board, const ConwaySettings& settings)
{
	// update
	for (int y = 0; y < board.getSize().y; y++)
	{
		for (int x = 0; x < board.getSize().x; x++)
		{
			//std::cout << "processing step (" << x << ", " << y << ")\n";
			CGOL::solveNeighborhood(x, y, board, settings);
		}
	}

	board.updateCellState();
}



// --------------------------------------------------------------------------------------------- //
//									PRIVATE Functions
// --------------------------------------------------------------------------------------------- //
/* Function Name: Solve neightborhood
* Description: Solves the neighborhood of a specified cells
* Inputs: the location of the cell to check, the board to compare to, the settings to check to
* Preconditions:
* Outputs: updated cell "nextState" variables
* Returns: none
* Postconditions:
*/
void CGOL::solveNeighborhood(const size_t& whereX, const size_t& whereY, BoolBoard& board, const ConwaySettings& settings)
{
	// define variables
	size_t numberOfNeighbors = CGOL::calculateNeighbors(whereX, whereY, board, settings);

	// switch for dead cell
	if(board.isCellState(whereX, whereY, LifeState::DEAD))
	{
		switch (numberOfNeighbors) {
		case 0:
		case 1:
			board.setCellNextState(whereX, whereY, LifeState::DEAD);
			break;
		case 3:		// come alive if by mating
			board.setCellNextState(whereX, whereY, LifeState::ALIVE);
			break;
		};
	}

	// rules proces for living cell
	else if (board.isCellState(whereX, whereY, LifeState::ALIVE))
	{
		switch (numberOfNeighbors) {
		case 0:
		case 1:		// underpopulation, cell dies
			board.setCellNextState(whereX, whereY, LifeState::DEAD);
			break;
		case 2:
		case 3:		// no change, stable
			//std::cout << "cell is stable, no change" << std::endl;
			break;
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:		// death due to overpopulation
			board.setCellNextState(whereX, whereY, LifeState::DEAD);
			break;
		};
	}
}

/* Function Name: Calcualte Neighbors
* Description: Calcuates the number of neighbors in the neighborhood and returns the result
* Inputs: locaiton of cell to check, board to compare, reference to settings
* Preconditions:
* Outputs: number of neighbors as unsigned int
* Returns: number of neighbors as unsigned int
* Postconditions:
*/
unsigned CGOL::calculateNeighbors(const size_t& whereX, const size_t& whereY,
	const BoolBoard& board, const ConwaySettings& settings)
{
	// define varibles
	int x = 0;
	int y = 0;
	unsigned result = 0;

	// passes are the number of neighbors. Starting is 8
	for (int pass = 0; pass < 8; pass++)
	{
		// set activeState of x,y coordinate
		switch (pass) {
		case 0:		// top left
			x = whereX - 1;
			y = whereY - 1;
			break;
		case 1:		// top
			x = whereX;
			y = whereY - 1;
			break;
		case 2:		// top right
			x = whereX + 1;
			y = whereY - 1;
			break;
		case 3:		// left
			x = whereX - 1;
			y = whereY;
			break;
		case 4:		// right
			x = whereX + 1;
			y = whereY;
			break;
		case 5:		// bottom left
			x = whereX - 1;
			y = whereY + 1;
			break;
		case 6:		// bottom
			x = whereX;
			y = whereY + 1;
			break;
		case 7:		// bottom right
			x = whereX + 1;
			y = whereY + 1;
			break;
		};

		// check if in bounds and not dead
		if (board.indexInBoardRange(x, y) && board.getCellState(x, y) == LifeState::ALIVE)
		{
			// one neighbor was alive
			result++;
		}
	}


	return result;
}



/* mFunction Name:
* Description:
* Inputs:
* Outputs:
*/


/* Function Name:
* Description:
* Inputs:
* Preconditions:
* Outputs:
* Returns:
* Postconditions:
*/