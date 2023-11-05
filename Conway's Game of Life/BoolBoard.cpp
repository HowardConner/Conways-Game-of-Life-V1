/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description:
******************************************************************************
*************/
#include "BoolBoard.hpp"


// --------------------------------------------------------------------------------------------- //
//				Constructors, Default Constructors, Copy Constructors, Destructors
// --------------------------------------------------------------------------------------------- //
// default constructor
BoolBoard::BoolBoard(const size_t& sizeX, const size_t& sizeY, const unsigned& tileSize) : 
	DrawableInterface(), IntersectionInterface(), 
	mCellArray(Cell())
{
	this->mTileSize = tileSize;

	// use built-in function which handle updating everything to scale
	this->setSize(sizeX, sizeY);
}

// destructor
BoolBoard::~BoolBoard()
{

}



// --------------------------------------------------------------------------------------------- //
//									Setters and Getters
// --------------------------------------------------------------------------------------------- //
// Setters
// resize option for the grid
void BoolBoard::setSize(const size_t& sizeX, const size_t& sizeY)
{
	// resize the board
	this->mCellArray.setSize(sizeX, sizeY);

	// resize the composite texture for future
	this->mRenderBuffer.create(mCellArray.size().x * this->mTileSize, mCellArray.size().y * this->mTileSize);

	// resize the Board Shape
	this->mCellArrRect.setSize(sf::Vector2f(mCellArray.size().x * this->mTileSize, mCellArray.size().y * this->mTileSize));

	// resize the overlay shape
	this->mGridOverlayRect.setSize(sf::Vector2f(mCellArray.size().x * this->mTileSize, mCellArray.size().y * this->mTileSize));

	// set refresh flag
	this->needsUpdate = true;
}

// set cell's active and next states to the provided state
void BoolBoard::overrideCellState(const size_t& whereX, const size_t& whereY, const LifeState& newState)
{
	// check if in bounds
	if (this->mCellArray.isInArray(whereX, whereY))
	{
		// in bounds, update the point
		this->mCellArray.at(whereX, whereY).activeState = newState;
		this->mCellArray.at(whereX, whereY).nextState = newState;

		// set update flag
		this->needsUpdate = true;
	}
}

// set cell activeState
void BoolBoard::setCellActiveState(const size_t& whereX, const size_t& whereY, const LifeState& newState)
{
	// check if in bounds
	if(this->mCellArray.isInArray(whereX, whereY))
	{
		// in bounds, update the point
		this->mCellArray.at(whereX, whereY).activeState = newState;
	}
}

// set cell's next expressed nextState
void BoolBoard::setCellNextState(const size_t& whereX, const size_t& whereY, const LifeState& newState)
{
	// check if in bounds
	if (this->mCellArray.isInArray(whereX, whereY))
	{
		// in bounds, update the point
		this->mCellArray.at(whereX, whereY).nextState = newState;
	}
}

// set Board Outline
void BoolBoard::setBoardOutline(const sf::Color& outlineColor, const float& size)
{
	// update the main output board rectangle
	this->mCellArrRect.setOutlineColor(outlineColor);
	this->mCellArrRect.setOutlineThickness(size);

	// trigger update flag
	//this->needsUpdate = true;
}


// Getters
// get LifeState of a cell
// returns LifeState::DEAD by default
LifeState BoolBoard::getCellState(const size_t& whereX, const size_t& whereY) const
{
	// define variables
	LifeState result = LifeState::DEAD;

	// check if in bounds
	if (this->mCellArray.isInArray(whereX, whereY))
	{
		// in bounds, update the point
		result = this->mCellArray.at(whereX, whereY).activeState;
	}

	return result;
}

// check activeState of a cell
// returns false if not found or out of bounds
bool BoolBoard::isCellState(const size_t& whereX, const size_t& whereY, const LifeState& whatState) const
{
	// Define Variables
	bool result = false;

	// check if in bounds
	if (this->mCellArray.isInArray(whereX, whereY))
	{
		// in bounds, update the point
		result = this->mCellArray.at(whereX, whereY).activeState == whatState;
	}

	return result;
}

// get float rectangle of dims of the board
const sf::FloatRect& BoolBoard::getGlobalBounds() const
{
	return this->mCellArrRect.getGlobalBounds();
}

// get size of board for bounds
sf::Vector2i BoolBoard::getSize() const
{
	return sf::Vector2i(mCellArray.size().x, mCellArray.size().y);
}

// check functions
// checks if a supplied point is within the index range of the board. If
//	it is, returns true, otherwise false
bool BoolBoard::indexInBoardRange(const int& whereX, const int& whereY) const
{
	return whereX >= 0 && whereY >= 0 && whereX < mCellArray.size().x && whereY < mCellArray.size().y;
}

