/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#ifndef VIRTUAL_DRAG_INTERFACE_HPP
#define VIRTUAL_DRAG_INTERFACE_HPP

#include "SFML/Graphics.hpp"


class DragInterface
{
public:
	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //
	// constructor
	DragInterface() {};

	// destructor
	virtual ~DragInterface() {};

	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //


	// check state of drag event
	// true if actively dragging, false otherwise
	virtual inline bool isDraggingActive() const
	{
		return this->mDragActive;
	}

	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* mFunction Name: Handler Drag Event
	* Description: Handles drag event by comparing previously cursor coord to the current one and
	*	adding delta to the camera or parent object
	* Inputs: None
	* Precondition: Call startDragEvent() before starting to loop function
	* Outputs: none
	*/
	virtual void handleDragEvent() = 0;

	/* mFunction Name: Start Drag Event
	* Description: Starts drag event by reseting the previous drag condition and sets
	*	is dragging flag to true
	* Inputs: None
	* Outputs: None
	*/
	virtual void startDragEvent(const sf::RenderWindow& openWindow);

	/* mFunction Name:
	* Description: Sets isDragging flag to false
	* Inputs: None
	* Outputs: None
	*/
	virtual void finishDragEvent();

protected:
	bool mDragActive = false;					// indicates whether the camera is in drag mode or not
	sf::Vector2i mDragPrevCursorPos = {0, 0};
	// --------------------------------------------------------------------------------------------- //
	//								  PRIVATE   Member Functions
	// --------------------------------------------------------------------------------------------- //



};

// --------------------------------------------------------------------------------------------- //
//									non - Member Functions
// --------------------------------------------------------------------------------------------- //
/* Function Name:
* Description:
* Inputs:
* Preconditions:
* Outputs:
* Returns:
* Postconditions:
*/


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