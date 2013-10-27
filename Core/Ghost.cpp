#include "Ghost.h"
#include "Logic.h"

Ghost::Ghost(AI *ai)
{
	_velocity = 90.f;
	_direction = Direction::STOP;
	_movingVector.setXY(0, 0);
	_ai.reset(ai);
}

Ghost::Ghost()
{
	_velocity = 100.f;
	_direction = Direction::STOP;
	_movingVector.setXY(0, 0);
}

Ghost::~Ghost(void)
{
}

void Ghost::seek(Maze maze, Pacman pacman)
{
	_ai->findPath(maze, *this, pacman);
}

std::vector<std::shared_ptr<WayPoint>> Ghost::getWay()
{
	return _way;
}

void Ghost::setWay(std::vector<std::shared_ptr<WayPoint>> way)
{
	_way = way;
}

void Ghost::setAI(AI* ai)
{
	_ai.reset(ai);
}

Vector2<int> Ghost::getDestinationPoint() const
{
	return _destinationPoint;
}

void Ghost::setDestinationPoint(Vector2<int> destinationPoint)
{
	_destinationPoint = destinationPoint;
}

void Ghost::setDestinationPoint(int x, int y)
{
	_destinationPoint.x = x;
	_destinationPoint.y = y;
}

void Ghost::clearWay()
{
	_way.clear();
}

void Ghost::setIsPointReached(bool isPointReached)
{
	pointReached = isPointReached;
}

bool Ghost::isPointReached()
{
	return pointReached;
}