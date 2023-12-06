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
// set active HUD 
//	takes hud_ID and sets that to active if valid Hud option.
//	Returns true if set to valid ID, false otherwise;
bool RenderEngine::setActiveHud(const Att::hud_ID& newActiveHud_ID)
{
	// define variables
	if (newActiveHud_ID > this->mHUDsList.size() && nullptr != this->mHUDsList.at(newActiveHud_ID))
	{
		// hud_ID is valid and doesnt refer to a nullified HUD View, proceed
		this->mActiveHud = newActiveHud_ID;
		return true;
	}
	return false;
}

// set active Camera 
//	takes camera_ID and sets that to active if valid Camera option.
//	Returns true if set to valid ID, false otherwise;
bool RenderEngine::setActiveCamera(const Att::camera_ID& newActiveCam_ID)
{
	if (newActiveCam_ID > this->mCamsList.size() && nullptr != this->mCamsList.at(newActiveCam_ID))
	{
		// camera_ID is valide and doesnt refer to a nullified cam view, proceed
		this->mActiveCam = newActiveCam_ID;
		return true;
	}
	return false;
}

// getters
Att::hud_ID RenderEngine::getActiveHudID() const
{
	return this->mActiveHud;
}

Att::camera_ID RenderEngine::getActiveCameraID() const
{
	return this->mActiveCam;
}

// -------------------------------------------------------------------------------------------- //
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
void RenderEngine::renderScene(sf::RenderWindow& outputWindow)
{
	// render active camera
	for (size_t objIndex = 0; objIndex < this->mCamObjects.size(); objIndex++)
	{
		if (this->mCamObjects.at(objIndex)->isInBounds(this->mCamsList.at(this->mActiveCam)->getCamRectangle()))
		{
			this->mCamObjects.at(objIndex)->draw(outputWindow);
		}
	}

	// render active HUD
	for (size_t objIndex = 0; objIndex < this->mHudObjects.size(); objIndex++)
	{
		if (this->mHudObjects.at(objIndex)->isInBounds(this->mHUDsList.at(this->mActiveHud)->getCamRectangle()))
		{
			this->mCamObjects.at(objIndex)->draw(outputWindow);
		}
	}
}

/* Function Name: Bind new camera
* Description: Adds a new camera to the internal list
* Inputs: reference to camera to add
* Preconditions:
* Outputs: binds camera to RenderEngine and sets its camera_ID
* Returns: camera_ID of the new camera
* Postconditions:
*/
Att::camera_ID RenderEngine::bindCamera(CameraController& newCamera)
{
	int insertAt = -1;
	Att::camera_ID result = 0;

	// check for uniqueness in cameras
	for (int index = 0; index < this->mCamsList.size(); index++)
	{
		if (mCamsList.at(index) != nullptr && mCamsList.at(index) == &newCamera)
		{
			std::cout << "Camera already bound. No binding set" << std::endl;
			return index;
		}
		else if (mCamsList.at(index) == nullptr && insertAt == -1)
		{
			// save the first empty index for insertion
			insertAt = index;
		}
	}

	// set the new cam
	if (insertAt == -1)
	{
		// push to end of list and return the value
		this->mCamsList.push_back(&newCamera);
		result = mCamsList.size();
	}
	else
	{
		// index was found before the end to insert
		this->mCamsList.at(insertAt) = &newCamera;
		result = insertAt;
	}
	
	newCamera.setID(*this, result);

	return result;
}

/* mFunction Name: Unbind Camera
* Description: remove a camera view from the render list
* Inputs: camera_ID to remove
* Outputs: true if removed, false otherwise
*/
bool RenderEngine::unbindCamera(CameraController& removeCamera)
{
	// check that removeCamera's ID inst already Null
	if (removeCamera.getID() == Att::NULL_CAMERA_ID)
	{
		return false;
	}
	// use ID to find object if it exists
	if (this->mCamsList.at(removeCamera.getID()) == &removeCamera)
	{
		// found it, now remove and update
		mCamsList.at(removeCamera.getID() - 1) = nullptr;
		removeCamera.setID(*this, Att::NULL_CAMERA_ID);   // setting to null
		return true;
	}
	return false;
}

