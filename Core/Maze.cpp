#include "Maze.h"

Maze::Maze(void)
{

}

int Maze::cellPixelSize = 0;

Maze::Maze(int size)
{
	_mazeSize = size;

	_maze.resize(_mazeSize);

	for(int i = 0; i < _mazeSize; i++)
		_maze[i].resize(_mazeSize);

	for(int i = 0; i < _mazeSize; i++)
	{
		for(int j = 0; j < _mazeSize; j++)
			{
				if(i == 0 || i == _mazeSize - 1 || j == 0 || j == _mazeSize - 1)
					_maze[i][j].setType(Type::WALL);
				else
					_maze[i][j].setType(Type::NOTHING);
				
			}
	}
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
			case 0:
				_maze[i][j].setType(Type::WALL);
				break;

			case 1:
				_maze[i][j].setType(Type::PILL);
				break;

			case 2:
				_maze[i][j].setType(Type::NOTHING);
				break;

			case 3:
				_pacmanStart.setXY(i,j);
				_maze[i][j].setType(Type::NOTHING);
				break;
			}
		}
	}
}

Maze::~Maze(void)
{

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