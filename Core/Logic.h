#ifndef PACMAN_LOGIC_H
#define	PACMAN_LOGIC_H

#include "Pacman.h"
#include "Maze.h"
#include "Physics.h"

class Logic
{
public:
	static Vector2<int> cellsToChange;

public:
	Logic();

public:
	static void processMovement(Pacman &pacman, Maze &maze);
};

#endif