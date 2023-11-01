/*****************************************************************************
**************
* Programmer: Conner Howard
* File:
* Date:
* Description: Boolean true/false board with RenderVisual Interface
******************************************************************************
*************/
#ifndef BOOL_BOARD_HPP
#define BOOL_BOARD_HPP

#include "MasterHeader.hpp"
#include "SFML/Graphics.hpp"
#include "Vector_Grid.hpp"
#include "Game-Engine/Interface Classes/vDrawableInterface.hpp"
#include "vIntersectionInterface.hpp"
#include "Cell.hpp"

struct BoolBoardSaveState{
	std::vector<LifeState> saveData;
};


class BoolBoard : public DrawableInterface, public IntersectionInterface
{
public:
	// --------------------------------------------------------------------------------------------- //
	//				Constructors, Default Constructors, Copy Constructors, Destructors
	// --------------------------------------------------------------------------------------------- //
	// default constructor
	BoolBoard(const size_t& sizeX, const size_t& sizeY, const unsigned& tileSize = 200);

	// destructor
	~BoolBoard();


	// --------------------------------------------------------------------------------------------- //
	//									Setters and Getters
	// --------------------------------------------------------------------------------------------- //
	// Setters
	// resize option for the grid
	void setSize(const size_t& sizeX, const size_t& sizeY);
	// set cell's active and next states to the provided state
	void overrideCellState(const size_t& whereX, const size_t& whereY, const LifeState& newState);
	// set cell activeState
	void setCellActiveState(const size_t& whereX, const size_t& whereY, const LifeState& newState);
	// set cell's next expressed activeState
	void setCellNextState(const size_t& whereX, const size_t& whereY, const LifeState& newState);
	// set Board Outline
	void setBoardOutline(const sf::Color& outlineColor, const float& size);

	// Getters
	// get LifeState of a cell
	// returns LifeState::DEAD by default
	LifeState getCellState(const size_t& whereX, const size_t& whereY) const;
	// check activeState of a cell
	// returns false if not found or out of bounds
	bool isCellState(const size_t& whereX, const size_t& whereY, const LifeState& whatState) const;
	// get float rectangle of dims of the board
	const sf::FloatRect& getGlobalBounds() const;
	// get size of board for bounds
	sf::Vector2i getSize() const;


	// check functions
	// checks if a supplied point is within the index range of the board. If
	//	it is, returns true, otherwise false
	bool indexInBoardRange(const int& whereX, const int& whereY) const;

	// Tells if a pixel coordinate point is on the board
	// precondition: any cursor inputs must be scaled to window locations
	// returns true if in board, false otherwise
	bool pixelOnBoard(const int& whereX, const int& whereY) const;
	bool pixelOnBoard(const sf::Vector2f& pixelPoint) const;


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
	virtual void draw(sf::RenderWindow& window) const;

	/* mFunction Name: Refresh Object
	* Description: refresh object texture.
	* Inputs:
	* Outputs:
	*/
	bool refresh();

	/* Function Name: Check Intersections
	* Description: Virtual Intersection functions utalizing SFML syntax or functinoality.
	*	Check an x,y coord as a floats.
	* Inputs: X,Y point as floats
	* Preconditions:
	* Outputs: true if contains point, false otherwise
	* Returns: true if contains point, false otherwise
	* Postconditions:
	*/
	bool contains(const float& x, const float& y);

	/* Function Name: Check Intersections
	* Description: Virtual Intersection functions utalizing SFML syntax or functinoality.
	*	Check an x,y coord as a vector2f
	* Inputs: X,Y point as a vector
	* Preconditions:
	* Outputs: true if contains point, false otherwise
	* Returns: true if contains point, false otherwise
	* Postconditions:
	*/
	bool contains(const sf::Vector2f& point);

	/* Function Name: Check Intersections
	* Description: Virtual Intersection functions utalizing SFML syntax or functinoality.
	*	Check an x,y coord from a rectangle shape.
	* Inputs: rectangle shape
	* Preconditions:
	* Outputs: true if contains rectangle, false otherwise
	* Returns: true if contains rectangle, false otherwise
	* Postconditions:
	*/
	bool contains(const sf::FloatRect& rectangle);

	/* mFunction Name: Update Cell State
	* Description: Updates all cells to have their "nextState" as current activeState
	* Inputs: none
	* Outputs: none
	*/
	void updateCellState();

	/* mFunction Name: Set Background Grid Overlay
	* Description: Toggle option to show background grid (ie, gridlines behind the 
	*	outputed render object
	* Inputs: state of the grid, either on (true) or off (false)
	* Outputs: none
	*/
	void setGridOverlay(const bool& showGridState = false);

	/* mFunction Name: Save Current Board
	* Description: Saves Current board to an output struct with any neccessary loading settings.
	* Inputs: BoolBoardSaveState Struct to save data to
	* Outputs: True if successful, false otherwise
	*/
	bool saveCurState(BoolBoardSaveState& saveTo);

	/* mFunction Name: Load states from
	* Description: Sets all states (current and next) to the array from BoolBoardSaveState
	* Inputs: SaveState Struct to load from
	* Outputs: true if successful, false otherwise
	*/
	bool loadCurState(const BoolBoardSaveState& loadFrom);

	/* mFunction Name: Pixel to cell Index
	* Description: Converts a screen pixel coordinate to an index value of the cell array
	* Precondition: must have returned true for indexInBoard()
	* Inputs: pixel to convert
	* Outputs: index of the location of the pixel
	*/
	sf::Vector2i pixelToCellIndex(const sf::Vector2f& pixelPoint) const;

private:
	Vector_Grid<Cell> mCellArray;
	bool needsUpdate;
	bool mShowGrid = false;
	unsigned mTileSize;	// size of tile in pixels
	sf::RenderTexture mRenderBuffer;	// temp renderTexture for generateing other textures
	sf::Texture mGridOverlayTexture;
	sf::RectangleShape mGridOverlayRect;
	sf::Texture	mCellArrTexture;				// texture to store output to mCellArrayRect
	sf::RectangleShape mCellArrRect;			// the renderable output of the state of the bool board


	// --------------------------------------------------------------------------------------------- //
	//								  PRIVATE   Member Functions
	// --------------------------------------------------------------------------------------------- //
	/* mFunction Name:
	* Description: refreshes the board by rendering it as a texture for a rectangleShape
	* Inputs:
	* Outputs:
	*/
	void refreshBoardTexture();

	/* mFunction Name: refresh Board Background Grid
	* Description: refreshes the texture background of the
	* Inputs: Colors for background and gridline colors
	* Outputs: none
	*/
	void refreshGridOverlay(const sf::Color& backgoundColor = sf::Color::Black,
		const sf::Color& gridlineColor = sf::Color(160, 160, 160));


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