#include "Physics.h"
#include <cmath>
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

bool Physics::isSphereAndSphereCollides(SphereCollider colliderA, SphereCollider colliderB)
{
	double xDistance = std::pow((colliderB.getCenter().x - colliderA.getCenter().x), 2);
	double yDistance = std::pow((colliderB.getCenter().y - colliderA.getCenter().y), 2);

	double distance = std::sqrt(xDistance + yDistance);

	int radiusSum = colliderA.getRadius() + colliderB.getRadius();

	if(distance <= radiusSum)
		return true;

	return false;
}

bool Physics::isBoxAndBoxCollides(BoxCollider colliderA, BoxCollider colliderB)
{
	float Tx = abs( ((colliderA.getTop().x + colliderA.getBottom().x) / 2) - ((colliderB.getTop().x + colliderB.getBottom().x) / 2) );
	float Ty = abs( ((colliderA.getTop().y + colliderA.getBottom().y) / 2) - ((colliderB.getTop().y + colliderB.getBottom().y) / 2) );

	float Ax = abs((colliderA.getBottom().x - colliderA.getTop().x) / 2);
	float Ay = abs((colliderA.getTop().y    - colliderA.getBottom().y) / 2);

	float Bx = abs((colliderB.getBottom().x - colliderB.getTop().x) / 2);
	float By = abs((colliderB.getTop().y    - colliderB.getBottom().y) / 2);

	if(Tx >= Ax + Bx || Ty >= Ay + By)
		return false;

	return true;
}