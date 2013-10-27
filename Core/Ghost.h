#ifndef PACMAN_GHOST_H_
#define PACMAN_GHOST_H_

#include <memory>
#include "MovingObject.h"
#include "AI.h"
#include "Pacman.h"

class AI;
class Ghost :
public MovingObject
{
public:
	void								   seek(Maze maze, Pacman pacman);
	std::vector<std::shared_ptr<WayPoint>> getWay();
	void								   setWay(std::vector<std::shared_ptr<WayPoint>> way);
	void								   clearWay();
	void								   setAI(AI* ai);
	Vector2<int>						   getDestinationPoint() const;
	void								   setDestinationPoint(Vector2<int> destinationPoint);
	void								   setDestinationPoint(int x, int y);
	void								   setIsPointReached(bool isPointReached);
	bool								   isPointReached();

public:
	Ghost(AI* ai);
	Ghost();
	~Ghost(void);

public:
	int iter;

private:
	std::shared_ptr<AI> _ai;
	std::vector<std::shared_ptr<WayPoint>> _way;
	Vector2<int> _destinationPoint;
	bool pointReached;

};

#endif