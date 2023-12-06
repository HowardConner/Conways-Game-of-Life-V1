/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#include "Button.hpp"

// --------------------------------------------------------------------------------------------- //
//				Constructors, Default Constructors, Copy Constructors, Destructors
// --------------------------------------------------------------------------------------------- //
// constructor
Button::Button(sf::Vector2f& buttonSize, const sf::Texture* pActiveTexture)
{
	this->mButtonShape.setSize(buttonSize);
	this->mButtonShape.setTexture(pActiveTexture);

	this->setState(Button::State::Active);
}

// Default Constructor
Button::Button()
{
	this->mButtonShape.setFillColor(sf::Color::Red);
	this->mButtonShape.setSize(sf::Vector2f(200, 200));

	this->setState(Button::State::Deactive);
}

// Copy Constructor
Button::Button(const Button& copy)
{
	this->mButtonShape = copy.mButtonShape;
	
	this->setState(copy.mButtonState);
}

// Copy Assignment Operator
Button& Button::operator=(const Button& rhs)
{
	this->mButtonShape = rhs.mButtonShape;

	this->setState(rhs.mButtonState);
	
	return *this;
}

// Destructor
Button::~Button()
{
	// nothing to free
}


// --------------------------------------------------------------------------------------------- //
//									Setters and Getters
// --------------------------------------------------------------------------------------------- //
// Setters
// set the texture
void Button::setTexture(const sf::Texture* newTexture)
{
	this->mButtonShape.setTexture(newTexture);
}

// set position
void Button::setPosition(const sf::Vector2f& newPosition)
{
	this->mButtonShape.setPosition(newPosition);
}

// set hitbox size
void Button::setSize(const sf::Vector2f& newSize)
{
	this->mButtonShape.setSize(newSize);
}

// Getters
// get the texture
const sf::Texture* Button::getTexture() const
{
	return this->mButtonShape.getTexture();
}

// get the hitbox of the button
sf::FloatRect Button::getHitbox() const
{
	return this->mButtonShape.getGlobalBounds();
}

// get position of the button
sf::Vector2f Button::getPosition() const
{
	return this->mButtonShape.getPosition();
}

// get the size of the button
sf::Vector2f Button::getSize() const
{
	return this->mButtonShape.getSize();
}


// check statements
// check if a point (the mouse cursor) is in the rectangle shape
bool Button::contains(const sf::Vector2f& pointToCheck) const
{
	return this->mButtonShape.getGlobalBounds().contains(pointToCheck);
}

// check if a float rectangle overlaps with the hitbox (idk why this matters
bool Button::intersects(const sf::FloatRect& shapeToCheck) const
{
	return this->mButtonShape.getGlobalBounds().intersects(shapeToCheck);
}



// --------------------------------------------------------------------------------------------- //
//								  PUBLIC   Member Functions
// --------------------------------------------------------------------------------------------- //
/* Function Name: Draw button
* Description: Draw Button to screen
* Inputs: output render window
* Preconditions: render window must be open
* Outputs: draws button to the window
* Returns: none
* Postconditions:
*/
void Button::draw(sf::RenderWindow& window) const
{
	window.draw(this->mButtonShape);
}



// --------------------------------------------------------------------------------------------- //
//								  PRIVATE   Member Functions
// --------------------------------------------------------------------------------------------- //
/* mFunction Name: Set State of Button
* Description: Set the state of the button and update it accordingly (greying out texture if dissabled etc.
* Inputs: State to change to
* Outputs: true if change made, else false
*/
bool Button::setState(const Button::State& newState)
{
	// define variables
	bool result = false;

	// check if new state matches active state
	if (this->mButtonState == newState)
	{
		 // break from loop
	}
	else
	{
		// update state
		this->mButtonState = newState;

		// update the shape according to its state
		switch (mButtonState)
		{
		case Button::Active:
			// remove any color filtering
			this->mButtonShape.setFillColor(sf::Color::Transparent);
			break;
		case Button::Pressed:
			// white wash the key
			this->mButtonShape.setFillColor(sf::Color(255, 255, 255, TransparancyValue));
			break;
		case Button::Deactive:
			// Grey out the key texture
			this->mButtonShape.setFillColor(sf::Color(160, 160, 160, TransparancyValue));
			break;
		default:
			std::cout << "state not defined for Button::State::" << mButtonState << std::endl;
			break;
		}
		result = true;
		std::cout << "result of setState(): " << result << std::endl;
	}


	return result;
}