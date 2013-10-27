#ifndef PACMAN_AI_H
#define	PACMAN_AI_H

#include "Maze.h"
#include "AStarSpecific\WayPoint.h"
#include "Ghost.h"
#include "AStarSpecific\WayNode.h"
#include "Pacman.h"
#include <memory>

class Ghost;
class AI
	{
	public:
		void findPath(Maze maze, Ghost &ghost, Pacman pacman);

	protected:
		virtual void _countDestinationPoint(Pacman pacman, Maze maze) = 0;

	protected:
		Vector2<int> _destinationPoint;
		Vector2<int> _startPoint;

	private:
		void _aStarPathFindingAlghortim(std::shared_ptr<WayNode> wayNode, Maze maze, Ghost ghost);
		void _initWay();
		
	private:
		std::vector<std::shared_ptr<WayNode>>  _openList;
		std::vector<std::shared_ptr<WayNode>>  _closedList;
		std::vector<std::shared_ptr<WayPoint>> _way;
	};

#endif