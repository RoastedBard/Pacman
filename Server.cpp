#include "Server.h"
#include "Core\AgressiveAI.h"
#include "Core\AmbushAI.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <string>

Server::Server(void)
{
	loadLevel("levels/LevelLikeOriginal.txt");
}


Server::~Server(void)
{

}

void Server::readData(InitDataFromClient data)
{
	for(int i = 0; i < _maze.getMazeSize(); i++)
	{
		for(int j = 0; j < _maze.getMazeSize(); j++)
		{
			_maze(i, j).setBoundingBox(data.cellBoundingBoxes[i][j].topX,    data.cellBoundingBoxes[i][j].topY,
									   data.cellBoundingBoxes[i][j].bottomX, data.cellBoundingBoxes[i][j].bottomY);
		}
	}

	for(int i = 0; i < _ghosts.size(); i++)
	{
		_ghosts[i].setBoundingBox(data.ghostsBoundingBoxes[i].topX,    data.ghostsBoundingBoxes[i].topY, 
								  data.ghostsBoundingBoxes[i].bottomX, data.ghostsBoundingBoxes[i].bottomY);
	}

	_pacman.setBoundingBox(data.pacmanBoundingBox.topX,    data.pacmanBoundingBox.topY, 
						   data.pacmanBoundingBox.bottomX, data.pacmanBoundingBox.bottomY);
}

void Server::readData(CommonDataFromClient data)
{
	_keyPressed = data.keyPressed;

	_pacman.setBoundingBox(data.pacmanBoundingBox.topX,    data.pacmanBoundingBox.topY, 
						   data.pacmanBoundingBox.bottomX, data.pacmanBoundingBox.bottomY);

	_pacman.setPosition(data.pacmanPosition.x, data.pacmanPosition.y);

	for(int i = 0; i < _ghosts.size(); i++)
	{
		_ghosts[i].setBoundingBox(data.ghostsBoundingBoxes[i].topX,    data.ghostsBoundingBoxes[i].topY, 
								  data.ghostsBoundingBoxes[i].bottomX, data.ghostsBoundingBoxes[i].bottomY);
	}
}

void Server::sendData(InitDataFromServer &data)
{
	data.mazeSize = _maze.getMazeSize();

	data.mazeCellIds.resize(_maze.getMazeSize());
	for(int i = 0; i < _maze.getMazeSize(); i++)
		data.mazeCellIds[i].resize(_maze.getMazeSize());

	for(int i = 0; i < _maze.getMazeSize(); i++)
	{
		for(int j = 0; j < _maze.getMazeSize(); j++)
		{
			switch(_maze(i, j).getType())
			{
			case Type::WALL:
				data.mazeCellIds[i][j] = 0;
				break;

			case Type::PILL:
				data.mazeCellIds[i][j] = 1;
				break;

			case Type::NOTHING:
				data.mazeCellIds[i][j] = 2;
				break;
			}
		}
	}

	data.pacmanStartPoint.x = _maze.getPacmanStartPosition().x;
	data.pacmanStartPoint.y = _maze.getPacmanStartPosition().y;

	data.ghostPositions.resize(_ghosts.size());

	for(int i = 0; i < data.ghostPositions.size(); i++)
	{
		data.ghostPositions[i].x = _ghosts[i].getPosition().x;
		data.ghostPositions[i].y = _ghosts[i].getPosition().y;
	}
}

void Server::sendData(CommonDataFromServer &data)
{
	data.cellToRedraw[0] = Logic::cellsToChange.x;
	data.cellToRedraw[1] = Logic::cellsToChange.y;
	data.cellToRedraw[2] = _maze(data.cellToRedraw[0], data.cellToRedraw[1]).getType();
	data.pacmanMovingVector.x = _pacman.getMovingVector().x;
	data.pacmanMovingVector.y = _pacman.getMovingVector().y;

	data.ghostsMovingVectors.clear();
	for(int i = 0; i < _ghosts.size(); i++)
	{
		data.ghostsMovingVectors.push_back(_ghosts[i].getMovingVector());
	}
}

void Server::update(int &gameState)
{
	processInput();
	for(int i = 0; i < _ghosts.size(); i++)
	{
		if(_ghosts[i].isPointReached())
		{
			_ghosts[i].seek(_maze, _pacman);
		}

		Logic::processGhostMovement(_ghosts[i], _maze);

		if(_ghosts[i].getPosition() == _pacman.getPosition())
		{
			gameState = GameStates::GAME_PAUSED;

			if(_pacman.getLife() == 0)
			{
				//cout<<"[]Pacman is dead!\n";
			}

			else
			{
				_pacman.setLife(_pacman.getLife() - 1);
				cout<<"[]Minus one Life!\n";
			}

			break;
		}
	}
}

void Server::processInput()
{
	switch(_keyPressed)
	{
	case KEY_PRESSED_UP:
		_pacman.setDirection(Direction::UP);
		break;

	case KEY_PRESSED_DOWN:
		_pacman.setDirection(Direction::DOWN);
		break;

	case KEY_PRESSED_LEFT:
		_pacman.setDirection(Direction::LEFT);
		break;

	case KEY_PRESSED_RIGHT:
		_pacman.setDirection(Direction::RIGHT);
		break;

	case KEY_RELEASED:
		_pacman.setDirection(Direction::STOP);
		break;
	}

	Logic::processMovement(_pacman, _maze);
}

void Server::loadLevel(const char* filename)
{
	std::ifstream file(filename);

	if(!file)
	{
		std::cout<<"Unable to open"<<filename<<endl;
	}

	std::string str;

	std::getline(file, str);

	int mazeSize = atoi(str.c_str());

	_maze.setMazeSize(mazeSize);

	int **map = new int*[_maze.getMazeSize()];

	for(int i = 0; i<_maze.getMazeSize(); i++)
		map[i] = new int[_maze.getMazeSize()];

	int i = 0;

	while(std::getline(file, str))
	{
		for(int j = 0; j<str.size(); j++)
		{
			switch(str[j])
			{
			case '#':
				map[j][i] = Type::WALL;
				break;

			case 'o':
				map[j][i] = Type::PILL;
				break;

			case '_':
				map[j][i] = Type::NOTHING;
				break;

			case 'P':
				map[j][i] = Type::PACMAN;
				_pacman.setPosition(j,i);
				break;

			case 'G':
				map[j][i] = Type::NOTHING;
				Ghost ghost;
				ghost.setPosition(j, i);
				_ghosts.push_back(ghost);

				_maze.setGhostStartPoints(ghost.getPosition());

				break;
			}
		}
		i++;
	}

	for(int i = 0; i < _ghosts.size(); i++)
	{
		switch(i)
		{
		case 0:
			_ghosts[i].setAI(new AgressiveAI());
			break;

		case 1:
			_ghosts[i].setAI(new AmbushAI());
			break;

		case 2:
			_ghosts[i].setAI(new AmbushAI());
			break;
		}
	}

	_maze.initMaze(map);

	file.close();

	for(int i = 0; i < _maze.getMazeSize(); i++)
		delete[] map[i];
	delete[] map;
}

void Server::reset()
{
	for (int i = 0; i < _ghosts.size(); i++)
	{
		_ghosts[i].setPosition(_maze.getGhostStartPoints()[i]);
		_ghosts[i].clearWay();
		_ghosts[i].setIsPointReached(true);
		_ghosts[i].setDirection(Direction::STOP);
	}

	_pacman.setPosition(_maze.getPacmanStartPosition());
}