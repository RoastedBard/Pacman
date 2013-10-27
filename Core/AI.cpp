#include "AI.h"

void AI::findPath(Maze maze, Ghost &ghost, Pacman pacman)
{
	_openList.clear();
	_closedList.clear();

	_startPoint	= ghost.getPosition();

	_countDestinationPoint(pacman, maze);

	ghost.setDestinationPoint(_destinationPoint);

	if(_startPoint == _destinationPoint)
		return;

	std::shared_ptr<WayNode> startWayNode(new WayNode(_startPoint.x, _startPoint.y));

	_openList.push_back(startWayNode);

	_aStarPathFindingAlghortim(startWayNode, maze, ghost);

	_initWay();

	std::reverse(_way.begin(), _way.end());
	ghost.setWay(_way);
}

//void AI::_countDestinationPoint(Pacman pacman)
//{
//	_destinationPoint = pacman.getPosition();
//}

void AI::_aStarPathFindingAlghortim(std::shared_ptr<WayNode> wayNode, Maze maze, Ghost ghost)
{
	for(int i = 0; i < _openList.size(); i++)
	{
		if(wayNode->m_position == _openList[i]->m_position)
		{
			_closedList.push_back(_openList[i]);

			auto it = _openList.begin() + i;

			_openList.erase(it);

			break;
		}
	}

	//std::vector<Vector2<int>> coords;

	//switch(ghost.getDirection())
	//{
	//case Direction::UP:
	//	coords.resize(3);
	//	coords[0].setXY(wayNode->m_position.x,	   wayNode->m_position.y - 1);
	//	coords[1].setXY(wayNode->m_position.x - 1, wayNode->m_position.y);
	//	coords[2].setXY(wayNode->m_position.x + 1, wayNode->m_position.y);
	//	break;

	//case Direction::DOWN:
	//	coords.resize(3);
	//	coords[0].setXY(wayNode->m_position.x,	   wayNode->m_position.y + 1);
	//	coords[1].setXY(wayNode->m_position.x - 1, wayNode->m_position.y);
	//	coords[2].setXY(wayNode->m_position.x + 1, wayNode->m_position.y);
	//	break;

	//case Direction::LEFT:
	//	coords.resize(3);
	//	coords[0].setXY(wayNode->m_position.x,	   wayNode->m_position.y - 1);
	//	coords[1].setXY(wayNode->m_position.x,	   wayNode->m_position.y + 1);
	//	coords[2].setXY(wayNode->m_position.x - 1, wayNode->m_position.y);
	//	break;

	//case Direction::RIGHT:
	//	coords.resize(3);
	//	coords[0].setXY(wayNode->m_position.x,	   wayNode->m_position.y - 1);
	//	coords[1].setXY(wayNode->m_position.x,	   wayNode->m_position.y + 1);
	//	coords[2].setXY(wayNode->m_position.x + 1, wayNode->m_position.y);
	//	break;

	//case Direction::STOP:
	//	coords.resize(4);
	//	coords[0].setXY(wayNode->m_position.x,	   wayNode->m_position.y - 1);
	//	coords[1].setXY(wayNode->m_position.x,	   wayNode->m_position.y + 1);
	//	coords[2].setXY(wayNode->m_position.x - 1, wayNode->m_position.y);
	//	coords[3].setXY(wayNode->m_position.x + 1, wayNode->m_position.y);
	//	break;
	//}

	Vector2<int> coords[4];
	coords[0].setXY(wayNode->m_position.x,	   wayNode->m_position.y - 1);
	coords[1].setXY(wayNode->m_position.x,	   wayNode->m_position.y + 1);
	coords[2].setXY(wayNode->m_position.x - 1, wayNode->m_position.y);
	coords[3].setXY(wayNode->m_position.x + 1, wayNode->m_position.y);

	bool add = true;

	for(int i = 0; i < 4; ++i)
	{
		if(maze.getMaze()[coords[i].x][coords[i].y].getType() != Type::WALL)
		{
			for(int j = 0; j < _openList.size(); ++j)
			{
				if(_openList[j]->m_position == coords[i])
				{
					add = false;
					break;
				}
			}

			for(int n = 0; n < _closedList.size(); ++n)
			{
				if(_closedList[n]->m_position == coords[i])
				{
					add = false;
					break;
				}
			}

			if(add)
			{
				std::shared_ptr<WayNode> newWayNode(new WayNode(coords[i].x, coords[i].y, wayNode));

				newWayNode->countF(_destinationPoint);

				_openList.push_back(newWayNode);
			}

			add = true;
		}
	}

	int index = 0;

	int minF = _openList[index]->m_F;

	for(int i = 0; i < _openList.size(); i++)
	{
		if(_openList[i]->m_F <= minF)
		{
			minF = _openList[i]->m_F;
			index = i;
		}
	}

	if(_openList[index]->m_position == _destinationPoint)
	{
		_way.clear();

		std::shared_ptr<WayNode> node = _openList[index];

		do
		{
			_way.push_back(std::shared_ptr<WayPoint>(new WayPoint(node->m_position.x, node->m_position.y)));
			node = node->m_parent;	
		}
		while(node->m_parent != NULL);

		_way.push_back(std::shared_ptr<WayPoint>(new WayPoint(_startPoint.x, _startPoint.y)));
		return;
	}

	else
	{
		_aStarPathFindingAlghortim(_openList[index], maze, ghost);
	}
}

void AI::_initWay()
{
	for(int i = _way.size() - 1; i > 0; --i)
	{
		if((_way[i]->m_x == _way[i - 1]->m_x)      && (_way[i - 1]->m_y == _way[i]->m_y + 1))
			_way[i]->direction = Direction::DOWN;														 
																								 
		if((_way[i]->m_x == _way[i - 1]->m_x)      && (_way[i - 1]->m_y == _way[i]->m_y - 1))
			_way[i]->direction = Direction::UP;														 
																								 
		if((_way[i - 1]->m_x == _way[i]->m_x - 1 ) && (_way[i - 1]->m_y == _way[i]->m_y))
			_way[i]->direction = Direction::LEFT;														 
																								 
		if((_way[i - 1]->m_x == _way[i]->m_x + 1 ) && (_way[i - 1]->m_y == _way[i]->m_y))
			_way[i]->direction = Direction::RIGHT;
	}
}