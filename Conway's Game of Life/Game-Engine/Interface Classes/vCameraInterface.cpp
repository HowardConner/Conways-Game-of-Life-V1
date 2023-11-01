/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#include "vCameraInterface.hpp"

// --------------------------------------------------------------------------------------------- //
//				Constructors, Default Constructors, Copy Constructors, Destructors
// --------------------------------------------------------------------------------------------- //
// constructor
// requires an opened render window to pair with. Uses for size information
CameraInterface::CameraInterface(sf::RenderWindow& displayWindow, const float& velocityPercentOfScreenPerStep) :
	mBoundWindow(displayWindow),
	mCamView(sf::Vector2f(displayWindow.getSize().x / 2, displayWindow.getSize().y / 2),
		sf::Vector2f(displayWindow.getSize().x, displayWindow.getSize().y))
{
	this->mOffset = { 0,0 };
	this->mResolution = sf::Vector2f(displayWindow.getSize().x, displayWindow.getSize().y);

	// set velocity
	setVeloctiy(velocityPercentOfScreenPerStep);
}

// destructor
CameraInterface::~CameraInterface()
{

}

// --------------------------------------------------------------------------------------------- //
//									Setters and Getters
// --------------------------------------------------------------------------------------------- //
// setters
void CameraInterface::setVeloctiy(const float& percentScreenPerStep)
{
	if (percentScreenPerStep >= 0)
	{
		this->mVelocityScreenPercent = percentScreenPerStep;
	}
	else
	{
		this->mVelocityScreenPercent = (-1) * percentScreenPerStep;
	}
	// update velocity values
	this->mVelocity.x = mVelocityScreenPercent * this->mResolution.x;
	this->mVelocity.y = mVelocityScreenPercent * this->mResolution.y;
}

// getters
const sf::View& CameraInterface::getView() const
{
	return this->mCamView;
}
sf::FloatRect CameraInterface::getViewBox() const
{
	return this->mCamView.getViewport();
}










// --------------------------------------------------------------------------------------------- //
//								  PUBLIC   Member Functions
// --------------------------------------------------------------------------------------------- //
/* mFunction Name: Updates the View of the render window to current conditions
* Description: Equivalent to "window.setView()"
* Inputs: output render window
* Outputs: none
*/
void CameraInterface::updateView()
{
	mBoundWindow.setView(this->mCamView);
}

/* mFunction Name: Move Camera
* Description: Moves the camera in the relative direction indicated by the orientation and by
*	the percent velocity (1 = 100% nominal velcity)
* Inputs: orientation and percent nominal velocity
* Outputs:
*/
void CameraInterface::move(const CamDirection& orientation, const float& percentVelocity)
{

	switch (orientation)
	{
	case CamDirection::UP:
		this->mCamView.move(sf::Vector2f(0.f, -mVelocity.y * percentVelocity * this->moveModifier));
		break;
	case CamDirection::DOWN:
		this->mCamView.move(sf::Vector2f(0.f, mVelocity.y * percentVelocity * this->moveModifier));
		break;
	case CamDirection::LEFT:
		this->mCamView.move(sf::Vector2f(-mVelocity.x * percentVelocity * this->moveModifier, 0.f));
		break;
	case CamDirection::RIGHT:
		this->mCamView.move(sf::Vector2f(mVelocity.x * percentVelocity * this->moveModifier, 0.f));
		break;
	}

	// set update flag
	this->mNeedUpdate = true;
}

/* mFunction Name: Move Camera
* Description: Moves the camera by scaling the integer number of pixels in the Window to match in view
*	velocity is a function of the number of pixels in the window that moves the view
* Inputs: vector of mouse int delta and percent nominal velocity
* Outputs:
*/
void CameraInterface::move(sf::Vector2i& windowDelta)
{
	// define variables
	sf::Vector2f scaledDelta = convertWindowToView(windowDelta);

	// update move
	this->mCamView.move(scaledDelta);

	// set update flag
	this->mNeedUpdate = true;

}

/* mFunction Name: Resize Viewport from Window update
* Description: Uses the event parameters to resize the internal viewport and updates the output panel
* Inputs:
* Outputs:
*/
void CameraInterface::resizeView(const sf::Event::SizeEvent eventSize)
{
	resizeView(eventSize.width, eventSize.height);

	updateVelocity();
}

