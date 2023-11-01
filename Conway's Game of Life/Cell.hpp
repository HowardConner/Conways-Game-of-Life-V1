/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#ifndef CELL_HPP
#define CELL_HPP

enum LifeState {
	DEAD = 0,
	ALIVE
};

struct Cell
{
public:
	LifeState activeState		= LifeState::DEAD;
	LifeState nextState = LifeState::DEAD;
	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //

	// copy assignment operator
	Cell& operator=(const Cell& rhs)
	{
		this->activeState = rhs.activeState;
		this->nextState = rhs.nextState;

		return *this;
	}


	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //




	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //
	// equallity comparison operator
	bool operator==(const Cell& rhs)
	{
		return this->activeState == rhs.activeState && this->nextState == rhs.nextState;
	}


private:

	// --------------------------------------------------------------------------------------------- //
	//								  PRIVATE   Member Functions
	// --------------------------------------------------------------------------------------------- //



};

// --------------------------------------------------------------------------------------------- //
//									non - Member Functions
// --------------------------------------------------------------------------------------------- //


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

#endif