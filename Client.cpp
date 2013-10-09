#include "Client.h"
#include <iostream>
#include <fstream>
#include <istream>

Client::Client(void)
	:_screenWidth(600),
	 _screenHeight(600),
	 _window(sf::VideoMode(_screenWidth, _screenHeight), "Pacman 0.0.1")
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

	_pacmanStartPoint[0] = data.pacmanStartPoint[0];
	_pacmanStartPoint[1] = data.pacmanStartPoint[1];
}

void Client::readData(CommonDataFromServer data)
{
	_cellToRedraw[0] = data.cellToRedraw[0];
	_cellToRedraw[1] = data.cellToRedraw[1];
	_cellToRedraw[2] = data.cellToRedraw[2];

	_pacmanMovingVector[0] = data.pacmanMovingVector[0];
	_pacmanMovingVector[1] = data.pacmanMovingVector[1];
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
}

void Client::sendData(CommonDataFromClient &data)
{
	data.keyPressed = _keyPressed;
	data.pacmanBoundingBox.setBoundingBox(_pacmanSprite.getGlobalBounds().left,  _pacmanSprite.getGlobalBounds().top,
										  _pacmanSprite.getGlobalBounds().left + _pacmanSprite.getLocalBounds().width,
										  _pacmanSprite.getGlobalBounds().top +  _pacmanSprite.getLocalBounds().height);

	data.pacmanPosition[0] = _pacmanSprite.getPosition().x / _cellPixelSize;
	data.pacmanPosition[1] = _pacmanSprite.getPosition().y / _cellPixelSize;
}

void Client::initialize()
{
	_cellPixelSize	 = _screenWidth / _mazeSize;
	_pacmanPixelSize = (86.7 * _cellPixelSize) / 100;

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

	_pacmanSprite.setTexture(_pacmanTexture);
	_pacmanSprite.setPosition(_pacmanStartPoint[0] * _cellPixelSize + _cellPixelSize/2, _pacmanStartPoint[1] * _cellPixelSize + _cellPixelSize/2);
	_pacmanSprite.setScale(_pacmanPixelSize / _pacmanSprite.getLocalBounds().width, _pacmanPixelSize / _pacmanSprite.getLocalBounds().height);
	_pacmanSprite.setOrigin(_pacmanSprite.getLocalBounds().width / 2, _pacmanSprite.getLocalBounds().height / 2);
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

	sf::Vector2f movement(_pacmanMovingVector[0], _pacmanMovingVector[1]);

	_pacmanSprite.move(movement * deltaTime.asSeconds());
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
	_window.display();
}	 
	 
void Client::processEvents()
{
	sf::Event windowEvent;

	while(_window.pollEvent(windowEvent))
	{
		switch(windowEvent.type)
		{
		case sf::Event::KeyPressed:
			if(windowEvent.key.code == sf::Keyboard::Escape)
				_window.close();
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