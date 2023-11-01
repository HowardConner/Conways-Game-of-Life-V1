/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#ifndef VIRUTAL_DRAWABLE_INTERFACE_HPP
#define VIRUTAL_DRAWABLE_INTERFACE_HPP

#include "SFML/Graphics.hpp"

class DrawableInterface
{
public:
	// constuctor
	DrawableInterface() {};
	// destructor
	virtual ~DrawableInterface() {};
	//---------------  VIRTUAL FUNCTIONS  ---------------//
	/* Function Name: Draw Visual
	* Description: Handles special-condition drawing of visual objects
	*	to a supplied window due to dependency injection
	* Inputs: output render window
	* Preconditions: render window must be open
	* Outputs: draws visual to the window
	* Returns: none
	* Postconditions:
	*/
	virtual void draw(sf::RenderWindow& window) const = 0;
};

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