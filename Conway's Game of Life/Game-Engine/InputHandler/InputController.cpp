/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#include "InputController.hpp"


// --------------------------------------------------------------------------------------------- //
//				Constructors, Default Constructors, Copy Constructors, Destructors
// --------------------------------------------------------------------------------------------- //




// --------------------------------------------------------------------------------------------- //
//									Setters and Getters
// --------------------------------------------------------------------------------------------- //
// Setters



// Getters



/* mFunction Name: Get Cursor Position
* Description: Gets the position (in terms of output panel pixels) of the cursor (mouse/ joystick axis)
*	and returns it as a Vector2i
* Inputs: none
* Outputs: (X,Y) of the cursor
*/
sf::Vector2i InputController::getCursorPosition() const
{
	// check mouse input
	return sf::Mouse::getPosition();

	// check axis input
}

/* mFunction Name: Get Cursor Delta Position
* Description: Gets the returns the delta of the cursor positions since the last update call. Delta is
*	expressed as a Vector2i of output display
* Inputs: none
* Outputs: (X,Y) of the cursor
*/
sf::Vector2i InputController::getCursorDelta() const
{
	return this->mCursorDelta;
}


// --------------------------------------------------------------------------------------------- //
//										Checks
// --------------------------------------------------------------------------------------------- //
/* mFunction Name: Bind to Command
* Description: Bind a keyboard key input to command
* Inputs: command to bind to,
* Outputs: none
*/
void InputController::bind(const Command& commandToBindTo, const sf::Keyboard::Key& keyboardKey)
{
	// check if command is already defined in keyBindings
	auto keyIt = this->mBindings.find(commandToBindTo);

	// check if bound, if not, create
	if (keyIt == this->mBindings.end())
	{
		// create temp binding variables
		InputOverloader tempOverload;
		tempOverload.setBinding(keyboardKey);

		// add to map
		this->mBindings.insert(std::pair<Command, InputOverloader>(commandToBindTo, tempOverload));
	}
	else
	{
		// command has been created, simply add it
		keyIt->second.setBinding(keyboardKey);
	}
}

/* mFunction Name: Bind to Command
* Description: bind mouse button to command
* Inputs: command to bind to,
* Outputs: none
*/
void InputController::bind(const Command& commandToBindTo, const sf::Mouse::Button& mouseButton)
{
	// check if command is already defined in keyBindings
	auto keyIt = this->mBindings.find(commandToBindTo);

	// check if bound, if not, create
	if (keyIt == this->mBindings.end())
	{
		// create temp binding variables
		InputOverloader tempOverload;
		tempOverload.setBinding(mouseButton);

		// add to map
		this->mBindings.insert(std::pair<Command, InputOverloader>(commandToBindTo, tempOverload));
	}
	else
	{
		// command has been created, simply add it
		keyIt->second.setBinding(mouseButton);
	}
}

/* mFunction Name: Bind to Command
* Description: bind mouse wheel movement to command
* Inputs: command to bind to,
* Outputs: none
*/
//void bind(const Command& commandToBindTo, const sf::Mouse::Wheel& mouseWheel);

/* mFunction Name: Check if Command is Active
* Description: Checks if a command is Currently activated. This is analogous to directly checking
*	the input with sf::keyboard::isKeyPressed();
* Inputs:
* Outputs:
*/
bool InputController::isCommandActive(const Command& commandToCheck)
{
	// check keyboard inputs
	auto keyboardIt = this->mBindings.find(commandToCheck);

	// check the different commands if actually found
	if (keyboardIt != this->mBindings.end())
	{
		// check primary key
		
		// check secondary key

		// check mouse buttom
	}

	return false;
}


// --------------------------------------------------------------------------------------------- //
//								  PUBLIC   Member Functions
// --------------------------------------------------------------------------------------------- //
/* mFunction Name: Update Inputes
* Description: Performs routine checks of system and updates needed inputs. Also provides an optimisition check
*	to see if any controllers are connected
* Inputs: none
* Outputs: none
*/
void InputController::update()
{
	// update mouse previous position for delta
	this->mPrevousMousePos = this->mCurrentMousePos;
	this->mCurrentMousePos = getCursorPosition();
	// update delta
	this->mCursorDelta = this->mCurrentMousePos - this->mPrevousMousePos;

	// check that a controller has not been detected
	// only check if false
	if(this->mControllerConnected == false)
	{
		if (sf::Joystick::isConnected(0))
		{
			std::cout << "WARNING: CONTROLLERS UNSUPPORTED AS INPUT VIA INPUT CONTROLLER" << std::endl;

			std::cout << "Controller 0 connected" << std::endl;
			this->mControllerConnected = true;
		}
	}
	// ignore otherwise
}



// --------------------------------------------------------------------------------------------- //
//								  PRIVATE   Member Functions
// --------------------------------------------------------------------------------------------- //




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