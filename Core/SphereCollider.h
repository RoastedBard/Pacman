#ifndef PACMAN_SPHERECOLLIDER_H
#define	PACMAN_SPHERECOLLIDER_H

#include "Collider.h"

class SphereCollider :
	public Collider
{
public:
	void setRadius(int radius);
	int  getRadius() const;

public:
	SphereCollider(void);
	~SphereCollider(void);

private:
	int _radius;
};

#endif