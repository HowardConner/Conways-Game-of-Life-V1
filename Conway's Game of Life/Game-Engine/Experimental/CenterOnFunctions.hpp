/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/

#include <iostream>
#include "SFML/Graphics.hpp"

namespace funct
{
	struct ViewInfo
	{
		sf::Vector2f center;
		sf::Vector2f size;
	};
	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* Function Name: Center View On
	* Description: Accepts a screen resoluition, frame to center on, percent offset of shape (where 1.0 = 100%) and
	*	returns the new size and center of the viewframe. Uses screen resolution to fit the supplied shape into
	*	the viewport while maintaining aspect ratio.
	* Inputs: Accepts a screen resoluition, frame to center on, percent offset of shape (where 1.0 = 100%)
	* Preconditions: resolution of the viewport being modified must be known
	* Outputs:
	* Returns: ViewInfo of a new viewframe
	* Postconditions:
	*/
	ViewInfo centerViewOn(const sf::Vector2f& Resolution, const sf::FloatRect& frameToCenterOn, const float percentShapeOffset = 1.0);


	// --------------------------------------------------------------------------------------------- //
	//								  PRIVATE   Member Functions
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
}