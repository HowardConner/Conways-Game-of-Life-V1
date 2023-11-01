/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description: Dedicated Camera Controller for Conway's Game of Life
******************************************************************************
*************/
#ifndef CAMERA_CONTROLLER_HPP
#define CAMERA_CONTROLLER_HPP

#include "Game-Engine/Interface Classes/vCameraInterface.hpp"
//#include "Game-Engine/Interface Classes/vEventInterface.hpp"
//#include "Game-Engine/Interface Classes/vInputInterface.hpp"
#include "Game-Engine/Interface Classes/vDragInterface.hpp"

//struct cameraKeyBindings {
//	sf::Keyboard::Key moveUp = sf::Keyboard::W;
//	sf::Keyboard::Key moveDown = sf::Keyboard::S;
//	sf::Keyboard::Key moveLeft = sf::Keyboard::A;
//	sf::Keyboard::Key moveRight = sf::Keyboard::D;
//
//	sf::Keyboard::Key zoomIn = sf::Keyboard::PageUp;
//	sf::Keyboard::Key zoomOut = sf::Keyboard::PageDown;
//};

class CameraController : public CameraInterface, public DragInterface//, public InputInterface, public EventInterface
{
public:
	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //
	// constructor
	CameraController(sf::RenderWindow& displayWindow, const float& velocityPercentOfScreenPerStep = 0.025);

	// destructor
	~CameraController();


	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //
	// setters


	// getters
	// Returns the location and size (in camView-relative pixels) as floatRect
	sf::FloatRect getCamRectangle() const;
	// check dragging active event
	//  returns true if active, false otherwise
	inline bool isDraggingActive() const;

	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //
	///* mFunction Name:
	//* Description: Accepts an event to process. Expected responses:
	//*	- movement
	//*	- zoom
	//* Inputs: Constant Reference to event to handle
	//* Outputs: returns true if an event was handled, false otherwise
	//*/
	//bool handleEvent(const sf::Event& eventToHandle);

	///* mFunction Name: Virtual Input Handler
	//* Description: Event Handler to for dynamic keyboard/mouse/controller input. Used for
	//*	rapid and direct input handling
	//* Inputs: accepts none
	//* Outputs: returns true if an event was handled, false otherwise
	//*/
	//bool handleInput();

	/* mFunction Name: Set Camera Max Bounds
	* Description: Sets the rectangle that the bounds that the camera can move in
	* Inputs: FloatRect of the area to move, percentOffset from that area
	* Outputs: none
	*/
	void setCameraBounds(const sf::FloatRect& area, const float& perecentOffset = 0.0);

	/* mFunction Name: Restrict (or Unrestrict) Camera bounds
	* Description: Either sets or unsets the flag for restricting camera movement outside of 
	*	the bounds of the Bound locking area. Auto snaps the camera back to a valid view location
	* Inputs: state to set to, true for restrict, false to unlock
	* Outputs: returns true if change made, false otherwise
	*/
	bool restrictCameraBounds(const bool& toState = true);

	/* mFunction Name: Handler Drag Event
	* Description: Handles drag event by comparing previously cursor coord to the current one and
	*	adding delta to the camera or parent object
	* Inputs: Current Mouse Move Event, open window
	* Outputs: none
	*/
	void handleDragEvent();

private:
	//cameraKeyBindings mBindings;	// key bindings for the camera class
	bool mEnforceCamBounds;			// flag before enforcing area
	sf::FloatRect mCamBounds;		// boundary area for locking movement

	/* ------------ from CameraInterface ------------ */
	//		sf::Vector2f		mResolution;
	//		sf::Vector2f		mOffset;
	//		sf::Vector2f		mVelocity;
	//		float				mVelocityScreenPercent;
	//		bool				mNeedUpdate = true;
	//		sf::View			mCamView;
	/* ------------ ------------------ ------------ */
	// --------------------------------------------------------------------------------------------- //
	//								  PRIVATE   Member Functions
	// --------------------------------------------------------------------------------------------- //


	/* mFunction Name: Enforce Bounds
	* Description: Enforces bound shift area by making sure (if possible) to shift and centers the 
	*	shape if possible
	* Inputs: none
	* Outputs: returns true if change made, false if not
	*/
	bool enforceBounds();


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