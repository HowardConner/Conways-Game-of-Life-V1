/*****************************************************************************
**************
* Programmer: Conner Howard
* File: 
* Date: 
* Description:
******************************************************************************
*************/

#include "MasterHeader.hpp"
#include "CameraController.hpp"
#include "BoolBoard.hpp"
#include "ConwaySolver.hpp"
#include "RectDisplay.hpp"
#include "TickClock.hpp"
#include "Game-Engine/Component Classes/Object_Flags.hpp"

#include "Game-Engine/Renderer/RenderEngine.hpp"

const float movementAmount = 0.10;
const float zoomAmount = 20.0;

enum class InputEvent
{
	CloseProgram	= 1 << 0, 
	MoveUp			= 1 << 1,
	MoveDown		= 1 << 2,
	MoveLeft		= 1 << 3,
	MoveRight		= 1 << 4,
	ZoomIn			= 1 << 5,
	ZoomOut			= 1 << 6,
	CenterOn		= 1 << 7,
	DragStarted		= 1 << 8,
	DragEnded		= 1 << 9,
	LoadSaveData	= 1 << 10,
	CursorMovement	= 1 << 11,
	RMBClick		= 1 << 12,
	LMBClick		= 1 << 13,
	PauseSim		= 1 << 14,
	RunSimulation	= 1 << 15,
	ClearBoard		= 1 << 16,
	SaveData		= 1 << 17,
	//Flag19= 1 << 18,
	//Flag20= 1 << 19,
	//Flag21= 1 << 20,
	//Flag22= 1 << 21,
	//Flag23= 1 << 22,
	//Flag24= 1 << 23,
	//Flag25= 1 << 24,
	//Flag26= 1 << 25,
	//Flag27= 1 << 26,
	//Flag28= 1 << 27,
	//Flag29= 1 << 28,
	//Flag30= 1 << 29,
	//Flag31= 1 << 30,
	//Flag32= 1 << 31,
	INPUT_COUNT			//the amount of flags active in the Enum list
};

struct ProgramBindings {
	sf::Keyboard::Key moveUp = sf::Keyboard::W;
	sf::Keyboard::Key moveDown = sf::Keyboard::S;
	sf::Keyboard::Key moveLeft = sf::Keyboard::A;
	sf::Keyboard::Key moveRight = sf::Keyboard::D;
	sf::Keyboard::Key saveKey = sf::Keyboard::Num1;
	sf::Keyboard::Key centerKey = sf::Keyboard::C;
	sf::Keyboard::Key toggleSimKey = sf::Keyboard::Space;
	sf::Keyboard::Key reloadKey = sf::Keyboard::R;

	sf::Keyboard::Key zoomIn = sf::Keyboard::PageUp;
	sf::Keyboard::Key zoomOut = sf::Keyboard::PageDown;

	// drag funcitonality
	sf::Mouse::Button dragButton = sf::Mouse::Button::Right;
	sf::Mouse::Button selectButton = sf::Mouse::Button::Left;
};

/* mFunction Name: Check Event Queue Input
* Description: Assesses the state of the event queue and unqueues all event inputs.
* Upgrade Ideas: create generic pass through for non-flag input signals to be processed from
* Inputs: window to poll from, masterFlag list to be outputed to
* Outputs: masterFlag list to be outputed to
*/
void checkEventQueueInputs(sf::RenderWindow& window, Flag_32<InputEvent>& masterFlag, bool runSim, const ProgramBindings& bindings, 
	const CameraController& activeCamera);

/* mFunction Name: Direct Input Flag Checker
* Description: Sets flags in the MasterFlag list based upon direct input, that is,
*	it does not use the event queue but polls the keys/mouse/joystick directly
* Inputs: window to reference, masterFlag list to be outputed to
* Outputs: masterFlag list to be outputed to
*/
void checkDirectInputs(sf::RenderWindow& window, Flag_32<InputEvent>& masterFlag, const ProgramBindings& bindings, 
	const CameraController& activeCamera);

