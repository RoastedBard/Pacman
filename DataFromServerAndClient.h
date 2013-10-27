#ifndef DATAFROMSERVERANDCLIENT_H_
#define DATAFROMSERVERANDCLIENT_H_

#include <vector>
#include "Core\Vector2.h"

using namespace std;

enum Key
{
	KEY_PRESSED_UP = 0,
	KEY_PRESSED_DOWN,
	KEY_PRESSED_LEFT,
	KEY_PRESSED_RIGHT,
	KEY_RELEASED
};

enum DataType
{
	INIT_DATA = 0,
	COMMON_DATA
};

struct InitDataFromClient 
{
	struct BoundingBox
	{
		float topX;
		float topY;
		float bottomX;
		float bottomY;

		void setBoundingBox(float topx,	float topy, float bottomx, float bottomy)
		{
			this->topX = topx;		 this->topY = topy;
			this->bottomX = bottomx; this->bottomY = bottomy;
		}
	};

	struct GhostBounds
	{
		Vector2<float> upOrLeft;
		Vector2<float> downOrRight;
	};

	BoundingBox	pacmanBoundingBox;
	vector<vector<BoundingBox>> cellBoundingBoxes;
	vector<BoundingBox> ghostsBoundingBoxes;

	InitDataFromClient()
	{
		pacmanBoundingBox.setBoundingBox(0,0,0,0);
	}
};

struct CommonDataFromClient 
{
	struct BoundingBox
	{
		float topX;
		float topY;
		float bottomX;
		float bottomY;

		void setBoundingBox(float topx,	float topy, float bottomx, float bottomy)
		{
			this->topX = topx;		 this->topY = topy;
			this->bottomX = bottomx; this->bottomY = bottomy;
		}
	};

	struct GhostBounds
	{
		Vector2<float> upOrLeft;
		Vector2<float> downOrRight;
	};

	BoundingBox	pacmanBoundingBox;
	int	  keyPressed;
	Vector2<int>  pacmanPosition;
	vector<BoundingBox> ghostsBoundingBoxes;

	CommonDataFromClient()
	{
		pacmanBoundingBox.setBoundingBox(0,0,0,0);
		keyPressed = 0;
		pacmanPosition.setXY(0, 0);
	}
};

struct InitDataFromServer 
{
	vector<vector<int>> mazeCellIds;

	vector<Vector2<int>> ghostPositions;

	Vector2<int> pacmanStartPoint;
	int mazeSize;

	InitDataFromServer()
	{
		pacmanStartPoint.setXY(0, 0);
		mazeSize = 0;
	}
};

struct CommonDataFromServer 
{
	int	  cellToRedraw[3];
	Vector2<float> pacmanMovingVector;

	vector<Vector2<float>> ghostsMovingVectors;

	CommonDataFromServer()
	{
		cellToRedraw[0] = 0;
		cellToRedraw[1] = 0;
		cellToRedraw[2] = 0;

		pacmanMovingVector.setXY(0.f, 0.f);
	}
};



#endif