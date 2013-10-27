#ifndef PACMAN_LOGIC_H
#define	PACMAN_LOGIC_H

#include "Pacman.h"
#include "Maze.h"
#include "Physics.h"
#include "Ghost.h"
#include "AStarSpecific\WayNode.h"
#include "AStarSpecific\WayPoint.h"

class Logic
{
public:
	static void processMovement(Pacman &pacman, Maze &maze);
	static void processGhostMovement(Ghost &ghost, Maze &maze);

public:
	static Vector2<int> cellsToChange;

};

#endif