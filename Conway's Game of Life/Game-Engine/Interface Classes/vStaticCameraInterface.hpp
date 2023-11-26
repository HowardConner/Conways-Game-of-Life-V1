/*****************************************************************************
**************
* Programmer: Conner Howard
* File: Camera
* Date:
* Description: The camera class is responsible for adjusting the outputed view of
*	the scene to the user. It has move commands
******************************************************************************
*************/
#ifndef VIRTUAL_STATIC_CAMERA_INTERFACE_HPP
#define VIRTUAL_STATIC_CAMERA_INTERFACE_HPP

#include <iostream>

#include "SFML/Graphics.hpp"
#include "vUpdateInterface.hpp"


class StaticCameraInterface
{
public:
	// offset rectangle that contains offset variables for different directions
	struct offsetRect
	{
		float top;
		float bottom;
		float left;
		float right;
	};


	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //
	// constructor
	// requires an opened render window to pair with. Uses for size information
	StaticCameraInterface(sf::RenderWindow& displayWindow);

	// destructor
	virtual ~StaticCameraInterface();

	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //
	// setters
	// Velocity percent is 100% = 1.0f. Velocity is a magnitude, thus always positive.
	//void setVeloctiy(const float& percentScreenPerStep = 1.f);

	// getters
	const sf::View& getView() const;
	sf::FloatRect getViewBox() const;



	// --------------------------------------------------------------------------------------------- //
	//								  PUBLIC   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* mFunction Name: Updates the View of the render window to current conditions
	* Description: Equivalent to "window.setView()"
	* Inputs: output render window
	* Outputs: none
	*/
	void updateView();

	/* mFunction Name: Move Camera
	* Description: Moves the camera in the relative direction indicated by the orientation and by
	*	the percent velocity (1 = 100% nominal velcity)
	* Inputs: orientation and percent nominal velocity
	* Outputs:
	*/
	//void move(const CamDirection& orientation, const float& percentVelocity = 1.0);

	/* mFunction Name: Move Camera
	* Description: Moves the camera by scaling the integer number of pixels in the Window to match in view
	*	velocity is a function of the number of pixels in the window that moves the view
	* Inputs: vector of mouse int delta and percent nominal velocity
	* Outputs:
	*/
	//void move(sf::Vector2i& windowDelta);

	/* mFunction Name: Resize Viewport from Window update
	* Description: Uses the event parameters to resize the internal viewport and updates the output panel
	* Inputs:
	* Outputs:
	*/
	//void resizeView(const sf::Event::SizeEvent eventSize);

	/* mFunction Name: Resize Viewport for new Resolution
	* Description: designates a new resolution/ aspect ratio for the camera
	* Inputs: size (width X height) of the new resolutions
	* Outputs:
	*/
	void resizeView(const float& width, const float& height);

	/* mFunction Name: Zoom Window
	* Description: Zooms the display screen by the scaling factor. Treat as percent
	*	zoom where 100 is 100% zoom out and -100 is -100% zoom in
	* Inputs: Multiplier to zoom, 0 being no zooming, positive amount zoom out,
	*	and negative amount zoom out
	* Outputs: none
	*/
	void zoom(const float& scalingFactor = 0.0);

	/* mFunction Name: Center View on rectangleFrame
	* Description: Center the camera on the rectangleFrame. perserves aspect ratio plus offset border.
	*	PercentShapeOffset is a percent of dims that added outside the rectangleFrame view
	* Inputs: FloatRec of shape to center, percent of shape dims to offset by
	* Outputs: none
	*/
	void centerOn(const sf::FloatRect& rectangleFrame, const float& percentShapeOffset = 0.0);

	/* mFunction Name: Center View on Rectangle Shape
	* Description: Center the Camera on the Shape provided
	* Inputs: reference to a square shape, percent of shape's dims to take offsets from
	* Outputs: none
	*/
	void centerOn(const sf::RectangleShape& rectObject, const float& percentShapeOffset = 0.0);

	/* mFunction Name: Center on Rectangle Shape
	* Description: Centers on a rectangle shape with a fixed pixel view size value
	*	Viewsize is exact pixel count. rejects zero
	* Inputs: object to center on, pixel dims of frame centered on that object
	* Outputs: none
	*/
	void centerOn(const sf::RectangleShape& rectObject, const sf::Vector2f& ViewSize);

	/* mFunction Name: Center View on Circle Shape
	* Description: Center the Camera on circle shape
	* Inputs: reference to a circle shape, percent of shape's dims to take offsets from
	* Outputs: none
	*/
	void centerOn(const sf::CircleShape& circObject, const float& percentShapeOffset = 0.0);

	/* mFunction Name: Center on Circle
	* Description: centers view on a circle object with the defined exact pixel size from
	*	ViewSize variable. Takes exact pixel count. Rejects zero
	* Inputs: Circle to center on, pixel sizes of the new view
	* Outputs:
	*/
	void centerOn(const sf::CircleShape& circObject, const sf::Vector2f& ViewSize);

	/* mFunction Name: Center View on Point
	* Description: Center camera on an (X,Y) point and applys the size variable
	*	to determin the width (x) and height (y) of the viewbox. If size = 0x0,
	*	then does not resize box at all. Rejects negative sizes
	* Inputs: Center point coordinates, size of frame to center around the point
	* Outputs: none
	*/
	void centerOn(const sf::Vector2f& centerPoint, const sf::Vector2f& ViewSize = { 0,0 });

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
	inline sf::Vector2f convertWindowToView(const sf::Vector2i& coordInWindow);


protected:
	//float mAspectRatio;
	sf::Vector2f mResolution;
	sf::Vector2f mOffset;
	//sf::Vector2f mVelocity;			// velocity of moving
	//float mVelocityScreenPercent;	// velocity function as percent of screen dims/step
	//float moveModifier = 0.05;
	bool mNeedUpdate = true;
	sf::View mCamView;
	sf::RenderWindow& mBoundWindow;	// current open window that this controller interacts with


	// --------------------------------------------------------------------------------------------- //
	//								  PROTECTED   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* mFunction Name: Update Velocity
	* Description: Calculates the new velocity functions. Useful after a resize to keep relative velocites
	*	somewhat consistent
	* Inputs: none
	* Outputs: none
	*/
	//void updateVelocity();




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