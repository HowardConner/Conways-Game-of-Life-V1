/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#include "InputOverloader.hpp"


// --------------------------------------------------------------------------------------------- //
//				Constructors, Default Constructors, Copy Constructors, Destructors
// --------------------------------------------------------------------------------------------- //




// --------------------------------------------------------------------------------------------- //
//									Setters and Getters
// --------------------------------------------------------------------------------------------- //
// setters
// Set a binding to a Key, a mouse button, or mouse wheel event
//	for Keys-- will always push to front of stack
// true if new binding set
bool InputOverloader::setBinding(const sf::Keyboard::Key& bindKeyboardKey)
{
	// define varaiables

	// check if already bound
	if (this->mActiveInputFlags.HasFlag(Active_Inputs_Flag::KeyPrimary) && this->mBoundPrimaryBoundKey == bindKeyboardKey)
	{
		// bound to primary
		return false;
	}
	else if (this->mActiveInputFlags.HasFlag(Active_Inputs_Flag::KeySecondary) && this->mBoundPrimaryBoundKey == bindKeyboardKey)
	{
		// bound to secondary
		return false;
	}

	// bind the new key
	// shift the current key bindings, then add the new one
	if (this->mActiveInputFlags.HasFlag(Active_Inputs_Flag::KeyPrimary))
	{
		// shift active
		this->mBoundSecondaryBoundKey = this->mBoundPrimaryBoundKey;
		// set secondary flag
		this->mActiveInputFlags.SetFlag(Active_Inputs_Flag::KeySecondary);
		// insert new key
		this->mBoundPrimaryBoundKey = bindKeyboardKey;
	}
	else
	{
		// insert new keystroke
		this->mBoundPrimaryBoundKey = bindKeyboardKey;
		// set flag
		this->mActiveInputFlags.SetFlag(Active_Inputs_Flag::KeyPrimary);
	}


	return true;
}

bool InputOverloader::setBinding(const sf::Mouse::Button& bindMouseButton)
{
	// define varaiables

	// check if already bound
	if (this->mActiveInputFlags.HasFlag(Active_Inputs_Flag::MouseButton))
	{
		// flag set, simply update
		this->mBoundMouseButton = bindMouseButton;
	}
	else
	{
		// set the new button
		this->mBoundMouseButton = bindMouseButton;
		// set new flag
		this->mActiveInputFlags.SetFlag(Active_Inputs_Flag::MouseButton);
	}

	return true;
}

// remove a binding
//		return true if removed and cleared
bool InputOverloader::removeBinding(const sf::Keyboard::Key& removeKey)
{
	// define varaiables
	bool result = false;

	// check if key is bound
	if (this->mActiveInputFlags.HasFlag(Active_Inputs_Flag::KeyPrimary) && this->mBoundPrimaryBoundKey == removeKey)
	{
		// primary is set to the target key, remove it
		if (this->mActiveInputFlags.HasFlag(Active_Inputs_Flag::KeySecondary))
		{
			// simply overwrite primary and unset secondary
			this->mBoundPrimaryBoundKey = this->mBoundSecondaryBoundKey;
			this->mActiveInputFlags.UnsetFlag(Active_Inputs_Flag::KeySecondary);
		}
		else
		{
			// simply unset primary flag
			this->mActiveInputFlags.UnsetFlag(Active_Inputs_Flag::KeyPrimary);
		}
		result = true;
	}
	// check if secondary
	else if (this->mActiveInputFlags.HasFlag(Active_Inputs_Flag::KeySecondary) && this->mBoundSecondaryBoundKey == removeKey)
	{
		// yes, its the second one. Simply uncheck it
		this->mActiveInputFlags.UnsetFlag(Active_Inputs_Flag::KeySecondary);
		result = false;
	}

	return result;
}

bool InputOverloader::removeBinding(const sf::Mouse::Button& removeButton)
{
	// define varaiables
	bool result = false;

	// check if removeButtom matches active (if active)
	if (this->mActiveInputFlags.HasFlag(Active_Inputs_Flag::MouseButton) && this->mBoundPrimaryBoundKey == removeButton)
	{
		// uncheck the binding flag
		this->mActiveInputFlags.UnsetFlag(Active_Inputs_Flag::MouseButton);

		// update result
		result = false;
	}

	return result;
}

// getters
// check if a binding is set (active) for this command tree
bool InputOverloader::isKeyActive(const Active_Inputs_Flag& whichBindingToCheck) const
{
	return this->mActiveInputFlags.HasFlag(whichBindingToCheck);
}

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
bool InputOverloader::triggered() const
{
	// check if primary key is pressed
	if (this->mActiveInputFlags.HasFlag(Active_Inputs_Flag::KeyPrimary) && sf::Keyboard::isKeyPressed(this->mBoundPrimaryBoundKey))
	{
		return true;
	}
	// check if Secondary key is pressed
	if (this->mActiveInputFlags.HasFlag(Active_Inputs_Flag::KeySecondary) && sf::Keyboard::isKeyPressed(this->mBoundSecondaryBoundKey))
	{
		return true;
	}

	// check if mousewheel is pressed
	if (this->mActiveInputFlags.HasFlag(Active_Inputs_Flag::MouseButton) && sf::Keyboard::isKeyPressed(this->mBoundPrimaryBoundKey))
	{
		return true;
	}

	return false;
}

/* mFunction Name:
* Description: Pass by reference check of system event queue
* Inputs:
* Outputs:
*/
bool InputOverloader::triggeredFromEvent(sf::Event& isEvent) const
{
	// check if primary key is pressed
	if (this->mActiveInputFlags.HasFlag(Active_Inputs_Flag::KeyPrimary) && isEvent.key.code == this->mBoundPrimaryBoundKey)
	{
		return true;
	}
	// check if Secondary key is pressed
	if (this->mActiveInputFlags.HasFlag(Active_Inputs_Flag::KeySecondary) && isEvent.key.code == this->mBoundSecondaryBoundKey)
	{
		return true;
	}

	// check if mousewheel is pressed
	if (this->mActiveInputFlags.HasFlag(Active_Inputs_Flag::MouseButton) && isEvent.mouseButton.button == this->mBoundPrimaryBoundKey)
	{
		return true;
	}

	return false;
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