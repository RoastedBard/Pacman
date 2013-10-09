#ifndef PACMAN_PHYSICS_H
#define	PACMAN_PHYSICS_H

#include "GameObject.h"

class Physics
{
public:
	static bool isIntersects(GameObject *a, GameObject *b, Direction::Id id);
};

#endif