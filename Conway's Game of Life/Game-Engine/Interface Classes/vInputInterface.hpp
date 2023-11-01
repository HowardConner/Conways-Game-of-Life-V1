/*****************************************************************************
**************
* Programmer: Conner Howard
* File: Virtual Input handler
* Date: 10/16/2023
* Description: Virtual Class allowing for direct input handling (free from
*	the SFML event stack)
******************************************************************************
*************/
#ifndef VIRTUAL_INPUT_INTERFACE_HPP
#define VIRTUAL_INPUT_INTERFACE_HPP

class InputInterface
{
public:
	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //
	InputInterface() {};

	virtual ~InputInterface() {};

	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //




	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* mFunction Name: Virtual Input Handler
	* Description: Event Handler to for dynamic keyboard/mouse/controller input. Used for 
	*	rapid and direct input handling
	* Inputs: accepts none
	* Outputs: returns true if an event was handled, false otherwise
	*/
	virtual bool handleInput() = 0;


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