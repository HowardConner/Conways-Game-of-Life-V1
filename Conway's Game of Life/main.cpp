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

const float movementAmount = 0.10;
const float zoomAmount = 20.0;

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
	sf::Vector2f screenDim(1280, 720);
	ProgramBindings bindings;
	bool pauseSim = true;
	int ticksPerSecond = 15;
	float secondsPerTick = 1.0 / ticksPerSecond;

	sf::Clock clock;
	float deltaTime = 0.0;
	sf::RenderWindow window(sf::VideoMode(screenDim.x, screenDim.y), appTitle);
	sf::RectangleShape shape(sf::Vector2f(100, 100));
	sf::Vector2f simStateScreenPercent(0.1, 0.1);
	sf::Image tempImage;


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
	BoolBoard world(64, 64, 50);
	ConwaySettings cwaySettings;

	//world.overrideCellState( 0, 0, LifeState::ALIVE);
	//world.overrideCellState( 1, 0, LifeState::ALIVE);
	//world.overrideCellState( 2, 0, LifeState::ALIVE);

	//world.overrideCellState(0, 1, LifeState::ALIVE);
	//world.overrideCellState(2, 1, LifeState::ALIVE);

	//world.overrideCellState( 0, 2, LifeState::ALIVE);
	//world.overrideCellState( 1, 2, LifeState::ALIVE);
	//world.overrideCellState( 2, 2, LifeState::ALIVE);

	//world.overrideCellState(10, 10, LifeState::ALIVE);
	//world.overrideCellState(10, 11, LifeState::ALIVE);
	//world.overrideCellState(11, 10, LifeState::ALIVE);
	//world.overrideCellState(11, 11, LifeState::ALIVE);

	//world.overrideCellState(16, 2, LifeState::ALIVE);
	//world.overrideCellState(16, 3, LifeState::ALIVE);
	//world.overrideCellState(16, 4, LifeState::ALIVE);

	//world.saveCurState(bbSave1);

	

	simStateOverlay.setSize(sf::Vector2f(200, 200));

	world.setBoardOutline(sf::Color::Cyan, 0.01 * window.getSize().y);
	world.setGridOverlay(true);


	simStateOverlay.snapTo(sf::Vector2f(0,720), Orientation::TopLeft);
	clock.restart();

	while (window.isOpen())
	{
		// make sure view is reset to camera view
		camera.updateView();

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
					camera.zoom(zoomAmount);
				}
				else if (event.key.code == bindings.zoomOut)
				{
					camera.zoom(-1 * zoomAmount);
				}
				else if (event.key.code == bindings.saveKey)
				{
					// save the current array for reloading
					world.saveCurState(bbSave1);
					std::cout << "save updated" << std::endl;
				}

			}
			// ===============================================
			//				Key Released Events
			// ===============================================
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::C)
				{
					camera.centerOn(world.getGlobalBounds(), 0.05);
					world.setBoardOutline(sf::Color::Cyan, 0.01 * window.getSize().y);
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
					// reload save state
					std::cout << "loading save 1" << std::endl;
					world.loadCurState(bbSave1);
				}
			}
			// ===============================================
			//				Mouse Click Events
			// ===============================================
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == bindings.dragButton && !camera.isDraggingActive())
				{
					camera.startDragEvent(window);
				}
				// Handle click to add/remove tile type
				// only activate if not dragging
				else if (!camera.isDraggingActive() && event.mouseButton.button == bindings.selectButton 
					&& world.pixelOnBoard(window.mapPixelToCoords( sf::Mouse::getPosition(window) )))
				{
					// get cell info
					sf::Vector2i targetCell = world.pixelToCellIndex(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

					switch (world.getCellState(targetCell.x, targetCell.y))
					{
					case LifeState::ALIVE:
						world.overrideCellState(targetCell.x, targetCell.y, LifeState::DEAD);
						break;
					case LifeState::DEAD:
						world.overrideCellState(targetCell.x, targetCell.y, LifeState::ALIVE);
						break;
					}
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				// release drag if correct button released
				if (event.key.code == event.mouseButton.button)
				{
					// unbind drag
					camera.finishDragEvent();
				}
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				// check if drag is active
				if (camera.isDraggingActive())
				{
					// it is, handle drag
					camera.handleDragEvent();
				}
			}
			else if (event.type == sf::Event::MouseWheelScrolled)
			{
				// check zoom in
				if (event.mouseWheelScroll.delta > 0)
				{
					camera.zoom(zoomAmount);
				}
				else if (event.mouseWheelScroll.delta < 0)
				{
					camera.zoom(-1 * zoomAmount);
				}
			}

		}


		// ===============================================
		//			Handle Instantaneous Inputs
		// ===============================================
		if (sf::Keyboard::isKeyPressed(bindings.moveUp))
		{
			camera.move(CamDirection::UP, movementAmount);
		}
		if (sf::Keyboard::isKeyPressed(bindings.moveDown))
		{
			camera.move(CamDirection::DOWN, movementAmount);
		}
		if (sf::Keyboard::isKeyPressed(bindings.moveLeft))
		{
			camera.move(CamDirection::LEFT, movementAmount);
		}
		if (sf::Keyboard::isKeyPressed(bindings.moveRight))
		{
			camera.move(CamDirection::RIGHT, movementAmount);
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
				CGOL::solveConwayStep(world, cwaySettings);
				//cout << "step processed" << endl;
			}

			// reset the clock
			clock.restart();
		}





		// ===============================================
		//		  Refresh Block
		// ===============================================
		window.clear();


		world.refresh();




		


		// ===============================================
		//				Camera/Dynamic Graphics
		// ===============================================
		camera.updateView();
		//window.draw(shape);
		world.draw(window);
		


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
