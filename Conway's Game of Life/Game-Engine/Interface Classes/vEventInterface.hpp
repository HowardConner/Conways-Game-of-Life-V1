/*****************************************************************************
**************
* Programmer: Conner Howard
* File: Virtual Event Handler
* Date:
* Description: Inhertiable virtual event handler class for objects dependent on
*	event call stack (less direct than InputInterface() )
******************************************************************************
*************/
#ifndef VIRTUAL_EVENT_INTERFACE_HPP
#define VIRTUAL_EVENT_INTERFACE_HPP

#include "SFML/Graphics.hpp"

class EventInterface
{
public:
	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //
	EventInterface() {};

	virtual ~EventInterface() {};

	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //




	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* mFunction Name: Virtual Event Handler
	* Description: Event Handler to overload
	* Inputs: Constant Reference to event to handle
	* Outputs: returns true if an event was handled, false otherwise
	*/
	virtual bool handleEvent(const sf::Event& eventToHandle) = 0;


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