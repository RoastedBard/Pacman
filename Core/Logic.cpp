#include "Logic.h"
#include "Vector2.h"
#include "Enums.h"
#include <iostream>

Vector2<int> Logic::cellsToChange(0,0);


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

void Logic::processGhostMovement(Ghost &ghost, Maze &maze)
{
	if(ghost.getWay().size() == 0)
		return;

	if(ghost.isPointReached())
		ghost.iter = 0;

	int X = 0;
	int Y = 0;

	//_movingVector.setXY(0,0);

	if(ghost.iter != ghost.getWay().size() -1)
	{
		ghost.setIsPointReached(false);

		if(ghost.getWay()[ghost.iter]->direction == Direction::UP || ghost.getWay()[ghost.iter]->direction == Direction::LEFT)
		{
			X = ghost.getBoundingBox().bottom.x;
			Y = ghost.getBoundingBox().bottom.y;
		}

		else if(ghost.getWay()[ghost.iter]->direction == Direction::DOWN || ghost.getWay()[ghost.iter]->direction == Direction::RIGHT)
		{
			X = ghost.getBoundingBox().top.x;
			Y = ghost.getBoundingBox().top.y;
		}

		if(X != ghost.getWay()[ghost.iter + 1]->m_x || Y != ghost.getWay()[ghost.iter + 1]->m_y)
		{	
			switch(ghost.getWay()[ghost.iter]->direction)
			{
			case Direction::UP:
				ghost.setDirection(Direction::UP);

				break;

			case Direction::DOWN:
				ghost.setDirection(Direction::DOWN);

				break;

			case Direction::LEFT:
				ghost.setDirection(Direction::LEFT);

				break;

			case Direction::RIGHT:
				ghost.setDirection(Direction::RIGHT);

				break;
			}
		}

		else
		{
			++ghost.iter;
			ghost.setPosition(X,Y);
		}
	}

	if(ghost.getPosition().x == ghost.getWay()[ghost.getWay().size() - 1]->m_x && ghost.getPosition().y == ghost.getWay()[ghost.getWay().size() - 1]->m_y)
	{
		ghost.setIsPointReached(true);
	}

	if(ghost.getPosition() == ghost.getDestinationPoint())
	{
		ghost.setDirection(Direction::STOP);
	}

	ghost.setMovingVector();
}