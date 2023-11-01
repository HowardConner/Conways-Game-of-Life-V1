/*****************************************************************************
**************
* Programmer: Conner Howard
* Project:
* Date:
* Description: Collection of data attributes (component values) to be accessed
*	as needed
* See also:
*	- VisualData.hpp
*	- AnimationData.hpp
******************************************************************************
*************/

#ifndef OBJECT_ATTRIBUTES_HPP
#define OBJECT_ATTRIBUTES_HPP

#include <iostream>

namespace Att{
	using unique_ID = uint16_t;

	struct Coord
	{
		int x;
		int y;
	};

	enum class Priority
	{
		BACK, MIDDLE, FRONT
	};

}


#endif