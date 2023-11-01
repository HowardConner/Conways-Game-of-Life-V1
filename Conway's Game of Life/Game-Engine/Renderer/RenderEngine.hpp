/*****************************************************************************
**************
* Programmer: Conner Howard
* File: Render Controller
* Date:
* Description: Put simply, responsible for dictating which visual items are
*	drawn on a screen at a given time. Uses dependency injections of the output
*	window to conduct this process
******************************************************************************
*************/
#ifndef RENDER_ENGINE_HPP
#define RENDER_ENGINE_HPP

#include <iostream>

#include "SFML/Graphics.hpp"
#include "../Component Classes/Object_Attributes.hpp"	// for Att::unique_ID
#include "../Renderer/RenderObject.hpp"	// for RenderObject virtual class
#include "../Interface Classes/vCameraInterface.hpp"	// for camera features

enum RenderGround{
	FORE = 0,
	MIDDLE,
	BACK
};

class RenderEngine
{
public:
	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //
	// default constructor
	// ViewArea is the rectangle which is visibly being output. Usually interacts with a CameraInterface
	RenderEngine()
	{

	}

	// destructor
	~RenderEngine()
	{
		// nothing to free
	}

	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //
	// setters


	// getters


	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* mFunction Name: RenderScene
	* Description: Renders the scene to the outputWindow. Uses the bounds of Camera Controller to handle
	*	updating the window to show what the camera designates, and then draws all RenderObjects that
	*	are within that bound to the window
	* Inputs: outputWindow (destination
	* Outputs:
	*/
	void render(const sf::RenderWindow& outputWindow, const CameraInterface* camView);

	/* mFunction Name: Add New Render Object
	* Description: Adds a new render object to Render pipeline in the propper layer.
	*	Returns true if inserted correctly, 
	* Inputs: Object to add, layer to add to
	* Outputs: true if added, false otherwise
	*/
	bool add(const RenderObject* newRenderObject, const RenderGround& whichLayer);

	/* mFunction Name: Remove Render Object from Render Pipeline
	* Description: Removes a Render object from the list if it is already in the list,
	*	returns true if removed, false otherwise (not found/not in list)
	*	NOTE: Removes from all layer lists if found in more than one
	* Inputs: pointer Object to be rendered
	* Outputs: true if removed, false otherwise
	*/
	bool remove(const RenderObject* removeRenderObject);

	/* mFunction Name: Update Textures
	* Description: Allows easy updating of all textures if applicable
	* Inputs:
	* Outputs:
	*/
	//void updateTexture(const TileLookup& reference);

private:
	// Unique ID for the next object to be added to the render pipeline
	Att::unique_ID mNextRenderID = 0;
	// current size and position of viewport relative to screen
	std::vector<RenderObject*> mMiddleGround;

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