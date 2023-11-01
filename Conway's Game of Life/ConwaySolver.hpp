/*****************************************************************************
**************
* Programmer: Conner Howard
* File: 
* Date: 
* Description: 
******************************************************************************
*************/
#ifndef CONWAY_GAME_OF_LIFE_HPP
#define CONWAY_GAME_OF_LIFE_HPP

#include "BoolBoard.hpp"
#include "ConwaySettings.hpp"

namespace CGOL	// stands for "Conway Game of Life
{
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
	void solveConwayStep(BoolBoard& board, const ConwaySettings& settings);



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
	void solveNeighborhood(const size_t& whereX, const size_t& whereY, BoolBoard& board, const ConwaySettings& settings);

	/* Function Name: Calcualte Neighbors
	* Description: Calcuates the number of neighbors in the neighborhood and returns the result
	* Inputs: locaiton of cell to check, board to compare, reference to settings
	* Preconditions:
	* Outputs: number of neighbors as unsigned int
	* Returns: number of neighbors as unsigned int
	* Postconditions:
	*/
	unsigned calculateNeighbors(const size_t& whereX, const size_t& whereY, const BoolBoard& board, const ConwaySettings& settings);



	/* Function Name:
	* Description:
	* Inputs:
	* Preconditions:
	* Outputs:
	* Returns:
	* Postconditions:
	*/
}
#endif