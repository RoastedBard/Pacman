#include "Client.h"
#include "Core\Enums.h"
#include <iostream>
#include <fstream>
#include <istream>

Client::Client(void)
{
	_fps = sf::seconds(1.f / 60.f);

	_mazeSize = 0;

	_cellPixelSize	 = 30;
	_pillPixelSize	 = 10;
	_pacmanPixelSize = 26;

	_wallTexture.loadFromFile("media/brick.png");

	_pillTexture.loadFromFile("media/pill.png");

	_pillOnTheFloorTexture.loadFromFile("media/pillOnTheFloor.png");

	_nothingTexture.loadFromFile("media/floor.png");

	_pacmanTexture.loadFromFile("media/pacman.png");

	_ghostTexture.loadFromFile("media/ghost.png");
}


Client::~Client(void)
{
}

void Client::readData(InitDataFromServer data)
{
	_mazeSize = data.mazeSize;

	_abstractMaze.resize(_mazeSize);
	for(int i = 0; i < _mazeSize; i++)
		_abstractMaze[i].resize(_mazeSize);

	for(int i = 0; i < _mazeSize; i++)
	{
		for(int j = 0; j < _mazeSize; j++)
		{
			_abstractMaze[i][j] = data.mazeCellIds[i][j];
		}
	}

	_pacmanStartPoint.x = data.pacmanStartPoint.x;
	_pacmanStartPoint.y = data.pacmanStartPoint.y;

	for(int i = 0; i < data.ghostPositions.size(); i++)
	{
		_ghostsStartPoint.push_back(data.ghostPositions[i]);
	}
}

void Client::readData(CommonDataFromServer data)
{
	_cellToRedraw[0] = data.cellToRedraw[0];
	_cellToRedraw[1] = data.cellToRedraw[1];
	_cellToRedraw[2] = data.cellToRedraw[2];

	_pacmanMovingVector.x = data.pacmanMovingVector.x;
	_pacmanMovingVector.y = data.pacmanMovingVector.y;

	_ghostsMovingVectors.clear();
	for(int i = 0; i < data.ghostsMovingVectors.size(); i++)
	{
		_ghostsMovingVectors.push_back(data.ghostsMovingVectors[i]);
	}
}

void Client::sendData(InitDataFromClient &data)
{
	data.pacmanBoundingBox.setBoundingBox(_pacmanSprite.getGlobalBounds().left,  _pacmanSprite.getGlobalBounds().top,
										  _pacmanSprite.getGlobalBounds().left + _pacmanSprite.getLocalBounds().width,
										  _pacmanSprite.getGlobalBounds().top +  _pacmanSprite.getLocalBounds().height);

	data.cellBoundingBoxes.resize(_mazeSize);
	for(int i = 0; i < _mazeSize; i++)
		data.cellBoundingBoxes[i].resize(_mazeSize);

	for(int i = 0; i < _mazeSize; i++)
	{
		int actualX = i * _cellPixelSize;

		for(int j = 0; j < _mazeSize; j++)
		{
			int actualY = j * _cellPixelSize;

			switch(_abstractMaze[i][j])
			{
				case 0:
					data.cellBoundingBoxes[i][j].setBoundingBox(actualX,  actualY,
																actualX + _cellPixelSize, 
																actualY + _cellPixelSize);

					break;

				case 1:
					data.cellBoundingBoxes[i][j].setBoundingBox(actualX + ((_cellPixelSize - _pillPixelSize) / 2),  
																actualY + ((_cellPixelSize - _pillPixelSize) / 2),
																actualX + ((_cellPixelSize - _pillPixelSize) / 2) + _pillPixelSize, 
																actualY + ((_cellPixelSize - _pillPixelSize) / 2) + _pillPixelSize);

					break;
			}
		}
	}

	data.ghostsBoundingBoxes.resize(_ghostSprites.size());

	for(int i = 0; i < _ghostSprites.size(); i++)
	{
		data.ghostsBoundingBoxes[i].setBoundingBox(_ghostSprites[i].getGlobalBounds().left / _cellPixelSize, _ghostSprites[i].getGlobalBounds().top / _cellPixelSize,
												  (_ghostSprites[i].getGlobalBounds().left + _ghostSprites[i].getLocalBounds().width)/ _cellPixelSize,
												  (_ghostSprites[i].getGlobalBounds().top + _ghostSprites[i].getLocalBounds().height)/ _cellPixelSize);
	}
}

