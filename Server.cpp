#include "Server.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <string>

Server::Server(void)
{
	loadLevel("levels/Level1.txt");
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

	_pacman.setBoundingBox(data.pacmanBoundingBox.topX,    data.pacmanBoundingBox.topY, 
						   data.pacmanBoundingBox.bottomX, data.pacmanBoundingBox.bottomY);
}

void Server::readData(CommonDataFromClient data)
{
	_keyPressed = data.keyPressed;

	_pacman.setBoundingBox(data.pacmanBoundingBox.topX,    data.pacmanBoundingBox.topY, 
						   data.pacmanBoundingBox.bottomX, data.pacmanBoundingBox.bottomY);

	_pacman.setPosition(data.pacmanPosition[0], data.pacmanPosition[1]);
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

	data.pacmanStartPoint[0] = _maze.getPacmanStartPosition().x;
	data.pacmanStartPoint[1] = _maze.getPacmanStartPosition().y;
}

void Server::sendData(CommonDataFromServer &data)
{
	data.cellToRedraw[0] = Logic::cellsToChange.x;
	data.cellToRedraw[1] = Logic::cellsToChange.y;
	data.cellToRedraw[2] = _maze(data.cellToRedraw[0], data.cellToRedraw[1]).getType();
	data.pacmanMovingVector[0] = _pacman.getMovingVector().x;
	data.pacmanMovingVector[1] = _pacman.getMovingVector().y;
}

void Server::update()
{
	processInput();
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
				map[j][i] = 0;
				break;

			case 'o':
				map[j][i] = 1;
				break;

			case '_':
				map[j][i] = 2;
				break;

			case 'P':
				map[j][i] = 3;
				_pacman.setPosition(j,i);
				break;
			}
		}

		i++;
	}

	_maze.initMaze(map);

	file.close();

	for(int i = 0; i < _maze.getMazeSize(); i++)
		delete[] map[i];
	delete[] map;
}