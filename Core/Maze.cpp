#include "Maze.h"

int Maze::cellPixelSize = 0;

Maze::Maze(void)
{

}

Maze::~Maze(void)
{

}

void Maze::initMaze(int** map)
{
	_maze.resize(_mazeSize);

	for(int i = 0; i < _mazeSize; i++)
		_maze[i].resize(_mazeSize);

	for(int i = 0; i < _mazeSize; i++)
	{
		for(int j = 0; j < _mazeSize; j++)
		{
			switch(map[i][j])
			{
			case Type::WALL:
				_maze[i][j].setType(Type::WALL);
				break;

			case Type::PILL:
				_maze[i][j].setType(Type::PILL);
				break;

			case Type::NOTHING:
				_maze[i][j].setType(Type::NOTHING);
				break;

			case Type::PACMAN:
				_pacmanStart.setXY(i,j);
				_maze[i][j].setType(Type::NOTHING);
				break;
			}
		}
	}
}

std::vector<std::vector<StaticObject>>& Maze::getMaze()
{
	return _maze;
}

int Maze::getMazeSize() const
{
	return _mazeSize;
}

void Maze::setMazeSize(int size)
{
	_mazeSize = size;
}

Vector2<int> Maze::getPacmanStartPosition() const
{
	return _pacmanStart;
}

StaticObject& Maze::operator() (int i, int j)
{
	return _maze[i][j];
}

std::vector<Vector2<int>> Maze::getGhostStartPoints()
{
	return _ghostStartPoints;
}

void Maze::setGhostStartPoints(Vector2<int> position)
{
	_ghostStartPoints.push_back(position);
}