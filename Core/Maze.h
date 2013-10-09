#ifndef PACMAN_MAZE_H
#define	PACMAN_MAZE_H

#include "CellContent.h"
#include <vector>

class Maze
{
private:
	std::vector<std::vector<StaticObject>> _maze;
	int			   _mazeSize;
	Vector2<int>   _pacmanStart;

public:
	static int cellPixelSize;

public:

	Maze(void);
	Maze(int size);
	~Maze(void);

	void		   initMaze(int** map);
	std::vector<std::vector<StaticObject>>& getMaze();
	int			   getMazeSize() const;
	void		   setMazeSize(int size);
	Vector2<int>   getPacmanStartPosition() const;

	StaticObject& operator() (int i, int j);
};

#endif