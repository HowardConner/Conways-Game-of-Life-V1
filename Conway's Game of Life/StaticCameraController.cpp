/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#include "StaticCameraController.hpp"


// --------------------------------------------------------------------------------------------- //
//				Constructors, Default Constructors, Copy Constructors, Destructors
// --------------------------------------------------------------------------------------------- //
// constructor
StaticCameraController::StaticCameraController(sf::RenderWindow& displayWindow) :
	CameraInterface(displayWindow),
	DragInterface()			//InputInterface(), EventInterface()
{

}

// destructor
StaticCameraController::~StaticCameraController()
{
	// destructors handled automatically
}



// --------------------------------------------------------------------------------------------- //
//									Setters and Getters
// --------------------------------------------------------------------------------------------- //
// Setters


// getters
// Returns the location and size (in camView-relative pixels) as floatRect
sf::FloatRect StaticCameraController::getCamRectangle() const
{
	return sf::FloatRect(this->mCamView.getCenter().x - 0.5 * mCamView.getSize().x,
		this->mCamView.getCenter().y - 0.5 * mCamView.getSize().y,
		mCamView.getSize().x,
		mCamView.getSize().y);
}

//  returns true if active, false otherwise
bool StaticCameraController::isDraggingActive() const
{
	return DragInterface::isDraggingActive();
}

// --------------------------------------------------------------------------------------------- //
//								  PUBLIC   Member Functions
// --------------------------------------------------------------------------------------------- //
/////* mFunction Name:
////* Description: Accepts an event to process. Expected responses:
////*	- movement
////*	- zoom
////* Inputs: Constant Reference to event to handle
////* Outputs: returns true if an event was handled, false otherwise
////*/
////bool StaticCameraController::handleEvent(const sf::Event& eventToHandle)
////{
////	// define variables
////	bool result = false;
////
////	// process mouse released
////	if (eventToHandle.type == sf::Event::MouseButtonReleased)
////	{
////		DragInterface::finishDragEvent();
////	}
////	// process mouse click
////	else if (eventToHandle.type == sf::Event::MouseButtonPressed)
////	{
////		DragInterface::startDragEvent(this->mBoundWindow);
////	}
////	// process mouse click
////	if (this->mDragActive == true && eventToHandle.type == sf::Event::MouseMoved)
////	{
////		// do a drag
////		handleDragEvent();
////	}
////
////	// process key press
////	else if (eventToHandle.type == sf::Event::KeyPressed)
////	{
////		result = true;
////		if (eventToHandle.Closed == true)
////		{
////
////		}
////		else
////		{
////			result = false;
////		}
////	}
////	// process key release
////	else if (eventToHandle.type == sf::Event::KeyReleased)
////	{
////		result = true;
////		if (eventToHandle.key.code == mBindings.zoomIn)
////		{
////			zoom(20);
////		}
////		else if (eventToHandle.key.code == mBindings.zoomOut)
////		{
////			zoom(-20);
////		}
////		else
////		{
////			result = false;
////		}
////	}
////	// process mouse wheel
////	else if (eventToHandle.type == sf::Event::MouseWheelScrolled)
////	{
////		// check zoom in
////		if (eventToHandle.mouseWheelScroll.delta > 0)
////		{
////			zoom(20);
////		}
////		else if (eventToHandle.mouseWheelScroll.delta < 0)
////		{
////			zoom(-20);
////		}
////
////	}
////
////
////	return result;
////}
//
///* mFunction Name: Virtual Input Handler
//* Description: Event Handler to for dynamic keyboard/mouse/controller input. Used for
//*	rapid and direct input handling
//* Inputs: accepts none
//* Outputs: returns true if an event was handled, false otherwise
//*/
//bool StaticCameraController::handleInput()
//{
//	// define variables
//	float moveAmount = 0.10;
//	bool result = false;
//
//	//if (sf::Keyboard::isKeyPressed(mBindings.moveUp))
//	//{
//	//	move(CamDirection::UP, moveAmount);
//	//	result = true;
//	//}
//	//if (sf::Keyboard::isKeyPressed(mBindings.moveDown))
//	//{
//	//	move(CamDirection::DOWN, moveAmount);
//	//	result = true;
//	//}
//	//if (sf::Keyboard::isKeyPressed(mBindings.moveLeft))
//	//{
//	//	move(CamDirection::LEFT, moveAmount);
//	//	result = true;
//	//}
//	//if (sf::Keyboard::isKeyPressed(mBindings.moveRight))
//	//{
//	//	move(CamDirection::RIGHT, moveAmount);
//	//	result = true;
//	//}
//
//
//
//	return result;
//}

/* mFunction Name: Set Camera Max Bounds
* Description: Sets the rectangle that the bounds that the camera can move in
* Inputs: FloatRect of the area to move, percentOffset from that area
* Outputs: none
*/
void StaticCameraController::setCameraBounds(const sf::FloatRect& area, const float& percentOffset)
{
	// make sure to incorperate percent offset
	this->mCamBounds = sf::FloatRect(area.left * (1 - percentOffset), area.top * (1 - percentOffset),
		area.width * (1 + percentOffset), area.height * (1 + percentOffset));
}

/* mFunction Name: Restrict (or Unrestrict) Camera bounds
* Description: Either sets or unsets the flag for restricting camera movement outside of
*	the bounds of the Bound locking area. Auto snaps the camera back to a valid view location
* Inputs: state to set to, true for restrict, false to unlock
* Outputs: returns true if change made, false otherwise
*/
bool StaticCameraController::restrictCameraBounds(const bool& toState)
{
	// if attempting to restrict, make sure its not already restricted
	if (toState == true && true != this->mEnforceCamBounds)
	{
		// set enforce flag to true, then force enforcement
		this->mEnforceCamBounds = true;

		return true;
	}
	// if attempting to unrestrict, make sure that currently unenforced
	else if (toState == false && false != this->mEnforceCamBounds)
	{
		// set the enforce flag to wrong
		this->mEnforceCamBounds = false;

		return true;
	}

	return false;
}

/* mFunction Name: Handler Drag Event
* Description: Handles drag event by comparing previously cursor coord to the current one and
*	adding delta to the camera or parent object
* Inputs: Current Mouse Move Event, open window
* Outputs: none
*/
void StaticCameraController::handleDragEvent()
{
	// define variables
	sf::Vector2i mousePos = sf::Mouse::getPosition(this->mBoundWindow);
	sf::Vector2i delta = this->mDragPrevCursorPos - mousePos;

	// move the camera
	move(delta);

	// update flag
	this->mNeedUpdate = true;

	// update previous camera
	this->mDragPrevCursorPos = mousePos;
}

// --------------------------------------------------------------------------------------------- //
//								  PRIVATE   Member Functions
// --------------------------------------------------------------------------------------------- //
/* mFunction Name: Enforce Bounds
* Description: Enforces bound shift area by making sure (if possible) to shift and centers the
*	shape if possible
* Inputs: none
* Outputs: returns true if change made, false if not
*/
bool StaticCameraController::enforceBounds()
{
	// define variables
	sf::Vector2f curCenter(getCamRectangle().left + 0.5 * getCamRectangle().width,
		getCamRectangle().top + 0.5 * getCamRectangle().height);
	sf::Vector2f bindingCenter(mCamBounds.left + 0.5 * mCamBounds.width,
		mCamBounds.top + 0.5 * mCamBounds.height);
	bool result = false;

	// avoid overchecking if the dimensions of the view frame are larger than the bounding box
	// check the X
	if (curCenter.x == bindingCenter.x)
	{
		// do nothing
	}
	else
	{

	}






	return result;
}



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