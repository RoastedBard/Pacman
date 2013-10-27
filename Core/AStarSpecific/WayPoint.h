#pragma once
#include "Enums.h"

struct WayPoint
{
	int m_x;
	int m_y;
	int direction;
	
	WayPoint(){};

	WayPoint(int x, int y)
	{
		m_x = x;
		m_y = y;
		direction = -1;
	}

	WayPoint(int x, int y, int dir)
	{
		m_x = x;
		m_y = y;
		direction = dir;
	}
};