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
	// Unique_ID tag - indicates ID number
	//		RESERVED: -1 = null
	//		RESERVED: UINT16_MAX = null
	using unique_ID = uint16_t;
	const uint16_t NULL_UNIQUE_ID = -1;
	// Render_ID tag - indicates ID number
	//		RESERVED: -1 = null
	//		RESERVED: UINT64_MAX = null
	using render_ID = uint64_t;
	const uint64_t NULL_RENDER_ID = -1;
	// Camera_ID tag - indicates ID number
	//		RESERVED: -1 = null
	//		RESERVED: UINT16_MAX = null
	using camera_ID = uint16_t;
	const uint16_t NULL_CAMERA_ID = -1;
	// Hud_ID tag - indicates ID number
	//		RESERVED: -1 = null
	//		RESERVED: UINT16_MAX = null
	using hud_ID = uint16_t;
	const uint16_t NULL_HUD_ID = -1;


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