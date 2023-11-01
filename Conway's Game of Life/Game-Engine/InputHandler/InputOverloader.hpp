/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#ifndef INPUT_OVERLOADER_HPP
#define INPUT_OVERLOADER_HPP

#include "SFML/Graphics.hpp"
#include "../Component Classes/Object_Flags.hpp"

enum class Active_Inputs_Flag
{
	KeyPrimary = 1 << 0,
	KeySecondary = 1 << 1,
	MouseButton = 1 << 2,
	//temp4 = 1 << 3,
	//JoystickButton = 1 << 4,
	//JoystickAxis = 1 << 5,
	//Flag7 = 1 << 6,
	//Flag8 = 1 << 7
};

struct InputOverloader
{
public:
	Flag_8<Active_Inputs_Flag>	mActiveInputFlags;
	sf::Keyboard::Key			mBoundPrimaryBoundKey;
	sf::Keyboard::Key			mBoundSecondaryBoundKey;
	sf::Mouse::Button			mBoundMouseButton;
	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //
	// Constructor
	InputOverloader()
	{
		this->mBoundPrimaryBoundKey		= sf::Keyboard::Key::KeyCount;
		this->mBoundSecondaryBoundKey	= sf::Keyboard::Key::KeyCount;
		this->mBoundMouseButton			= sf::Mouse::Button::ButtonCount;
	}

	// copy constructor
	// copy assingment
	// ----- do not want copying of command nodes directly ------

	// destructor
	~InputOverloader() {}


	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //
	// setters
	// Set a binding to a Key, a mouse button, or mouse wheel event
	//	for Keys-- will always push to front of stack
	//		return true if new binding set
	bool setBinding(const sf::Keyboard::Key& bindKeyboardKey);
	bool setBinding(const sf::Mouse::Button& bindMouseButton);
	// remove a binding
	//		return true if removed and cleared
	inline bool removeBinding(const sf::Keyboard::Key& removeKey);
	inline bool removeBinding(const sf::Mouse::Button& removeButton);

	// getters
	// check if a binding is set (active) for this command tree
	inline bool isKeyActive(const Active_Inputs_Flag& whichBindingToCheck) const;
	//// look at the primary Bound Keyboard key
	////	precondition: Determine that the key is active first with isKeyActive()
	//inline sf::Keyboard::Key getBoundPrimaryKey(const size_t& whichActiveKey) const;
	//// look at the secondary bound keyboard key
	////	precondition: Determine that the key is active first with isKeyActive()
	//inline sf::Keyboard::Key getBoundSecondaryKey(const size_t& whichActiveKey) const;
	//// look at the bound mouse button
	////	precondition: Determine that the key is active first with isKeyActive()
	//inline sf::Mouse::Button getBoundMouseButton() const;



	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* mFunction Name:
	* Description: Static Check of current inputs
	* Inputs:
	* Outputs:
	*/
	bool triggered() const;

	/* mFunction Name:
	* Description: Pass by reference check of system event queue
	* Inputs:
	* Outputs:
	*/
	bool triggeredFromEvent(sf::Event& isEvent) const;



	// joystick button list
	// joystick axis list
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