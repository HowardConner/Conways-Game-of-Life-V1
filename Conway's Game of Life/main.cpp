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
#include "Game-Engine/Component Classes/Object_Flags.hpp"

const float movementAmount = 0.10;
const float zoomAmount = 20.0;

enum class InputEvent
{
	MoveUp			= 1 << 0,
	MoveDown		= 1 << 1,
	MoveLeft		= 1 << 2,
	MoveRight		= 1 << 3,
	ZoomIn			= 1 << 4,
	ZoomOut			= 1 << 5,
	CenterOn		= 1 << 6,
	DragStarted		= 1 << 7,
	DragActive		= 1 << 8,		// likely redunduant by using "CursorMovment"
	DragEnded		= 1 << 9,
	SaveData		= 1 << 10,
	LoadSaveData	= 1 << 11,
	CursorMovement	= 1 << 12,
	RMBClick		= 1 << 13,
	LMBClick		= 1 << 14,
	//Flag16= 1 << 15,
	//Flag17= 1 << 16,
	//Flag18= 1 << 17,
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
};

struct ProgramBindings {
	sf::Keyboard::Key moveUp = sf::Keyboard::W;
	sf::Keyboard::Key moveDown = sf::Keyboard::S;
	sf::Keyboard::Key moveLeft = sf::Keyboard::A;
	sf::Keyboard::Key moveRight = sf::Keyboard::D;
	sf::Keyboard::Key saveKey = sf::Keyboard::Num1;

	sf::Keyboard::Key zoomIn = sf::Keyboard::PageUp;
	sf::Keyboard::Key zoomOut = sf::Keyboard::PageDown;

	// drag funcitonality
	sf::Mouse::Button dragButton = sf::Mouse::Button::Middle;
	sf::Mouse::Button selectButton = sf::Mouse::Button::Left;
};

