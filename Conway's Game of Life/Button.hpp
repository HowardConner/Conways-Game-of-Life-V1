/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <iostream>

#include "SFML/Graphics.hpp"	// for sf::RectShape
#include "Game-Engine/Interface Classes/vDrawableInterface.hpp"

// Define Constants
const float TransparancyValue = 0.5;

class Button : public DrawableInterface
{
public:
	enum State
	{
		Active = 0, Pressed, Deactive
	};
	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //
	// constructor
	Button(sf::Vector2f& buttonSize, const sf::Texture* pActiveTexture);

	// Default Constructor
	Button();

	// Copy Constructor
	Button(const Button& copy);

	// Copy Assignment Operator
	Button& operator=(const Button& rhs);

	// Destructor
	~Button();


	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //
	// Setters
	// set the texture
	void setTexture(const sf::Texture* newTexture);
	// set position
	void setPosition(const sf::Vector2f& newPosition);
	// set hitbox size
	void setSize(const sf::Vector2f& newSize);
	

	// Getters
	// get the texture
	const sf::Texture* getTexture() const;
	// get the hitbox of the button
	sf::FloatRect getHitbox() const;
	// get position of the button
	sf::Vector2f getPosition() const;
	// get the size of the button
	sf::Vector2f getSize() const;

	// check statements
	// check if a point (the mouse cursor) is in the rectangle shape
	bool contains(const sf::Vector2f& pointToCheck) const;
	// check if a float rectangle overlaps with the hitbox (idk why this matters
	bool intersects(const sf::FloatRect& shapeToCheck) const;


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
	virtual void draw(sf::RenderWindow& window) const;

	/* mFunction Name:
	* Description:
	* Inputs:
	* Outputs:
	*/
	


private:
	State mButtonState;					// current state of the button
	sf::RectangleShape mButtonShape;	// shape representing the button. Rectangle Shape hitbox
	// --------------------------------------------------------------------------------------------- //
	//								  PRIVATE   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* mFunction Name: Set State of Button
	* Description: Set the state of the button and update it accordingly (greying out texture if dissabled etc.
	* Inputs: State to change to
	* Outputs: true if change made, else false
	*/
	bool setState(const Button::State& newState);


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