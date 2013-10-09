#pragma once
#include <iostream>
#include <math.h>
#include <memory>
#include "Vector2.h"

struct WayNode
{
	std::shared_ptr<WayNode> m_parent;
	Vector2<int> m_position;
	int m_F;
	int m_G;
	int m_H;

	WayNode()
	{
		m_parent = NULL;
		m_position.x = 0;
		m_position.y = 0;
		m_F = 0;
		m_G = 0;
		m_H = 0;
	}

	WayNode(int x, int y)
	{
		m_parent = NULL;
		m_position.x = x;
		m_position.y = y;
		m_F = 0;
		m_G = 0;
		m_H = 0;
	}

	WayNode(int x, int y, std::shared_ptr<WayNode> parent)
	{
		m_parent = parent;
		m_position.x = x;
		m_position.y = y;
		m_F = 0;
		m_G = 0;
		m_H = 0;
	}

	void setAll(int x, int y, std::shared_ptr<WayNode> parent)
	{
		m_parent = parent;
		m_position.x = x;
		m_position.y = y;
		m_F = 0;
		m_G = 0;
		m_H = 0;
	}

	~WayNode()
	{
		/*if(this->m_parent != NULL)
			delete m_parent;*/
	}

	int countG()
	{
		m_G += m_parent->m_G + 1;
		return m_G;
	}

	int countH(Vector2<int> destination)
	{
		m_H = abs(destination.x - this->m_position.x) + abs(destination.y - this->m_position.y);
		return m_H;
	}

	void countF(Vector2<int> destination)
	{
		m_F = countG() + countH(destination);
	}

	bool operator ==(WayNode node)
	{
		if( node.m_position == this->m_position)
			return true;
		else 
			return false;
	}
};