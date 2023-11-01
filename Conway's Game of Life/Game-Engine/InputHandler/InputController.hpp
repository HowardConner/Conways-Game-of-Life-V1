/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#ifndef INPUT_CONTROLLER_HPP
#define INPUT_CONTROLLER_HPP

#include <iostream>
#include <unordered_map>
#include <vector>

#include "SFML/Graphics.hpp"
#include "InputOverloader.hpp"

using std::unordered_map;
using std::vector;


// consider rebuilding input controller as a template for an enum
enum Command
{
	Exit = 0,
	Pause,
	MoveUp,
	MoveDown,
	MoveLeft,
	MoveRight,
	ZoomIn,
	ZoomOut,


	COUNT	// Number of Commands avaliable
};

class InputController
{
public:
	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //
	// constructor
	InputController()
	{
		this->mPrevousMousePos = this->mCurrentMousePos = sf::Mouse::getPosition();
	}

	// copy constructors
	//	----- not copyable -----

	// copy assignmnet operator
	//	----- not copyable -----

	// destructor
	~InputController()
	{

	}


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
	sf::Vector2i getCursorPosition() const;

	/* mFunction Name: Get Cursor Delta Position
	* Description: Gets the returns the delta of the cursor positions since the last update call. Delta is 
	*	expressed as a Vector2i of output display 
	* Inputs: none
	* Outputs: (X,Y) of the cursor
	*/
	sf::Vector2i getCursorDelta() const;


	// --------------------------------------------------------------------------------------------- //
	//										Checks
	// --------------------------------------------------------------------------------------------- //
	/* mFunction Name: Bind to Command
	* Description: Bind a keyboard key input to command
	* Inputs: command to bind to, 
	* Outputs: none
	*/
	void bind(const Command& commandToBindTo, const sf::Keyboard::Key& keyboardKey);

	/* mFunction Name: Bind to Command
	* Description: bind mouse button to command
	* Inputs: command to bind to,
	* Outputs: none
	*/
	void bind(const Command& commandToBindTo, const sf::Mouse::Button& mouseButton);

	/* mFunction Name: Bind to Command
	* Description: bind mouse wheel movement to command
	* Inputs: command to bind to,
	* Outputs: none
	*/
	//void bind(const Command& commandToBindTo, const sf::Mouse::Wheel& mouseWheel);

	/* mFunction Name: Bind to Command
	* Description: Bind joystick button to command
	* Inputs: command to bind to,
	* Outputs: none
	*/
	//void bind(const Command& commandToBindTo, const sf::Joystick& keyboardKey);


	/* mFunction Name: Check if Command is Active
	* Description: Checks if a command is Currently activated. This is analogous to directly checking
	*	the input with sf::keyboard::isKeyPressed();
	* Inputs:
	* Outputs:
	*/
	bool isCommandActive(const Command& commandToCheck);



	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* mFunction Name: Update Inputes
	* Description: Performs routine checks of system and updates needed inputs. Also provides an optimisition check	
	*	to see if any controllers are connected
	* Inputs: none
	* Outputs: none
	*/
	void update();




private:
	bool mControllerConnected = false;
	sf::Vector2i	mPrevousMousePos;
	sf::Vector2i	mCurrentMousePos;
	sf::Vector2i	mCursorDelta;
	unordered_map<Command, InputOverloader>		mBindings;

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