/* mFunction Name: Resize Viewport for new Resolution
* Description: designates a new resolution/ aspect ratio for the camera
* Inputs: size (width X height) of the new resolutions
* Outputs:
*/
void CameraInterface::resizeView(const float& width, const float& height)
{
	this->mCamView.setSize(sf::Vector2f(width, height));

	// update velocities
	updateVelocity();

	// set update flag
	this->mNeedUpdate = true;
}

/* mFunction Name: Zoom Window
* Description: Zooms the display screen by the scaling factor. Treat as percent
*	zoom where 100 is 100% zoom out and -100 is -100% zoom in
* Inputs: Multiplier to zoom, 0 being no zooming, positive amount zoom out,
*	and negative amount zoom out
* Outputs: none
*/
void CameraInterface::zoom(const float& scalingFactor)
{
	// Set new zoom factor
	this->mCamView.zoom(1 + scalingFactor * 0.01);// * this->mVelocityScreenPercent

	// update velocities
	updateVelocity();

	// set update flag
	this->mNeedUpdate = true;
}

/* mFunction Name: Center View on rectangleFrame
* Description: Center the camera on the rectangleFrame. perserves aspect ratio plus offset border.
*	PercentShapeOffset is a percent of dims that added outside the rectangleFrame view
* Inputs: FloatRec of shape to center, percent of shape dims to offset by
* Outputs: none
*/
void CameraInterface::centerOn(const sf::FloatRect& rectangleFrame, const float& percentShapeOffset)
{
	// define variables
	sf::Vector2f curViewSize(this->mResolution.x, this->mResolution.y);

	float offsetWidth = rectangleFrame.width * (1 + 2 * percentShapeOffset),
		offsetHeight = rectangleFrame.height * (1 + 2 * percentShapeOffset);

	float ratioX = offsetWidth / curViewSize.x,
		ratioY = offsetHeight / curViewSize.y;

	sf::Vector2f viewCenter(rectangleFrame.left + 0.5 * rectangleFrame.width,
		rectangleFrame.top + 0.5 * rectangleFrame.height);

	sf::Vector2f viewSize(0, 0);

	// check if ratios are equal, if so, even scaling
	if (ratioX == ratioY)
	{
		// evenly scale by boarder
		// keep as is
	}
	else if (ratioX > ratioY)
	{
		// the X dim has greater change, thus the Y dim is dependent on X:
		offsetHeight = offsetWidth * (curViewSize.y / curViewSize.x);
	}
	else if (ratioX < ratioY)
	{
		// the Y dim has greater precidence, thus X dim is dependent on current Y
		offsetWidth = offsetHeight * (curViewSize.x / curViewSize.y);
	}
	// update the temp viewport
	viewSize.x = offsetWidth;
	viewSize.y = offsetHeight;

	std::cout << "adjusted offsets (" << offsetWidth << ", " << offsetHeight << ")\n";
	std::cout << "new center:(" << viewCenter.x << ", " << viewCenter.y << ")   " << \
		viewSize.x << " x " << viewSize.y << std::endl << std::endl;

	// apply to cam view
	this->mCamView.setSize(viewSize);
	this->mCamView.setCenter(viewCenter);

	// update velocities for new relative view
	updateVelocity();

	// activate update flag
	this->mNeedUpdate = true;
}

/* mFunction Name: Center View on Rectangle Shape
* Description: Center the Camera on the Shape provided
* Inputs: reference to a square shape, percent of shape's dims to take offsets from
* Outputs: none
*/
void CameraInterface::centerOn(const sf::RectangleShape& rectObject, const float& percentShapeOffset)
{
	// define variables
	sf::FloatRect rectFrame(rectObject.getPosition().x, rectObject.getPosition().y,
		rectObject.getSize().x, rectObject.getSize().y);

	// call centerOn() for floatRect object
	centerOn(rectFrame, percentShapeOffset);
}

