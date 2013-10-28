#ifndef PACMAN_PHYSICS_H
#define	PACMAN_PHYSICS_H

#include "GameObject.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

class Physics
{
public:
	static bool isIntersects(GameObject *a, GameObject *b, Direction::Id id);

private:
	static bool isSphereAndSphereCollides(SphereCollider colliderA, SphereCollider colliderB);
	static bool isBoxAndBoxCollides(BoxCollider colliderA, BoxCollider colliderB);
	static bool isSphereAndBoxCollides(SphereCollider colliderA, BoxCollider colliderB){};
};

#endif