// Tells if a pixel coordinate point is on the board
// precondition: any cursor inputs must be scaled to window locations
// returns true if in board, false otherwise
bool BoolBoard::pixelOnBoard(const int& whereX, const int& whereY) const
{
	// modify input coords by rectangle location
	sf::Vector2i relativeSize((whereX - mCellArrRect.getPosition().x) / this->mTileSize,
		(whereY - mCellArrRect.getPosition().y) / this->mTileSize);

	// check if pixel is greature than zero
	if (relativeSize.x >= 0 && relativeSize.y >= 0)
	{
		if (relativeSize.x < mCellArray.size().x && relativeSize.y < mCellArray.size().y)
		{
			// point is within range of the box
			return true;
		}
	}

	// otherwise
	return false;
}

bool BoolBoard::pixelOnBoard(const sf::Vector2f& pixelPoint) const
{
	return pixelOnBoard(pixelPoint.x, pixelPoint.y);
}


// --------------------------------------------------------------------------------------------- //
//								  PUBLIC   Member Functions
// --------------------------------------------------------------------------------------------- //
/* Function Name: Draw Bool Board Visual
* Description: renders the current activeState of the board to the supplied window
* Inputs: output render window
* Preconditions: render window must be open
* Outputs: draws visual to the window
* Returns: none
* Postconditions:
*/
void BoolBoard::draw(sf::RenderWindow& window) const
{
	// Draw shapes, background objects first
	if(this->mShowGrid == true){
		window.draw(this->mGridOverlayRect);
	}
	// then foreground
	window.draw(this->mCellArrRect);
}

/* mFunction Name: Refresh Object
* Description: refresh object texture.
* Inputs:
* Outputs:
*/
bool BoolBoard::refresh()
{
	// define variables
	bool result = false;

	// check if visual update is in order
	if (this->needsUpdate)
	{
		this->refreshBoardTexture();


		// indicate an update was made
		result = true;
		this->needsUpdate = false;
	}

	return result;
}

/* Function Name: Check Intersections
* Description: Virtual Intersection functions utalizing SFML syntax or functinoality.
*	Check an x,y coord as a floats.
* Inputs: X,Y point as floats
* Preconditions:
* Outputs: true if contains point, false otherwise
* Returns: true if contains point, false otherwise
* Postconditions:
*/
bool BoolBoard::contains(const float& x, const float& y)
{
	return this->mCellArrRect.getGlobalBounds().contains(x,y);
}

/* Function Name: Check Intersections
* Description: Virtual Intersection functions utalizing SFML syntax or functinoality.
*	Check an x,y coord as a vector2f
* Inputs: X,Y point as a vector
* Preconditions:
* Outputs: true if contains point, false otherwise
* Returns: true if contains point, false otherwise
* Postconditions:
*/
bool BoolBoard::contains(const sf::Vector2f& point)
{
	return this->mCellArrRect.getGlobalBounds().contains(point);

}

/* Function Name: Check Intersections
* Description: Virtual Intersection functions utalizing SFML syntax or functinoality.
*	Check an x,y coord from a rectangle shape.
* Inputs: rectangle shape
* Preconditions:
* Outputs: true if contains rectangle, false otherwise
* Returns: true if contains rectangle, false otherwise
* Postconditions:
*/
bool BoolBoard::contains(const sf::FloatRect& rectangle)
{
	return this->mCellArrRect.getGlobalBounds().intersects(rectangle);

}

/* mFunction Name: Update Cell State
* Description: Updates all cells to have their "nextState" as current activeState
* Inputs: none
* Outputs: none
*/
void BoolBoard::updateCellState()
{
	for (int index = 0; index < this->mCellArray.getLength(); index++)
	{
		mCellArray(index).activeState = mCellArray(index).nextState;
	}

	// set update flag
	this->needsUpdate = true;
}

/* mFunction Name: Set Background Grid Overlay
* Description: Toggle option to show background grid (ie, gridlines behind the
*	outputed render object
* Inputs: state of the grid, either on (true) or off (false)
* Outputs: none
*/
void BoolBoard::setGridOverlay(const bool& showGridState)
{
	// toggle on when currently off
	if (showGridState == true && mShowGrid == false)
	{
		// set show state to true
		this->mShowGrid = true;
		// refresh the grid shape
		refreshGridOverlay();
	}
	// toggle off if already on
	else if (showGridState == false && mShowGrid == true)
	{
		// set show state to false
		this->mShowGrid = false;
	}
}

/* mFunction Name: Save Current Board
* Description: Saves Current board to an output struct with any neccessary loading settings.
* Inputs: BoolBoardSaveState Struct to save data to
* Outputs: True if successful, false otherwise
*/
bool BoolBoard::saveCurState(BoolBoardSaveState& saveTo)
{
	// define variables
	bool result = false;
	
	// make sure the vector is long enough for the data
	saveTo.saveData.resize(this->mCellArray.getLength());

	// check that array is properly sized
	if(saveTo.saveData.size() == mCellArray.getLength())
	{
		// copy all data to save struct
		for (int index = 0; index < mCellArray.getLength(); index++)
		{
			saveTo.saveData.at(index) = this->mCellArray(index).activeState;
		}

		result = true;
	}
	else
	{
		std::cout << "failed to save; length required: " << mCellArray.getLength() << \
			", amount allocated: " << saveTo.saveData.size() << std::endl;
	}

	return result;
}

