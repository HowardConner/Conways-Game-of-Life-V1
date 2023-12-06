/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#ifndef STATIC_HEADS_UP_DISPLAY_HPP
#define STATIC_HEADS_UP_DISPLAY_HPP

#include "Game-Engine/Interface Classes/vStaticCameraInterface.hpp"
#include "Game-Engine/Component Classes/Object_Attributes.hpp"	// for Att::hud_ID
#include "Game-Engine/Renderer/RenderEngine.hpp"	

// predefine renderer class and the set_ID functions
class RenderEngine;

class HeadsUpDisplay : public StaticCameraInterface
{
public:
	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //
	// constructor
	HeadsUpDisplay(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size)
		: StaticCameraInterface(window)
	{
		this->mCamView.setCenter(sf::Vector2f(position.x + 0.5 * size.x, position.y + 0.5 * size.y));
		this->mCamView.setSize(size);
	}

	//// Copy constructor
	//HeadsUpDisplay(const HeadsUpDisplay& rhs) : StaticCameraInterface(rhs)
	//{
	//	
	//}

	//// copy assingment operator
	//HeadsUpDisplay& operator=(const HeadsUpDisplay& copy)
	//{
	//	
	//}

	// destructor
	~HeadsUpDisplay()
	{
		// nothing to free

	}

	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //
	// Setters
	// set Hud_ID.
	//	Requires render engine object in order to verify that user has permission to change the ID
	Att::hud_ID setID(const RenderEngine& rendererObject, const Att::hud_ID& newHudID);

	// Getters
	Att::hud_ID getID() const;

	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //


	friend class RenderEngine;
protected:
	Att::hud_ID mHUD_ID = Att::NULL_HUD_ID;
	// --------------------------------------------------------------------------------------------- //
	//								  PROTECTED   Member Functions
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