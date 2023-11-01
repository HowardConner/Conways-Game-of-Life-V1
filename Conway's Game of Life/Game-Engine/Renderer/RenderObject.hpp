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
class RenderObject
{
public:
	// getters
	// public check of render ID
	Att::unique_ID getRenderID() const
	{
		return this->renderID;
	}

	/* mFunction Name: Draw Render Object
	* Description: Virtual Render object function
	* Inputs: outputWindow to draw to
	* Precondition: call isInBounds() and have true
	* Outputs:
	*/
	virtual void draw(sf::RenderWindow& outputWindow) = 0;

	/* mFunction Name: Check is Texture in Bounds
	* Description: Virtual Render culling check. Allows each RenderObject to
	*	decide how to check if it should be rendered. Suggestions are checking if
	*	the points of the windowBounds intersect with the stored texture. Return true
	*	if the bounds overlap with the texture at all
	* Inputs: bounds of window as floatRectangle
	* Outputs: true if RenderObject is in window bounds, false otherwise
	*/
	virtual bool isInBounds(const sf::FloatRect& windowBounds) = 0;

	// Classes Exclusivly permitted to modify private members (ie, renderID)
	friend class RenderEngine;
private:
	// render ID value
	// set to "NULL" until captured by a render engine
	mutable Att::unique_ID renderID = 0;


	/* mFunction Name:
	* Description:
	* Inputs:
	* Outputs:
	*/
};

/* mFunction Name:
* Description:
* Inputs:
* Outputs:
*/

#endif