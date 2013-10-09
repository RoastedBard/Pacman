#include "MovingObject.h"


MovingObject::MovingObject(void)
{
}


MovingObject::~MovingObject(void)
{
}

void MovingObject::setVelocity(float velocity)
{
	_velocity = velocity;
}

float MovingObject::getVelocity() const
{
	return _velocity;
}

void MovingObject::setDirection(Direction::Id direction)
{
	_direction = direction;
}

Direction::Id MovingObject::getDirection() const
{
	return _direction;
}

void MovingObject::setMovingVector(Vector2<float> movingVector)
{
	_movingVector = movingVector;
}

void MovingObject::setMovingVector(float x, float y)
{
	_movingVector.x = x;
	_movingVector.y = y;
}

Vector2<float>	MovingObject::getMovingVector() const
{
	return _movingVector;
}