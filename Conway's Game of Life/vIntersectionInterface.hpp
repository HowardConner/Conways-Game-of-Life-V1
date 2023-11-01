/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#ifndef VIRTUAL_INTERSECTION_INTERFACE_HPP
#define VIRTUAL_INTERSECTION_INTERFACE_HPP

#include "SFML/Graphics.hpp"

class IntersectionInterface
{
public:
	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //
	// constructor
	IntersectionInterface() {};

	// Destructor
	virtual ~IntersectionInterface() {};


	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //
	/* Function Name: Check Intersections
	* Description: Virtual Intersection functions utalizing SFML syntax or functinoality. 
	*	Check an x,y coord as a floats, vector2f, or from a rectangle shape.
	* Inputs: X,Y point (as float or vector), or rectangle shape
	* Preconditions:
	* Outputs: true if contains point or rectangle, false otherwise
	* Returns: true if contains point or rectangle, false otherwise
	* Postconditions:
	*/
	virtual bool contains(const float& x, const float& y) = 0;
	virtual bool contains(const sf::Vector2f& point) = 0;
	virtual bool contains(const sf::FloatRect& rectangle) = 0;



	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //



private:

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