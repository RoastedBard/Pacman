#ifndef DATAFROMSERVERANDCLIENT_H_
#define DATAFROMSERVERANDCLIENT_H_

#include <vector>
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

//struct ClientData
//{
//	struct BoundingBox
//	{
//		float topX;
//		float topY;
//		float bottomX;
//		float bottomY;
//
//		void setBoundingBox(float topx,	float topy, float bottomx, float bottomy)
//		{
//			this->topX = topx;		 this->topY = topy;
//			this->bottomX = bottomx; this->bottomY = bottomy;
//		}
//	};
//
//	BoundingBox	pacmanBoundingBox;
//};

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

	BoundingBox	pacmanBoundingBox;
	vector<vector<BoundingBox>> cellBoundingBoxes;
	//BoundingBox **cellBoundingBoxes;

	InitDataFromClient()
	{
		pacmanBoundingBox.setBoundingBox(0,0,0,0);
		//cellBoundingBoxes.resize(0);
		
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

	BoundingBox	pacmanBoundingBox;
	int	  keyPressed;
	int	  pacmanPosition[2];

	CommonDataFromClient()
	{
		pacmanBoundingBox.setBoundingBox(0,0,0,0);
		keyPressed = 0;
		pacmanPosition[0] = 0;
		pacmanPosition[1] = 0;
	}
};

//struct ServerData
//{
//	
//};

struct InitDataFromServer 
{
	vector<vector<int>> mazeCellIds;
	//int **mazeCellIds;;
	int pacmanStartPoint[2];
	int mazeSize;

	InitDataFromServer()
	{
		//mazeCellIds.resize(0);
		pacmanStartPoint[0] = 0;
		pacmanStartPoint[1] = 0;
		mazeSize = 0;
	}
};

struct CommonDataFromServer 
{
	int	  cellToRedraw[3];
	float pacmanMovingVector[2];

	CommonDataFromServer()
	{
		cellToRedraw[0] = 0;
		cellToRedraw[1] = 0;
		cellToRedraw[2] = 0;

		pacmanMovingVector[0] = 0;
		pacmanMovingVector[1] = 0;
	}
};



#endif