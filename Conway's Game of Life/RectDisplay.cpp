/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#include "RectDisplay.hpp"


// --------------------------------------------------------------------------------------------- //
//				Constructors, Default Constructors, Copy Constructors, Destructors
// --------------------------------------------------------------------------------------------- //
// Default constructor
RectDisplay::RectDisplay(const sf::Vector2f& rectSize) : DrawableInterface()
{
	this->mShape.setSize(rectSize);
}

// copy constructor
RectDisplay::RectDisplay(const RectDisplay& copy) : DrawableInterface()
{
	this->mActiveTexture = copy.mActiveTexture;
	this->mShape = copy.mShape;
	this->mTextureList = copy.mTextureList;
}

// copy assignment operator
RectDisplay& RectDisplay::operator=(const RectDisplay& rhs)
{
	this->mActiveTexture = rhs.mActiveTexture;
	this->mShape = rhs.mShape;
	this->mTextureList = rhs.mTextureList;

	return *this;
}

//destructor
RectDisplay::~RectDisplay()
{

}


// --------------------------------------------------------------------------------------------- //
//									Setters and Getters
// --------------------------------------------------------------------------------------------- //
// Setters
// set size of shape
void RectDisplay::setSize(const sf::Vector2f& newSize)
{
	this->mShape.setSize(newSize);
}

// set position of the shape
void RectDisplay::setPosition(const sf::Vector2f& newPosition)
{
	this->mShape.setPosition(newPosition);
}

// set the active texture (from the texture array)
//		returns: true if texture set, false if not found
//bool RectDisplay::setActiveTexture(const size_t& texture_id)
//{
//	// define variables
//	bool result = false;
//
//	if (texture_id < this->mTextureList.size())
//	{
//		// set the texture
//		this->mShape.setTexture(&this->mTextureList.at(texture_id));
//
//		// update the active texture number
//		this->mActiveTexture = texture_id;
//
//		result = true;
//	}
//
//	return result;
//}

// Set Texture pointer for display shape
void RectDisplay::setTexture(const sf::Texture* newTexture)
{
	this->mShape.setTexture(newTexture);
}


// Getters
// get size of shape
sf::Vector2f RectDisplay::getSize() const
{
	return this->mShape.getSize();
}

// get position
sf::Vector2f RectDisplay::getPosition() const
{
	return this->mShape.getPosition();
}

// get the active texture Id
//size_t RectDisplay::getActiveTextureID() const
//{
//	return this->mActiveTexture;
//}


// --------------------------------------------------------------------------------------------- //
//								  PUBLIC   Member Functions
// --------------------------------------------------------------------------------------------- //
/* mFunction Name: Add Texture to Display
* Description: Attempts to create and insert a new texture into the list of textures. Note: a local
*	texture object is stored in the display shape
* Inputs: Filename of file to create into the texture (png, jpg, etc)
* Outputs: returns the index corresponding to the texture
*/
//size_t RectDisplay::addTexture(std::string& filename)
//{
//	// define variables
//	size_t newTextureID = -1;
//	sf::Texture tempTexture;
//
//	// open file
//	if (tempTexture.loadFromFile(filename))
//	{
//		// save the temp texture to the list
//		this->mTextureList.push_back(tempTexture);
//
//		// get the index value of the new last item
//		newTextureID = this->mTextureList.size() - 1;
//	}
//
//	return newTextureID;
//}

