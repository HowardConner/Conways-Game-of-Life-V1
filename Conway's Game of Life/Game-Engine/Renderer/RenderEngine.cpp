/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#include "RenderEngine.hpp"


// --------------------------------------------------------------------------------------------- //
//				Constructors, Default Constructors, Copy Constructors, Destructors
// --------------------------------------------------------------------------------------------- //




// --------------------------------------------------------------------------------------------- //
//									Setters and Getters
// --------------------------------------------------------------------------------------------- //
// setters


// getters


// -------------------------------------------------------------------------------------------- //
//								  PUBLIC   Member Functions
// --------------------------------------------------------------------------------------------- //
/* mFunction Name: RenderScene
* Description: Renders the scene to the outputWindow. Uses the bounds of Camera Controller to handle
*	updating the window to show what the camera designates, and then draws all RenderObjects that
*	are within that bound to the window
* Inputs: outputWindow (destination
* Outputs:
*/
void RenderEngine::render(const sf::RenderWindow& outputWindow, const CameraInterface* camView)
{
	for (int index = 0; index < this->mMiddleGround.size(); index++)
	{

	}
}

/* mFunction Name: Add New Render Object
* Description: Adds a new render object to Render pipeline in the propper layer.
*	Returns true if inserted correctly,
* Inputs: Object to add, layer to add to
* Outputs: true if added, false otherwise
*/
bool RenderEngine::add(const RenderObject* newRenderObject, const RenderGround& whichLayer)
{
	std::cout << "RenderEngine::add() undefined" << std::endl;
	return false;
}

/* mFunction Name: Remove Render Object from Render Pipeline
* Description: Removes a Render object from the list if it is already in the list,
*	returns true if removed, false otherwise (not found/not in list)
*	NOTE: Removes from all layer lists if found in more than one
* Inputs: pointer Object to be rendered
* Outputs: true if removed, false otherwise
*/
bool RenderEngine::remove(const RenderObject* removeRenderObject)
{
	std::cout << "RenderEngine::remove() undefined" << std::endl;
	return false;
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