/* Function Name: bind Hud
* Description: binds the HUD view to the renderer and sets a new hud_ID for it
* Inputs: new HUD object to bind to the renderer
* Preconditions:
* Outputs: bind hud to renderer by setting hud_ID
* Returns: new hud_id of the HUD object
* Postconditions:
*/
Att::hud_ID RenderEngine::bindHUD(HeadsUpDisplay& newHUD)
{
	int insertAt = -1;
	Att::hud_ID result = 0;

	// check for uniqueness in cameras
	for (int index = 0; index < this->mHUDsList.size(); index++)
	{
		if (mHUDsList.at(index) != nullptr && mHUDsList.at(index) == &newHUD)
		{
			std::cout << "HUD already bound. No binding set" << std::endl;
			return index;
		}
		else if (mHUDsList.at(index) == nullptr && insertAt == -1)
		{
			// save the first empty index for insertion
			insertAt = index;
		}
	}

	// set the new cam
	if (insertAt == -1)
	{
		// push to end of list and return the value
		this->mHUDsList.push_back(&newHUD);
		result = mHUDsList.size();
	}
	else
	{
		// index was found before the end to insert
		this->mHUDsList.at(insertAt) = &newHUD;
		result = insertAt;
	}

	newHUD.setID(*this, result);

	return result;
}

/* mFunction Name: Unbind HUD
* Description: remove a hud view from the render list
* Inputs: hud object to remove to remove
* Outputs: true if removed, false otherwise
*/
bool RenderEngine::unbindHud(HeadsUpDisplay& removeHUD)
{
	// check that removeCamera's ID inst already Null
	if (removeHUD.getID() == Att::NULL_HUD_ID)
	{
		return false;
	}
	// use ID to find object if it exists
	if (this->mHUDsList.at(removeHUD.getID()) == &removeHUD)
	{
		// found it, now remove and update
		mHUDsList.at(removeHUD.getID()) = nullptr;
		removeHUD.setID(*this, Att::NULL_HUD_ID);   // setting to null
		return true;
	}
	return false;
}

/* Function Name: Bind New Object (Camera Overload)
* Description:
* Inputs: Reference of the new RenderObject
* Preconditions:
* Outputs:
* Returns: ID of new render object, or Att::NULL_CAMERA_ID if failed
* Postconditions:
*/
Att::render_ID RenderEngine::addCamObject(RenderObject& newObject)
{
	// define variables
	int firstIndex = -1;
	Att::render_ID result = Att::NULL_CAMERA_ID;

	//// serach list for a blank space
	//for (int index = 0; index < this->mCamObjects.size(); index++)
	//{
	//	if (mCamObjects.at(index) == &newObject)
	//	{
	//		
	//	}
	//}
	this->mCamObjects.push_back(&newObject);
	result = mCamObjects.size();
	newObject.setRender_ID(result);

	return result;
}

/* Function Name: Bind New Object (HUD Overload)
* Description:
* Inputs: Reference of the new RenderObject
* Preconditions:
* Outputs:
* Returns: ID of new render object, or Att::NULL_HUD_ID if failed
* Postconditions:
*/
Att::render_ID RenderEngine::addHudObject(RenderObject& newObject)
{
	// define variables
	int firstIndex = -1;
	Att::render_ID result = Att::NULL_CAMERA_ID;

	//// serach list for a blank space
	//for (int index = 0; index < this->mCamObjects.size(); index++)
	//{
	//	if (mCamObjects.at(index) == &newObject)
	//	{
	//		
	//	}
	//}
	this->mHudObjects.push_back(&newObject);
	result = mHudObjects.size();
	newObject.setRender_ID(result);

	return result;
}





// --------------------------------------------------------------------------------------------- //
//								  PRIVATE   Member Functions
// --------------------------------------------------------------------------------------------- //






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
Att::render_ID encodeRenderID(const RenderObjectLocation& objectLocal)
{
	// Use bitwise OR and shift operations to pack the data
	Att::render_ID packedData = 0;

	// Pack hudElement (1 bit)
	packedData |= (static_cast<uint64_t>(objectLocal.hudElement) & 0x1) << 63;

	// Pack camIndex (8 bits)
	packedData |= (static_cast<uint64_t>(objectLocal.camIndex) & 0xFF) << 55;

	// Pack objectIndex (32 bits)
	packedData |= (static_cast<uint64_t>(objectLocal.objectIndex) & 0xFFFFFFFF);

	return packedData;
}

/* Function Name: Decode Render ID
* Description: Decodes the render_ID into its constituent parts
* Inputs: render_ID tag
* Preconditions:
* Outputs: RenderObjectLocation Data
* Returns: RenderObjectLocation Data
* Postconditions: must check that data is actually in the arrays. Function does
*	not guarantee existence, only converts
*/
RenderObjectLocation decodeRenderID(const Att::render_ID& objectID)
{
	return {
		static_cast<bool>((objectID >> 63) & 0x1),
		static_cast<uint8_t>((objectID >> 55) & 0xFF),
		static_cast<uint32_t>(objectID & 0xFFFFFFFF)
	};
}

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