/* mFunction Name: Snap Display shape to Float Rectangle
* Description: Allows the display shape to be positioned to a corner of the rectangle (attempting to keep
*	it inside the rectangle). Applies relative to corner specificed for the frame and the displayshape
* Inputs: FloatRect of the shape to lock to (ie, a viewport), and corner of that frame to lock to
* Outputs: true if success, false otherwise
*/
void RectDisplay::snapTo(const sf::FloatRect& frameToLockTo, const Orientation& corner)
{
	// define variables
	sf::Vector2f newPosition;

	switch (corner)
	{
	case Orientation::TopLeft:
		newPosition.x = frameToLockTo.left;
		newPosition.y = frameToLockTo.top;
		break;
	case Orientation::TopRight:
		newPosition.x = frameToLockTo.left + frameToLockTo.width - this->mShape.getSize().x;
		newPosition.y = frameToLockTo.top;
		break;
	case Orientation::BottomLeft:
		newPosition.x = frameToLockTo.left;
		newPosition.y = frameToLockTo.top + frameToLockTo.height - this->mShape.getSize().y;
		break;
	case Orientation::BottomRight:
		newPosition.x = frameToLockTo.left + frameToLockTo.width - this->mShape.getSize().x;
		newPosition.y = frameToLockTo.top + frameToLockTo.height - this->mShape.getSize().y;
		break;
	default:
		std::cout<< "Orientation not Supported in RectDisplay::snapTo()" << std::endl;
		return;
		break;
	};

	// set the position
	this->mShape.setPosition(newPosition);
}

/* mFunction Name: Snap Display shape to Float Rectangle
* Description: Allows the display shape to be positioned to a corner of the rectangle (attempting to keep
*	it inside the rectangle). Applies relative to corner specificed for the frame and the displayshape
* Inputs: FloatRect of the shape to lock to (ie, a viewport), and corner of that frame to lock to
* Outputs: true if success, false otherwise
*/
void RectDisplay::snapTo(const sf::IntRect& frameToLockTo, const Orientation& corner)
{
	// define variables
	sf::FloatRect floatConverted(sf::Vector2f(frameToLockTo.left, frameToLockTo.top),
		sf::Vector2f(frameToLockTo.width, frameToLockTo.height));

	snapTo(floatConverted, corner);
}

/* mFunction Name: Snap Display Shape to Point
* Description: Snaps the corner of shape to the point indicated with applied offsets
* Inputs: Point to snap to, which corner of the shape to alighn to, and any offset
* Outputs: none
*/
void RectDisplay::snapTo(const sf::Vector2f& point, const Orientation& corner, const sf::Vector2f& offset)
{
	// define variables
	sf::Vector2f newPosition(point);

	// apply offset
	newPosition - offset;

	switch (corner)
	{
	case Orientation::TopLeft:
		
		break;
	case Orientation::TopRight:
		newPosition.x -= this->mShape.getSize().x;
		
		break;
	case Orientation::BottomLeft:
		
		newPosition.y -= this->mShape.getSize().y;
		break;
	case Orientation::BottomRight:
		newPosition.x -= this->mShape.getSize().x;
		newPosition.y -= this->mShape.getSize().y;
		break;
	default:
		std::cout << "Orientation not Supported in RectDisplay::snapTo(point)" << std::endl;
		return;
		break;
	};

	// set the position
	this->mShape.setPosition(newPosition);
}

/* mFunction Name: Resize Relative to FLoat Rectangle
* Description: Allows the Display shape to be resized relative to a float rectangle (ie, a viewport)
*	so that it can be a constant size that is dependent of the FloatRect input
* Precondition: RelativePercent is a positive number
* Inputs: FloatRectangle to scale relative to
	relative percent where 100.0 = 100% (size), 200.0 = 200% = twice size,
		50.0 = 50.0% = half the size
* Outputs: none
*/
void RectDisplay::resizeRelativeTo(const sf::FloatRect& relativeFrame, const float& relativePercent)
{
	this->mShape.setSize(sf::Vector2f(relativePercent * 0.01 * relativeFrame.width, relativePercent * 0.01 * relativeFrame.height));
}

/* mFunction Name: Rectangular Display Draw
* Description: Draws the rectangular display to the supplied window
* Inputs: window to draw to
* Outputs: none
*/
void RectDisplay::draw(sf::RenderWindow& window) const
{
	window.draw(this->mShape);
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