int main()
{
	// Define Variables
	string appTitle = "Conway's Game of Life";

	// define program characteristics
	sf::ContextSettings winContextSettings(0U, 0U, 0U);
	sf::Vector2f screenDim(1280, 720);
	ProgramBindings bindings;
	bool runSim = false;
	unsigned ticksPerSecond = 10;
	TickClock globalTickTimer(ticksPerSecond);

	// define program resources
	sf::Clock clock;
	float deltaTime = 0.0;
	sf::RenderWindow window(sf::VideoMode(screenDim.x, screenDim.y), appTitle, 7U, winContextSettings);
	sf::RectangleShape shape(sf::Vector2f(100, 100));
	sf::Vector2f simStateScreenPercent(0.1, 0.1);
	sf::Image tempImage;
	Flag_32<InputEvent> ProgramEvent;
	sf::Vector2i mousePos;

	sf::Texture simActiveTexture;
	tempImage.create(200, 200, sf::Color::Green);
	if (!simActiveTexture.loadFromImage(tempImage))
	{
		std::cout << "Failed to create [simActiveTexture] texture" << std::endl;
	}

	sf::Texture simPausedTexture;
	tempImage.create(200, 200, sf::Color::Red);
	if(!simPausedTexture.loadFromImage(tempImage))
	{
		std::cout << "Failed to create [simaPausedTexture] texture" << std::endl;
	}

	RectDisplay simStateOverlay(sf::Vector2f(20,10));

	BoolBoardSaveState bbSaveNull;
	BoolBoardSaveState bbSave1;

	CameraController camera(window, 0.025);
	CameraController hud(window, 0.000025);
	BoolBoard lifeBoard(32, 16, 50);
	ConwaySettings cwaySettings;

	lifeBoard.saveCurState(bbSaveNull);
	
	lifeBoard.setBoardOutline(sf::Color::Cyan, 0.01 * window.getSize().y);
	lifeBoard.setGridOverlay(true);


	//simStateOverlay.snapTo(sf::Vector2f(0,720), Orientation::BottomLeft);
	simStateOverlay.setSize(sf::Vector2f(100, 50));
	simStateOverlay.snapTo(hud.getCamRectangle(), Orientation::TopRight);
	simStateOverlay.setTexture(&simPausedTexture);

	camera.centerOn(lifeBoard.getGlobalBounds(), 0.05);

	clock.restart();

	
	while (window.isOpen())
	{
		// make sure view is reset to camera view
		camera.updateView();

		// make sure flags are unset
		

		// get mouse position
		mousePos = sf::Mouse::getPosition(window);

		// ===============================================
		//				Key Pressed events
		// ===============================================
		checkEventQueueInputs(window, ProgramEvent, runSim, bindings, camera);


		// ===============================================
		//			Handle Instantaneous Inputs
		// ===============================================
		checkDirectInputs(window, ProgramEvent, bindings, camera);



		// ==============================================================================================
		//										Process Event Flags
		// ==============================================================================================
		// only process if an event was recorded
		if(!ProgramEvent.allFlagsFalse())
		{
			if (ProgramEvent.HasFlag(InputEvent::MoveUp))
			{
				// Move Main Camera Upwards
				camera.move(CamDirection::UP, movementAmount);
			}
			if (ProgramEvent.HasFlag(InputEvent::MoveDown))
			{
				// Move Main Camera Downwards
				camera.move(CamDirection::DOWN, movementAmount);
			}
			if (ProgramEvent.HasFlag(InputEvent::MoveLeft))
			{
				// Move Main Camera Left
				camera.move(CamDirection::LEFT, movementAmount);
			}
			if (ProgramEvent.HasFlag(InputEvent::MoveRight))
			{
				// Move Main Camera Right 
				camera.move(CamDirection::RIGHT, movementAmount);
			}
			if (ProgramEvent.HasFlag(InputEvent::ZoomIn))
			{
				// scroll up, zoom out
				camera.zoom(zoomAmount);
			}
			else if (ProgramEvent.HasFlag(InputEvent::ZoomOut))
			{
				// scroll down, zoom in
				camera.zoom(-1 * zoomAmount);
			}

			if (ProgramEvent.HasFlag(InputEvent::SaveData))
			{
				// save the current array for reloading
				lifeBoard.saveCurState(bbSave1);
				std::cout << "save updated" << std::endl;
			}
			else if (ProgramEvent.HasFlag(InputEvent::ClearBoard))
			{
				// load null data plot
				std::cout << "Wiping Board Clear" << std::endl;
				lifeBoard.loadCurState(bbSaveNull);
			}
			else if (ProgramEvent.HasFlag(InputEvent::LoadSaveData))
			{
				// reload save state
				std::cout << "loading save 1" << std::endl;
				lifeBoard.loadCurState(bbSave1);
			}

			if (ProgramEvent.HasFlag(InputEvent::CenterOn))
			{
				// center on board
				camera.centerOn(lifeBoard.getGlobalBounds(), 0.05);
				lifeBoard.setBoardOutline(sf::Color::Cyan, 0.01 * window.getSize().y);
			}
			// check if mouseclick should flip the cell's state, but only if click + not currently dragging + cursor is on the board
			if (ProgramEvent.HasFlag(InputEvent::LMBClick) && !camera.isDraggingActive()
				&& lifeBoard.pixelOnBoard(window.mapPixelToCoords(mousePos)))//sf::Mouse::getPosition(window)
			{
				// click happens and the drag is not active, thus flip cell state
				// get cell info
				sf::Vector2i targetCell = lifeBoard.pixelToCellIndex(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

				switch (lifeBoard.getCellState(targetCell.x, targetCell.y))
				{
				case LifeState::ALIVE:
					lifeBoard.overrideCellState(targetCell.x, targetCell.y, LifeState::DEAD);
					break;
				case LifeState::DEAD:
					lifeBoard.overrideCellState(targetCell.x, targetCell.y, LifeState::ALIVE);
					break;
				}
			}
			// drag events
			if (ProgramEvent.HasFlag(InputEvent::DragStarted) && !camera.isDraggingActive())
			{
				camera.startDragEvent(window);
			}
			else if (ProgramEvent.HasFlag(InputEvent::DragEnded) && camera.isDraggingActive())
			{
				camera.finishDragEvent();
			}
			else if (ProgramEvent.HasFlag(InputEvent::CursorMovement) && camera.isDraggingActive())
			{
				camera.handleDragEvent();
			}

			// process pause/play sim
			if (ProgramEvent.HasFlag(InputEvent::RunSimulation))
			{
				// sim is paused, reengage it
				runSim = true;
				simStateOverlay.setTexture(&simActiveTexture);
				// reset the clock
				clock.restart();
			}
			else if (ProgramEvent.HasFlag(InputEvent::PauseSim))
			{
				// sim active, pause it
				runSim = false;
				simStateOverlay.setTexture(&simPausedTexture);
			}
		}


		// ===============================================
		//			Tick Event Block
		// ===============================================
		// check for tick clock update and process as long as there is one
		while (globalTickTimer.update())
		{
			// a tick pulse has been activated, thus, begin processing events
			if (runSim == true)
			{
				//				TICK BLOCK
				// =======================================
				CGOL::solveConwayStep(lifeBoard, cwaySettings);
				//cout << "step processed" << endl;
			}




		}



		// ===============================================
		//		  Refresh Block
		// ===============================================
		window.clear();

		lifeBoard.refresh();



		// ===============================================
		//				Camera/Dynamic Graphics
		// ===============================================
		camera.updateView();
		//window.draw(shape);
		lifeBoard.draw(window);



		// ===============================================
		//				Static Hud Graphics
		// ===============================================
		hud.updateView();
		//overlay drawings
		simStateOverlay.draw(window);



		window.display();
	}

	return 0;
}


/* mFunction Name: Check Event Queue Input
* Description: Assesses the state of the event queue and unqueues all event inputs.
* Upgrade Ideas: create generic pass through for non-flag input signals to be processed from
* Inputs: window to poll from, masterFlag list to be outputed to
* Outputs: masterFlag list to be outputed to
*/
void checkEventQueueInputs(sf::RenderWindow& window, Flag_32<InputEvent>& masterFlag, bool runSim, const ProgramBindings& bindings,
	const CameraController& activeCamera)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			// ===============================================
			//				Window Close event
			// ===============================================
		case sf::Event::Closed:
			window.close();
			break;
			// ===============================================
			//				Key Pressed events
			// ===============================================
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			else if (event.key.code == bindings.zoomIn)
			{
				masterFlag.SetFlag(InputEvent::ZoomIn);
			}
			else if (event.key.code == bindings.zoomOut)
			{
				masterFlag.SetFlag(InputEvent::ZoomOut);
			}
			else if (event.key.code == bindings.saveKey)
			{
				masterFlag.SetFlag(InputEvent::SaveData);
			}
			else if (event.key.code == sf::Keyboard::Key::Num0)
			{
				masterFlag.SetFlag(InputEvent::ClearBoard);
			}
			else if (event.key.code == bindings.reloadKey)
			{
				masterFlag.SetFlag(InputEvent::LoadSaveData);
			}
			break;
			// ===============================================
			//				Key Released Events
			// ===============================================
		case sf::Event::KeyReleased:
			if (event.key.code == bindings.centerKey)
			{
				masterFlag.SetFlag(InputEvent::CenterOn);
			}
			else if (event.key.code == bindings.toggleSimKey && runSim == false)
			{
				masterFlag.SetFlag(InputEvent::RunSimulation);
			}
			else if (event.key.code == bindings.toggleSimKey && runSim == true)
			{
				masterFlag.SetFlag(InputEvent::PauseSim);
			}
			break;
			// ===============================================
			//			Mouse Button Pressed Events
			// ===============================================
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == bindings.dragButton)
			{
				masterFlag.SetFlag(InputEvent::DragStarted);
			}
			else if (event.mouseButton.button == bindings.selectButton)
			{
				masterFlag.SetFlag(InputEvent::LMBClick);
			}
			break;
			// ===============================================
			//			Mouse Buttone Released Events
			// ===============================================
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == bindings.dragButton)
			{
				masterFlag.SetFlag(InputEvent::DragEnded);
			}
			break;
			// ===============================================
			//				Moused Move Events
			// ===============================================
		case sf::Event::MouseMoved:
			if (activeCamera.isDraggingActive())
			{
				masterFlag.SetFlag(InputEvent::CursorMovement);
			}
			break;
			// ===============================================
			//			Mouse Wheel Scrolled Events
			// ===============================================
		case sf::Event::MouseWheelScrolled:
			if (!activeCamera.isDraggingActive() && event.mouseWheelScroll.delta > 0)
			{
				masterFlag.SetFlag(InputEvent::ZoomIn);
			}
			else if (!activeCamera.isDraggingActive() && event.mouseWheelScroll.delta < 0)
			{
				masterFlag.SetFlag(InputEvent::ZoomOut);
			}
			break;
			//default:
			//	break;
		}

	}
}

/* mFunction Name: Direct Input Flag Checker
* Description: Sets flags in the MasterFlag list based upon direct input, that is,
*	it does not use the event queue but polls the keys/mouse/joystick directly
* Inputs: window to reference, masterFlag list to be outputed to
* Outputs: masterFlag list to be outputed to
*/
void checkDirectInputs(sf::RenderWindow& window, Flag_32<InputEvent>& masterFlag, const ProgramBindings& bindings,
	const CameraController& activeCamera)
{
	if (sf::Keyboard::isKeyPressed(bindings.moveUp))
	{
		masterFlag.SetFlag(InputEvent::MoveUp);
	}
	if (sf::Keyboard::isKeyPressed(bindings.moveDown))
	{
		masterFlag.SetFlag(InputEvent::MoveDown);
	}
	if (sf::Keyboard::isKeyPressed(bindings.moveLeft))
	{
		masterFlag.SetFlag(InputEvent::MoveLeft);
	}
	if (sf::Keyboard::isKeyPressed(bindings.moveRight))
	{
		masterFlag.SetFlag(InputEvent::MoveRight);
	}
}