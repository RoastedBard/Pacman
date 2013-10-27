#include "Physics.h"
#include <iostream>

bool Physics::isIntersects(GameObject *a, GameObject *b, Direction::Id id)
{
	BoundingBox aBb = a->getBoundingBox();
	BoundingBox bBb = b->getBoundingBox();
	
	float Tx = abs( ((aBb.top.x + aBb.bottom.x) / 2) - ((bBb.top.x + bBb.bottom.x) / 2) );
	float Ty = abs( ((aBb.top.y + aBb.bottom.y) / 2) - ((bBb.top.y + bBb.bottom.y) / 2) );

	float Ax = abs((aBb.bottom.x - aBb.top.x) / 2);
	float Ay = abs((aBb.top.y - aBb.bottom.y) / 2);

	float Bx = abs((bBb.bottom.x - bBb.top.x) / 2);
	float By = abs((bBb.top.y - bBb.bottom.y) / 2);

	if(Tx >= Ax + Bx || Ty >= Ay + By)
		return false;

	return true;
}

