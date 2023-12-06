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
#include <vector>
#include <array>

#include "SFML/Graphics.hpp"
//#include "../Component Classes/Object_Attributes.hpp"	// for Att::unique_ID, Att::render_ID
#include "../Renderer/RenderObject.hpp"					// for RenderObject virtual class
//#include "../Interface Classes/vCameraController.hpp"	// for camera features
#include "../../CameraController.hpp"
#include "../../HeadsUpDisplay.hpp"	// for HUD class

// forward declairations
class CameraController;
class HeadsUpDisplay;

enum RenderDepth{
	FORE = 0,
	MIDDLE,
	BACK,
	COUNT
};

struct RenderObjectLocation
{
	bool		hudElement;
	uint16_t	camIndex;
	uint32_t	objectIndex;
};

class RenderEngine
{
public:
	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //
	// default constructor
	RenderEngine()
	{

	}

	// destructor
	~RenderEngine()
	{
		// nothing to free
		// Render Engine not responsible for lifetime of object pointers
	}

	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //
	// setters
	// set active HUD 
	//	takes hud_ID and sets that to active if valid Hud option.
	//	Returns true if set to valid ID, false otherwise;
	bool setActiveHud(const Att::hud_ID& newActiveHud_ID);
	// set active Camera 
	//	takes camera_ID and sets that to active if valid Camera option.
	//	Returns true if set to valid ID, false otherwise;
	bool setActiveCamera(const Att::camera_ID& newActiveCam_ID);

	// getters
	Att::hud_ID getActiveHudID() const;
	Att::camera_ID getActiveCameraID() const;

	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* Function Name:
	* Description: Renders the scene with the active camera and then the active hud views.
	* Inputs: window to output render to
	* Preconditions: 
	* Outputs: none
	* Returns: none
	* Postconditions:
	*/
	void renderScene(sf::RenderWindow& outputWindow);

	/* Function Name: Bind new camera
	* Description: Adds a new camera to the internal list
	* Inputs: reference to camera to add
	* Preconditions:
	* Outputs: binds camera to RenderEngine and sets its camera_ID
	* Returns: camera_ID of the new camera
	* Postconditions:
	*/
	Att::camera_ID bindCamera(CameraController& newCamera);

	/* mFunction Name: Unbind Camera
	* Description: remove a camera view from the render list
	* Inputs: camera object to remove
	* Outputs: true if removed, false otherwise
	*/
	bool unbindCamera(CameraController& removeCamera);

	/* Function Name: bind Hud
	* Description: binds the HUD view to the renderer and sets a new hud_ID for it
	* Inputs: new HUD object to bind to the renderer
	* Preconditions:
	* Outputs: bind hud to renderer by setting hud_ID
	* Returns: new hud_id of the HUD object
	* Postconditions:
	*/
	Att::hud_ID bindHUD(HeadsUpDisplay& newHUD);

	/* mFunction Name: Unbind HUD
	* Description: remove a hud view from the render list
	* Inputs: hud object to remove
	* Outputs: true if removed, false otherwise
	*/
	bool unbindHud(HeadsUpDisplay& removeHUD);

	/* Function Name: Bind New Object (Camera Overload)
	* Description:
	* Inputs: Reference of the new RenderObject
	* Preconditions:
	* Outputs:
	* Returns: ID of new render object, or Att::NULL_CAMERA_ID if failed
	* Postconditions:
	*/
	Att::render_ID addCamObject(RenderObject& newObject);

	/* Function Name: Bind New Object (HUD Overload)
	* Description:
	* Inputs: Reference of the new RenderObject
	* Preconditions:
	* Outputs:
	* Returns: ID of new render object, or Att::NULL_HUD_ID if failed
	* Postconditions:
	*/
	Att::render_ID addHudObject(RenderObject& newObject);

	// comment please
	//bool removeCamObject(const RenderObject& objectToRemove);
	//bool removeHudObject(const RenderObject& objectToRemove);


	/* Function Name:
	* Description:
	* Inputs:
	* Preconditions:
	* Outputs:
	* Returns:
	* Postconditions:
	*/

private:
	// define world objects
	size_t mActiveCam = 0;
	std::vector<CameraController*> mCamsList;
	std::vector<RenderObject*> mCamObjects;
	// define HUD objects
	size_t mActiveHud = 0;
	std::vector<HeadsUpDisplay*> mHUDsList;
	std::vector<RenderObject*> mHudObjects;


	// --------------------------------------------------------------------------------------------- //
	//								  PRIVATE   Member Functions
	// --------------------------------------------------------------------------------------------- //
	// copy constructor is private
	RenderEngine(const RenderEngine& copy)
	{
		// nothing, dont allow copy
	}
	// copy assignment operator not allowed
	RenderEngine& operator=(const RenderEngine& rhs)
	{
		// nothing, dont allow for copy
	}


};

// --------------------------------------------------------------------------------------------- //
//									non - Member Functions
// --------------------------------------------------------------------------------------------- //
/* Function Name: Encode Render ID
* Description: Encodes the location information of a render object within the render engine into
*	a render_ID which contains all the information needed to decode the location
* Inputs: RenderObjectLocation data
* Preconditions:
* Outputs: render_ID as a unique key to access one render cell
* Returns: render_ID as a unique key to access one render cell
* Postconditions:
*/
Att::render_ID encodeRenderID(const RenderObjectLocation& objectLocal);

/* Function Name: Decode Render ID
* Description: Decodes the render_ID into its constituent parts
* Inputs: render_ID tag
* Preconditions:
* Outputs: RenderObjectLocation Data
* Returns: RenderObjectLocation Data
* Postconditions: must check that data is actually in the arrays. Function does
*	not guarantee existence, only converts
*/
RenderObjectLocation decodeRenderID(const Att::render_ID& objectID);


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