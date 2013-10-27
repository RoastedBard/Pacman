#include "AgressiveAI.h"
#include "Logic.h"

AgressiveAI::AgressiveAI(void)
{
}


AgressiveAI::~AgressiveAI(void)
{
}

void AgressiveAI::_countDestinationPoint(Pacman pacman, Maze maze)
{
	_destinationPoint = pacman.getPosition();
}