int main()
{
	// Define Variables
	string appTitle = "Conway's Game of Life";

	// define program characteristics
	sf::Vector2f screenDim(1280, 720);
	ProgramBindings bindings;
	bool pauseSim = true;
	int ticksPerSecond = 15;
	float secondsPerTick = 1.0 / ticksPerSecond;

	// define program resources
	sf::Clock clock;
	float deltaTime = 0.0;
	sf::RenderWindow window(sf::VideoMode(screenDim.x, screenDim.y), appTitle);
	sf::RectangleShape shape(sf::Vector2f(100, 100));
	sf::Vector2f simStateScreenPercent(0.1, 0.1);
	sf::Image tempImage;
	Flag_32<InputEvent> ProgramEvent;

	sf::Texture simActiveTexture;
	tempImage.create(200, 200, sf::Color::Green);
	simActiveTexture.loadFromImage(tempImage);

	sf::Texture simPausedTexture;
	tempImage.create(200, 200, sf::Color::Red);
	simActiveTexture.loadFromImage(tempImage);

	RectDisplay simStateOverlay;
	simStateOverlay.setTexture(&simActiveTexture);

	BoolBoardSaveState bbSave1;

	CameraController camera(window, 0.025);
	CameraController hud(window, 0.025);
	BoolBoard lifeBoard(64, 64, 50);
	ConwaySettings cwaySettings;

	//lifeBoard.overrideCellState( 0, 0, LifeState::ALIVE);
	//lifeBoard.overrideCellState( 1, 0, LifeState::ALIVE);
	//lifeBoard.overrideCellState( 2, 0, LifeState::ALIVE);

	//lifeBoard.overrideCellState(0, 1, LifeState::ALIVE);
	//lifeBoard.overrideCellState(2, 1, LifeState::ALIVE);

	//lifeBoard.overrideCellState( 0, 2, LifeState::ALIVE);
	//lifeBoard.overrideCellState( 1, 2, LifeState::ALIVE);
	//lifeBoard.overrideCellState( 2, 2, LifeState::ALIVE);

	//lifeBoard.overrideCellState(10, 10, LifeState::ALIVE);
	//lifeBoard.overrideCellState(10, 11, LifeState::ALIVE);
	//lifeBoard.overrideCellState(11, 10, LifeState::ALIVE);
	//lifeBoard.overrideCellState(11, 11, LifeState::ALIVE);

	//lifeBoard.overrideCellState(16, 2, LifeState::ALIVE);
	//lifeBoard.overrideCellState(16, 3, LifeState::ALIVE);
	//lifeBoard.overrideCellState(16, 4, LifeState::ALIVE);

	//lifeBoard.saveCurState(bbSave1);

	

	simStateOverlay.setSize(sf::Vector2f(200, 200));

	lifeBoard.setBoardOutline(sf::Color::Cyan, 0.01 * window.getSize().y);
	lifeBoard.setGridOverlay(true);


	simStateOverlay.snapTo(sf::Vector2f(0,720), Orientation::TopLeft);
	clock.restart();

	while (window.isOpen())
	{
		// make sure view is reset to camera view
		camera.updateView();

		// make sure flags are unset
		ProgramEvent.SetAllFlagsFalse();

		sf::Event event;
		while (window.pollEvent(event))
		{
			// Handle Prgram close
			if (event.type == sf::Event::Closed )
				window.close();

			// ===============================================
			//				Key Pressed events
			// ===============================================
			if (event.type == sf::Event::KeyPressed)
			{
				// handle program close
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				else if (event.key.code == bindings.zoomIn)
				{
					ProgramEvent.SetFlag(InputEvent::ZoomIn);
				}
				else if (event.key.code == bindings.zoomOut)
				{
					ProgramEvent.SetFlag(InputEvent::ZoomOut);
				}
				else if (event.key.code == bindings.saveKey)
				{
					ProgramEvent.SetFlag(InputEvent::SaveData);
				}

			}
			// ===============================================
			//				Key Released Events
			// ===============================================
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::C)
				{
					ProgramEvent.SetFlag(InputEvent::CenterOn);
				}
				else if (event.key.code == sf::Keyboard::Space)
				{
					if (pauseSim == false)
					{
						// sim active, pause it
						pauseSim = true;
						simStateOverlay.setTexture(&simPausedTexture);
					}
					else
					{
						// sim is paused, reengage it
						pauseSim = false;
						simStateOverlay.setTexture(&simActiveTexture);
						deltaTime = secondsPerTick;
						// reset the clock
						clock.restart();
					}
				}
				else if (event.key.code == sf::Keyboard::R)
				{
					ProgramEvent.SetFlag(InputEvent::LoadSaveData);
				}
			}
			// ===============================================
			//				Mouse Click Events
			// ===============================================
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == bindings.dragButton)
				{
					ProgramEvent.SetFlag(InputEvent::DragStarted);
				}
				// Handle click to add/remove tile type
				// only activate if not dragging
				else if (event.mouseButton.button == bindings.selectButton)
				{
					ProgramEvent.SetFlag(InputEvent::LMBClick);
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				// release drag if correct button released
				if (event.key.code == event.mouseButton.button)
				{
					// unbind drag
					ProgramEvent.SetFlag(InputEvent::DragEnded);
				}
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				// check if drag is active
				ProgramEvent.SetFlag(InputEvent::CursorMovement);
			}
			else if (event.type == sf::Event::MouseWheelScrolled)
			{
				// check zoom in
				if (event.mouseWheelScroll.delta > 0)
				{
					
				}
				else if (event.mouseWheelScroll.delta < 0)
				{
					
				}
			}

		}


		// ===============================================
		//			Handle Instantaneous Inputs
		// ===============================================
		if (sf::Keyboard::isKeyPressed(bindings.moveUp))
		{
			ProgramEvent.SetFlag(InputEvent::MoveUp);
		}
		if (sf::Keyboard::isKeyPressed(bindings.moveDown))
		{
			ProgramEvent.SetFlag(InputEvent::MoveDown);
		}
		if (sf::Keyboard::isKeyPressed(bindings.moveLeft))
		{
			ProgramEvent.SetFlag(InputEvent::MoveLeft);
		}
		if (sf::Keyboard::isKeyPressed(bindings.moveRight))
		{
			ProgramEvent.SetFlag(InputEvent::MoveRight);
		}




		// ==============================================================================================
		//										Process Event Flags
		// ==============================================================================================
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
		if (ProgramEvent.HasFlag(InputEvent::ZoomOut))
		{
			// scroll down, zoom in
			camera.zoom( -1 * zoomAmount);
		}
		if (ProgramEvent.HasFlag(InputEvent::SaveData))
		{
			// save the current array for reloading
			lifeBoard.saveCurState(bbSave1);
			std::cout << "save updated" << std::endl;
		}
		if (ProgramEvent.HasFlag(InputEvent::LoadSaveData))
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
		if (ProgramEvent.HasMultiFlag(InputEvent::LMBClick) && !camera.isDraggingActive() 
			&& lifeBoard.pixelOnBoard(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
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



		// ===============================================
		//			Tick Event Block
		// ===============================================
		if (pauseSim != true)
		{
			deltaTime += clock.getElapsedTime().asSeconds();

			if (deltaTime >= secondsPerTick)
			{
				// "reset" delta time
				deltaTime = deltaTime - secondsPerTick;

				//				TICK BLOCK
				// =======================================
				CGOL::solveConwayStep(lifeBoard, cwaySettings);
				//cout << "step processed" << endl;
			}

			// reset the clock
			clock.restart();
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
