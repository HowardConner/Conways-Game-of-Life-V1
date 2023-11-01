/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#include "vDragInterface.hpp"

// --------------------------------------------------------------------------------------------- //
//				Constructors, Default Constructors, Copy Constructors, Destructors
// --------------------------------------------------------------------------------------------- //




// --------------------------------------------------------------------------------------------- //
//									Setters and Getters
// --------------------------------------------------------------------------------------------- //




// --------------------------------------------------------------------------------------------- //
//								  PUBLIC   Member Functions
// --------------------------------------------------------------------------------------------- //
/* mFunction Name: Start Drag Event
* Description: Starts drag event by reseting the previous drag condition and sets
*	is dragging flag to true
* Inputs: Open Window used as reference
* Outputs: None
*/
void DragInterface::startDragEvent(const sf::RenderWindow& openWindow)
{
	this->mDragActive = true;
	this->mDragPrevCursorPos = sf::Mouse::getPosition(openWindow);
}

/* mFunction Name:
* Description: Sets isDragging flag to false
* Inputs: None
* Outputs: None
*/
void DragInterface::finishDragEvent()
{
	this->mDragActive = false;
}



// --------------------------------------------------------------------------------------------- //
//								  PRIVATE   Member Functions
// --------------------------------------------------------------------------------------------- //




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