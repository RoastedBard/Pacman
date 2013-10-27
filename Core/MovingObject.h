#ifndef PACMAN_MOVINGOBJECT_H
#define	PACMAN_MOVINGOBJECT_H

#include "gameobject.h"

class MovingObject :
	public GameObject
{
public:
	void		   setVelocity(float velocity);
	float		   getVelocity() const;
	void		   setDirection(Direction::Id direction);
	Direction::Id  getDirection() const;
	void		   setMovingVector();
	virtual void   setMovingVector(Vector2<float> movingVector);
	void		   setMovingVector(float x, float y);
	Vector2<float> getMovingVector() const;

public:
	MovingObject(void);
	~MovingObject(void);

protected:
	float		   _velocity;
	Vector2<float> _movingVector;
	Direction::Id  _direction;
};

#endif