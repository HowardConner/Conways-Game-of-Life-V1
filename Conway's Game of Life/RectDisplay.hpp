/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#ifndef RECTANGLE_DISPLAY_SHAPE_HPP
#define RECTANGLE_DISPLAY_SHAPE_HPP

#include <iostream>
#include <vector>

#include "Game-Engine/Interface Classes/vDrawableInterface.hpp"


enum Orientation
{
	//Top = 0,
	//Bottom,
	//Left,
	//Right,
	TopLeft = 0,
	TopRight,
	BottomLeft,
	BottomRight
};


class RectDisplay : public DrawableInterface
{
public:
	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //
	// Default constructor
	RectDisplay(const sf::Vector2f& rectSize = {0.0, 0.0});

	// copy constructor
	RectDisplay(const RectDisplay& copy);

	// copy assignment operator
	RectDisplay& operator=(const RectDisplay& rhs);

	//destructor
	~RectDisplay();


	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //
	// Setters
	// set size of shape
	void setSize(const sf::Vector2f& newSize);
	// set position of the shape
	void setPosition(const sf::Vector2f& newPosition);
	// set the active texture (from the texture array)
	//		returns: true if texture set, false if not found
	//bool setActiveTexture(const size_t& texture_id);
	// Set Texture pointer for display shape
	void setTexture(const sf::Texture* newTexture);


	// Getters
	// get size of shape
	sf::Vector2f getSize() const;
	// get position
	sf::Vector2f getPosition() const;
	// get the active texture Id
	//size_t getActiveTextureID() const;


	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* mFunction Name: Add Texture to Display
	* Description: Attempts to create and insert a new texture into the list of textures. Note: a local
	*	texture object is stored in the display shape
	* Inputs: Filename of file to create into the texture (png, jpg, etc)
	* Outputs: returns the index corresponding to the texture
	*/
	//size_t addTexture(std::string& filename);

	/* mFunction Name: Snap Display shape to Float Rectangle
	* Description: Allows the display shape to be positioned to a corner of the rectangle (attempting to keep
	*	it inside the rectangle). Applies relative to corner specificed for the frame and the displayshape
	* Inputs: FloatRect of the shape to lock to (ie, a viewport), and corner of that frame to lock to
	* Outputs: true if success, false otherwise
	*/
	void snapTo(const sf::FloatRect& frameToLockTo, const Orientation& corner);

	/* mFunction Name: Snap Display shape to Float Rectangle
	* Description: Allows the display shape to be positioned to a corner of the rectangle (attempting to keep
	*	it inside the rectangle). Applies relative to corner specificed for the frame and the displayshape
	* Inputs: FloatRect of the shape to lock to (ie, a viewport), and corner of that frame to lock to
	* Outputs: true if success, false otherwise
	*/
	void snapTo(const sf::IntRect& frameToLockTo, const Orientation& corner);

	/* mFunction Name: Snap Display Shape to Point
	* Description: Snaps the corner of shape to the point indicated with applied offsets
	* Inputs: Point to snap to, which corner of the shape to alighn to, and any offset
	* Outputs: none 
	*/
	void snapTo(const sf::Vector2f& point, const Orientation& corner, const sf::Vector2f& offset = {0, 0});

	/* mFunction Name: Resize Relative to FLoat Rectangle
	* Description: Allows the Display shape to be resized relative to a float rectangle (ie, a viewport)
	*	so that it can be a constant size that is dependent of the FloatRect input
	* Precondition: RelativePercent is a positive number
	* Inputs: FloatRectangle to scale relative to
		relative percent where 100.0 = 100% (size), 200.0 = 200% = twice size,
			50.0 = 50.0% = half the size 
	* Outputs: none
	*/
	void resizeRelativeTo(const sf::FloatRect& relativeFrame, const float& relativePercent = 100.0);

	/* mFunction Name: Rectangular Display Draw
	* Description: Draws the rectangular display to the supplied window
	* Inputs: window to draw to
	* Outputs: none
	*/
	void draw(sf::RenderWindow& window) const;

private:
	size_t mActiveTexture = 0;	// index of the currently active texture
	sf::RectangleShape mShape;
	std::vector<sf::Texture> mTextureList;
	// --------------------------------------------------------------------------------------------- //
	//								  PRIVATE   Member Functions
	// --------------------------------------------------------------------------------------------- //



};

// --------------------------------------------------------------------------------------------- //
//									non - Member Functions
// --------------------------------------------------------------------------------------------- //
/* Function Name:
* Description:
* Inputs:
* Preconditions:
* Outputs:
* Returns:
* Postconditions:
*/


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