#ifndef PACMAN_COLLIDER_H
#define	PACMAN_COLLIDER_H

#include "Vector2.h"

class Collider
{
public:
	void		   setCenter(Vector2<float> center);
	void		   setCenter(float x, float y);
	Vector2<float> getCenter() const;

public:
	Collider(void);
	virtual ~Collider(void);

private:
	Vector2<float> _center;
};

#endif