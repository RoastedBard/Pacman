#include "AmbushAI.h"


AmbushAI::AmbushAI(void)
{
}


AmbushAI::~AmbushAI(void)
{
}

void AmbushAI::_countDestinationPoint(Pacman pacman, Maze maze)
{
	Vector2<int> target = pacman.getPosition();

	switch(pacman.getDirection())
	{
	case Direction::UP:
		target.y += 4;
		break;

	case Direction::DOWN:
		target.y -= 4;
		break;

	case Direction::LEFT:
		target.x -= 4;
		break;

	case Direction::RIGHT:
		target.x += 4;
		break;
	}

	if(checkTarget(target, maze))
		_destinationPoint = target;
	else
		_destinationPoint = _startPoint;
}

bool AmbushAI::checkTarget(Vector2<int> target, Maze maze)
{
	if((target.x > 0 && target.y > 0) && (target.x < maze.getMazeSize() && target.y < maze.getMazeSize()))
	{
		if(maze.getMaze()[target.x][target.y].getType() != Type::WALL)
		{
			return true;
		}
	}

	return false;
}