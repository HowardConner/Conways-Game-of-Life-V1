/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/

#include "CenterOnFunctions.hpp"

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
funct::ViewInfo funct::centerViewOn(const sf::Vector2f & Resolution, const sf::FloatRect & frameToCenterOn,
	const float percentShapeOffset)
{
	// define variables
	ViewInfo newViewInfo = { {0.0, 0.0}, {0.0, 0.0} };
	float offsetWidth = frameToCenterOn.width * (1 + 2 * percentShapeOffset),
		offsetHeight = frameToCenterOn.height * (1 + 2 * percentShapeOffset);

	float ratioX = offsetWidth / Resolution.x,
		ratioY = offsetHeight / Resolution.y;

	// set a default value for the frame center (easy part)
	newViewInfo.center = { frameToCenterOn.left + 0.5 * frameToCenterOn.width,
		frameToCenterOn.top + 0.5 * frameToCenterOn.height };
	// Frame size unknown, finish below calcs for correct size
	//newViewInfo.size = { 0, 0 };

	// check if ratios are equal, if so, even scaling
	if (ratioX == ratioY)
	{
		// evenly scale by boarder
		// keep as is
	}
	else if (ratioX > ratioY)
	{
		// the X dim has greater change, thus the Y dim is dependent on X:
		offsetHeight = offsetWidth * (Resolution.y / Resolution.x);
	}
	else if (ratioX < ratioY)
	{
		// the Y dim has greater precidence, thus X dim is dependent on current Y
		offsetWidth = offsetHeight * (Resolution.x / Resolution.y);
	}
	// update the temp viewport
	newViewInfo.size.x = offsetWidth;
	newViewInfo.size.y = offsetHeight;

	std::cout << "adjusted offsets (" << offsetWidth << ", " << offsetHeight << ")\n";
	std::cout << "new center:(" << newViewInfo.center.x << ", " << newViewInfo.center.y << ")   " << \
		newViewInfo.size.x << " x " << newViewInfo.size.y << std::endl << std::endl;

	// update new view info

	return newViewInfo;
}





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