void Client::sendData(CommonDataFromClient &data)
{
	data.keyPressed = _keyPressed;
	data.pacmanBoundingBox.setBoundingBox(_pacmanSprite.getGlobalBounds().left,  _pacmanSprite.getGlobalBounds().top,
										  _pacmanSprite.getGlobalBounds().left + _pacmanSprite.getLocalBounds().width,
										  _pacmanSprite.getGlobalBounds().top +  _pacmanSprite.getLocalBounds().height);

	data.pacmanPosition.setXY(_pacmanSprite.getPosition().x / _cellPixelSize, _pacmanSprite.getPosition().y / _cellPixelSize);

	data.ghostsBoundingBoxes.resize(_ghostSprites.size());

	for(int i = 0; i < _ghostSprites.size(); i++)
	{
		data.ghostsBoundingBoxes[i].setBoundingBox(_ghostSprites[i].getGlobalBounds().left / _cellPixelSize, _ghostSprites[i].getGlobalBounds().top / _cellPixelSize,
												  (_ghostSprites[i].getGlobalBounds().left + _ghostSprites[i].getLocalBounds().width)/ _cellPixelSize,
												  (_ghostSprites[i].getGlobalBounds().top + _ghostSprites[i].getLocalBounds().height)/ _cellPixelSize);
	}
}

void Client::createWindow()
{
	_screenHeight = _mazeSize * _cellPixelSize;
	_screenWidth  = _mazeSize * _cellPixelSize;

	_window.create(sf::VideoMode(_screenWidth, _screenHeight), "Pacman 0.0.1");
}

void Client::initialize()
{
	_levelSprites.resize(_mazeSize);
	for(int i = 0; i < _mazeSize; i++)
		_levelSprites[i].resize(_mazeSize);

	for(int i = 0; i < _mazeSize; i++)
	{
		int actualX = i * _cellPixelSize;

		for(int j = 0; j < _mazeSize; j++)
		{
			int actualY = j * _cellPixelSize;

			switch(_abstractMaze[i][j])
			{
				case 0:
					_levelSprites[i][j].setTexture(_wallTexture);
					_levelSprites[i][j].setPosition(actualX, actualY);
					_levelSprites[i][j].setScale(_cellPixelSize / _levelSprites[i][j].getLocalBounds().width, _cellPixelSize / _levelSprites[i][j].getLocalBounds().height);

					break;

				case 1:
					_levelSprites[i][j].setTexture(_pillOnTheFloorTexture);
					_levelSprites[i][j].setPosition(actualX, actualY);
					_levelSprites[i][j].setScale(_cellPixelSize / _levelSprites[i][j].getLocalBounds().width, _cellPixelSize / _levelSprites[i][j].getLocalBounds().height);
					

					break;

				//for testing only
				case 2:
					_levelSprites[i][j].setTexture(_nothingTexture);
					_levelSprites[i][j].setPosition(actualX, actualY);
					_levelSprites[i][j].setScale(_cellPixelSize / _levelSprites[i][j].getLocalBounds().width, _cellPixelSize / _levelSprites[i][j].getLocalBounds().height);
					break;
			}
		}
	}

	_ghostSprites.resize(_ghostsStartPoint.size());

	for(int i = 0; i < _ghostSprites.size(); i++)
	{
		_ghostSprites[i].setTexture(_ghostTexture);
		_ghostSprites[i].setPosition(_ghostsStartPoint[i].x * _cellPixelSize, _ghostsStartPoint[i].y * _cellPixelSize);
		//_ghostSprites[i].setOrigin(_ghostSprites[i].getLocalBounds().width / 2, _ghostSprites[i].getLocalBounds().height / 2);
	}

	_pacmanSprite.setTexture(_pacmanTexture);
	_pacmanSprite.setPosition(_pacmanStartPoint.x * _cellPixelSize + _cellPixelSize/2, _pacmanStartPoint.y * _cellPixelSize + _cellPixelSize/2);
	_pacmanSprite.setScale(_pacmanPixelSize / _pacmanSprite.getLocalBounds().width, _pacmanPixelSize / _pacmanSprite.getLocalBounds().height);
	_pacmanSprite.setOrigin(_pacmanSprite.getLocalBounds().width / 2, _pacmanSprite.getLocalBounds().height / 2);

	_ghostsStartPoint.clear();
}