/* mFunction Name: Load states from
* Description: Sets all states (current and next) to the array from BoolBoardSaveState
* Inputs: SaveState Struct to load from
* Outputs: true if successful, false otherwise
*/
bool BoolBoard::loadCurState(const BoolBoardSaveState& loadFrom)
{
	// define variables
	bool result = false;

	// make sure structures are compatible
	if(loadFrom.saveData.size() == this->mCellArray.getLength())
	{
		// unload data from save struct
		for (int index = 0; index < loadFrom.saveData.size(); index++)
		{
			// set both states to save state data
			mCellArray(index).activeState = mCellArray(index).nextState = loadFrom.saveData.at(index);
		}

		// set update flag true to reprocess
		this->needsUpdate = true;

		// force refresh
		refresh();

		// data loaded, set return flag to true
		result = true;
	}
	else
	{
		std::cout << "failed to import; length of array: " << mCellArray.getLength() << \
			", struct length: " << loadFrom.saveData.size() << std::endl;

	}

	return result;
}

/* mFunction Name: Pixel to cell Index
* Description: Converts a screen pixel coordinate to an index value of the cell array
* Precondition: must have returned true for indexInBoard()
* Inputs: pixel to convert
* Outputs: index of the location of the pixel
*/
sf::Vector2i BoolBoard::pixelToCellIndex(const sf::Vector2f& pixelPoint) const
{
	// define variables
	sf::Vector2i result;

	// apply shape position offset
	// mod based upon size of each cell
	result.x = static_cast<int>((pixelPoint.x - this->mCellArrRect.getPosition().x) / this->mTileSize);
	result.y = static_cast<int>((pixelPoint.y - this->mCellArrRect.getPosition().y) / this->mTileSize);

	// display result for verification
	/*std::cout << "point (" << pixelPoint.x << ", " << pixelPoint.y << ") corresponds to index [" << \
		result.x << ", " << result.y << "]\n" << std::endl;*/

	return result;
}




// --------------------------------------------------------------------------------------------- //
//								  PRIVATE   Member Functions
// --------------------------------------------------------------------------------------------- //
/* mFunction Name:
* Description: refreshes the board by rendering it as a texture for a rectangleShape
* Inputs:
* Outputs:
*/
void BoolBoard::refreshBoardTexture()
{
	// define variables
	sf::RectangleShape aliveShape(sf::Vector2f(this->mTileSize, this->mTileSize));

	// set shape color for dead and alive shapes
	aliveShape.setFillColor(sf::Color::White);

	// clear the current texture file
	this->mRenderBuffer.clear(sf::Color::Transparent);

	// begin building shape
	for (unsigned indexY = 0; indexY < this->mCellArray.size().y; indexY++)
	{
		for (unsigned indexX = 0; indexX < this->mCellArray.size().x; indexX++)
		{
			// don't draw the LifeState::Dead

			// for any other case
			if (this->mCellArray.at(indexX, indexY).activeState == LifeState::ALIVE)
			{
				// update position
				aliveShape.setPosition(sf::Vector2f(indexX * this->mTileSize, indexY * this->mTileSize));

				// draw it
				this->mRenderBuffer.draw(aliveShape);
			}
		}
	}

	// complete the render
	this->mRenderBuffer.display();

	// generate texture to Board rectangle shape
	this->mCellArrTexture = this->mRenderBuffer.getTexture();
	this->mCellArrRect.setTexture(&this->mCellArrTexture);
}

/* mFunction Name: refresh Board Background Grid
* Description: refreshes the texture background of the
* Inputs: Colors for background and gridline colors
* Outputs: none
*/
void BoolBoard::refreshGridOverlay(const sf::Color& backgoundColor, const sf::Color& gridlineColor)
{
	// define variables
	float outlineDim = 1.0;
	sf::RectangleShape backgroundShape(sf::Vector2f(this->mTileSize, this->mTileSize));

	// setup the shape
	BP::addRectOutline(backgroundShape, outlineDim, gridlineColor);
	backgroundShape.setFillColor(sf::Color::Transparent);

	// refresh the buffer
	this->mRenderBuffer.clear(backgoundColor);

	// loop through the array and output to the buffer
	for (int y = 0; y < this->mCellArray.size().y; y++)
	{
		for (int x = 0; x < this->mCellArray.size().x; x++)
		{
			// move the shape
			backgroundShape.setPosition(sf::Vector2f(mTileSize * x + outlineDim, mTileSize * y + outlineDim));

			// paste to render buffer
			mRenderBuffer.draw(backgroundShape);
		}
	}
	// display draws
	mRenderBuffer.display();

	// update texture
	this->mGridOverlayTexture = mRenderBuffer.getTexture();

	// update shape's texture pointer
	this->mGridOverlayRect.setTexture(&mGridOverlayTexture);
}



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