/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#ifndef RENDER_OBJECT_HPP
#define RENDER_OBJECT_HPP

#include "../Component Classes/Object_Attributes.hpp"
#include "../Interface Classes/vDrawableInterface.hpp"
#include "SFML/Graphics.hpp"
#include "RenderEngine.hpp"

//forward declairation of all classes with permission to edit the renderID
class RenderEngine;

// --------------------------------------------------------------------------------------------- //
//											Data Structure
// --------------------------------------------------------------------------------------------- //

// --------------------------------------------------------------------------------------------- //
//									Data Structure Base Class
// --------------------------------------------------------------------------------------------- //
class RenderObject : public DrawableInterface
{
public:
	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //
	// constructor
	RenderObject()
	{

	}

	// copy constructor
	RenderObject(const RenderObject& copy)
	{
		this->renderID = copy.renderID;
		this->drawObjectFlag = copy.drawObjectFlag;
	}

	// copy assignment operator

	// destructor
	~RenderObject()
	{
		// nothing to destroy
	}

	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //
	// setters


	// getters
	// public check of render ID
	Att::render_ID getRenderID() const
	{
		return this->renderID;
	}
	// Get RenderBounds
	//	require all RenderObjects to output a floatRect that describes the render boundary
	virtual sf::FloatRect getRenderBounds() const = 0;

	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //

	/* mFunction Name: Draw Render Object
	* Description: Virtual Render object function
	* Inputs: outputWindow to draw to
	* Precondition: call isInBounds() and have true
	* Outputs:
	*/
	//virtual void draw(sf::RenderWindow& outputWindow) = 0;
	//  NOT NEEDED, CAPTURED BY "DrawableInterface" interface
	//	ADDED CONDITION FOR DRAW CALL: only render if drawObjectFlag == true

	/* mFunction Name: Check is Texture in Bounds
	* Description: Virtual Render culling check. Allows each RenderObject to
	*	decide how to check if it should be rendered. Suggestions are checking if
	*	the points of the cameraBounds intersect with the stored texture. Return true
	*	if the bounds overlap with the texture at all
	* Inputs: bounds of window as floatRectangle
	* Outputs: true if RenderObject is in window bounds, false otherwise
	*/
	virtual bool isInBounds(const sf::FloatRect& cameraBounds) = 0;

	// Classes Exclusivly permitted to modify private members (ie, renderID)
	// allows access to functions like set_ID
	friend class RenderEngine;
private:
	// render ID value
	// set to "NULL" until captured by a render engine
	mutable Att::render_ID renderID = Att::NULL_RENDER_ID;
	// allowed to draw
	bool drawObjectFlag = true;
	// --------------------------------------------------------------------------------------------- //
	//								  PRIVATE   Member Functions
	// --------------------------------------------------------------------------------------------- //
	// set ID
	// Restricted access (currently only to friend class RenderEngine
	//	returns: whatever the render_ID was set to
	Att::render_ID setRender_ID(const Att::render_ID& newRenderID)
	{
		return this->renderID = newRenderID;
	}


};

/* mFunction Name:
* Description:
* Inputs:
* Outputs:
*/

/* mFunction Name:
* Description:
* Inputs:
* Outputs:
*/

#endif