void Client::update(sf::Time deltaTime)
{	 
	_abstractMaze[_cellToRedraw[0]][_cellToRedraw[1]] = _cellToRedraw[2];

	switch(_abstractMaze[_cellToRedraw[0]][_cellToRedraw[1]])
	{
	case 0:
		_levelSprites[_cellToRedraw[0]][_cellToRedraw[1]].setTexture(_wallTexture);
		break;

	case 1:
		_levelSprites[_cellToRedraw[0]][_cellToRedraw[1]].setTexture(_pillTexture);
		break;

	case 3:
		_levelSprites[_cellToRedraw[0]][_cellToRedraw[1]].setTexture(_nothingTexture);
		break;
	}

	_levelSprites[_cellToRedraw[0]][_cellToRedraw[1]].setPosition(_cellToRedraw[0] * _cellPixelSize, 
																  _cellToRedraw[1] * _cellPixelSize);

	sf::Vector2f movement(_pacmanMovingVector.x, _pacmanMovingVector.y);

	_pacmanSprite.move(movement * deltaTime.asSeconds());

	for(int i = 0; i < _ghostSprites.size(); i++)
	{
		movement.x = _ghostsMovingVectors[i].x;
		movement.y = _ghostsMovingVectors[i].y;
		_ghostSprites[i].move(movement * deltaTime.asSeconds());
	}
}	 
	 
void Client::render()
{	 
	 _window.clear();

	for (int i = 0; i < _levelSprites.size(); i++)
	{
		for (int j = 0; j < _levelSprites.size(); j++)
		{
			_window.draw(_levelSprites[i][j]);
		}
	}

	_window.draw(_pacmanSprite);

	for(int i = 0; i < _ghostSprites.size(); i++)
	{
		_window.draw(_ghostSprites[i]);
	}

	_window.display();
}	 
	 
void Client::processEvents(int &gameState)
{
	sf::Event windowEvent;

	while(_window.pollEvent(windowEvent))
	{
		switch(windowEvent.type)
		{
		case sf::Event::KeyPressed:
			if(windowEvent.key.code == sf::Keyboard::Escape)
				_window.close();

			if(windowEvent.key.code == sf::Keyboard::Space)
				gameState = GameStates::GAME_RUNNING;

			break;

		case sf::Event::KeyReleased:
			if(windowEvent.key.code == sf::Keyboard::W  ||
				windowEvent.key.code == sf::Keyboard::A ||
				windowEvent.key.code == sf::Keyboard::S ||
				windowEvent.key.code == sf::Keyboard::D)
				_keyPressed = Key::KEY_RELEASED;
			break;

		case sf::Event::Closed: 
			_window.close();
			break;
		}
	}
}

void Client::input()
{	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		_keyPressed = Key::KEY_PRESSED_UP;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_keyPressed = Key::KEY_PRESSED_DOWN;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		_keyPressed = Key::KEY_PRESSED_LEFT;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_keyPressed = Key::KEY_PRESSED_RIGHT;
	}
}

bool Client::isWindowOpen() const
{
	return _window.isOpen();
}

sf::Time Client::getFps() const
{
	return _fps;
}