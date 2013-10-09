#ifndef PACMAN_BOUNDINGBOX_H
#define	PACMAN_BOUNDINGBOX_H

#include "Vector2.h"

class BoundingBox
{
public:
	BoundingBox(void);

	BoundingBox(Vector2<float> Top, Vector2<float> Bottom)
	{
		top = Top;
		bottom = Bottom;
		center.x = bottom.x - (bottom.x - top.x / 2);
		center.y = top.y - (top.y - bottom.y / 2);
	}

	BoundingBox(float topX, float topY, float bottomX, float bottomY)
	{
		top.x = topX;
		top.y = topY;
		bottom.x = bottomX;
		bottom.y = bottomY;
		center.x = top.x + (bottom.x - top.x / 2);
		center.y = top.y + (top.y - bottom.y / 2);
	}

	~BoundingBox(void);

public:
	Vector2<float> top;
	Vector2<float> bottom;
	Vector2<float> center;
};

#endif