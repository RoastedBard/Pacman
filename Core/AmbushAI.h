#ifndef PACMAN_AMBUSHAI_H
#define	PACMAN_AMBUSHAI_H

#include "AI.h"
#include "Ghost.h"
#include "AStarSpecific\WayPoint.h"

class AmbushAI :
	public AI
{
public:
	AmbushAI(void);
	~AmbushAI(void);

private:
	virtual void _countDestinationPoint(Pacman pacman, Maze maze) override;
	bool checkTarget(Vector2<int> target, Maze maze);
};

#endif