#include "Logic.h"
#include "Vector2.h"
#include <iostream>

Vector2<int> Logic::cellsToChange(0,0);

Logic::Logic()
{

}

void Logic::processMovement(Pacman &pacman, Maze &maze)
{
	Vector2<int> coords(0,0);

	switch(pacman.getDirection())	
	{
		case Direction::UP:
			coords.x = pacman.getPosition().x;
			coords.y = pacman.getPosition().y - 1;
			break;

		case Direction::DOWN:
			coords.x = pacman.getPosition().x;
			coords.y = pacman.getPosition().y + 1;
			break;

		case Direction::LEFT:
			coords.x = pacman.getPosition().x - 1;
			coords.y = pacman.getPosition().y;
			break;

		case Direction::RIGHT:
			coords.x = pacman.getPosition().x + 1;
			coords.y = pacman.getPosition().y;
			break;

		case Direction::STOP:
			coords.x = pacman.getPosition().x;
			coords.y = pacman.getPosition().y;
			break;
	}

	if(maze.getMaze()[coords.x][coords.y].getType() != Type::NOTHING)
	{
		if(Physics::isIntersects(&pacman, &maze.getMaze()[coords.x][coords.y], pacman.getDirection()))
		{
			switch(maze.getMaze()[coords.x][coords.y].getType())
			{
			case Type::PILL:
					pacman.setScore(pacman.getScore() + 2);
					maze.getMaze()[coords.x][coords.y].setType(Type::NOTHING);
					cellsToChange.setXY(coords.x, coords.y);
					break;

				case Type::BONUS:
					break;

				case Type::WALL:
					pacman.setDirection(Direction::STOP);
					break;
			}
		}
	}

	pacman.setMovingVector();
}