/* mFunction Name: Center on Rectangle Shape
* Description: Centers on a rectangle shape with a fixed pixel view size value
*	Viewsize is exact pixel count. rejects zero
* Inputs: object to center on, pixel dims of frame centered on that object
* Outputs: none
*/
void CameraInterface::centerOn(const sf::RectangleShape& rectObject, const sf::Vector2f& ViewSize)
{
	if (ViewSize.x != 0 && ViewSize.y != 0)
	{
		// define variables
		sf::Vector2f center(rectObject.getPosition().x + 0.5 * rectObject.getSize().x,
			rectObject.getPosition().y + 0.5 * rectObject.getSize().y);
		sf::FloatRect rectFrame(center, ViewSize);

		// now use defined centerOn() for floatRect
		centerOn(rectFrame, 0.f);
	}
}

/* mFunction Name: Center View on Circle Shape
* Description: Center the Camera on circle shape
* Inputs: reference to a circle shape, percent of shape's dims to take offsets from
* Outputs: none
*/
void CameraInterface::centerOn(const sf::CircleShape& circObject, const float& percentShapeOffset)
{
	// define variables
	// shape is a box that has size 2 * radius that is centered on the circle's center
	sf::FloatRect circleFrame(circObject.getPosition().x, circObject.getPosition().y,
		circObject.getRadius() * 2, circObject.getRadius() * 2);

	// now call the floatRect version of the centerOn()
	centerOn(circleFrame, percentShapeOffset);

	// update frame velocity
	updateVelocity();

	// set update flag
	this->mNeedUpdate = true;
}

/* mFunction Name: Center on Circle
* Description: centers view on a circle object with the defined exact pixel size from
*	ViewSize variable. Takes exact pixel count. Rejects zero
* Inputs: Circle to center on, pixel sizes of the new view
* Outputs:
*/
void CameraInterface::centerOn(const sf::CircleShape& circObject, const sf::Vector2f& ViewSize)
{
	if (ViewSize.x != 0 && ViewSize.y != 0)
	{
		// define variables
		sf::Vector2f center(circObject.getPosition().x + circObject.getRadius(), circObject.getPosition().y + circObject.getRadius());
		sf::FloatRect circFrame(center, ViewSize);

		// now pass into defined floatRect centerOn() function
		centerOn(circFrame, 0.f);
	}
}

/* mFunction Name: Center View on Point
* Description: Center camera on an (X,Y) point and applys the size variable
*	to determin the width (x) and height (y) of the viewbox. If size = 0x0,
*	then does not resize box at all. Rejects negative sizes
* Inputs: Center point coordinates, size of frame to center around the point
* Outputs: none
*/
void CameraInterface::centerOn(const sf::Vector2f& centerPoint, const sf::Vector2f& ViewSize)
{
	if (ViewSize.x != 0 && ViewSize.y != 0)
	{
		// define variables
		sf::FloatRect pointFrame(centerPoint.x + 0.5 * ViewSize.x, centerPoint.y + 0.5 * ViewSize.y,
			ViewSize.x, ViewSize.y);

		// call defined function center on rect
		centerOn(pointFrame, 0.f);
	}
}

/* Function Name: Convert Window Coordinate to View Coordinate
* Description: Converts a coordinate in relative to the bound output window to the corresponding
*	coordinate pair in the view window using scaling between the two
*	Useful for:
*		converting mouse input in window to relative window global coordinates
* Inputs: Coordinate Relative to window
* Preconditions:
* Outputs: Coordinate in view corresponding to where it is relative to window
* Returns: Coordinate in view corresponding to where it is relative to window
* Postconditions:
*/
sf::Vector2f CameraInterface::convertWindowToView(const sf::Vector2i& coordInWindow)
{	
	return sf::Vector2f(coordInWindow.x * (mCamView.getSize().x / mBoundWindow.getSize().x),
		coordInWindow.y * (mCamView.getSize().y / mBoundWindow.getSize().y));
}




// --------------------------------------------------------------------------------------------- //
//								  PROTECTED   Member Functions
// --------------------------------------------------------------------------------------------- //
/* mFunction Name: Update Velocity
* Description: Calculates the new velocity functions. Useful after a resize to keep relative velocites
*	somewhat consistent
* Inputs: none
* Outputs: none
*/
void CameraInterface::updateVelocity()
{
	// update velocity relative to screen size
	this->mVelocity.x = this->mCamView.getSize().x * this->mVelocityScreenPercent;
	this->mVelocity.y = this->mCamView.getSize().y * this->mVelocityScreenPercent;
}

