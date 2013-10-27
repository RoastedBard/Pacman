#ifndef PACMAN_AGRESSIVEAI_H_
#define PACMAN_AGRESSIVEAI_H_

#include <memory>
#include "AStarSpecific\WayNode.h"
#include "AStarSpecific\WayPoint.h"
#include "AI.h"
#include "Ghost.h"

class AgressiveAI :
	public AI
{
public:

public:
	AgressiveAI(void);
	~AgressiveAI(void);

private:
	virtual void _countDestinationPoint(Pacman pacman, Maze maze) override;
};

#endif