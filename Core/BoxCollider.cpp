#include "BoxCollider.h"

BoxCollider::BoxCollider(void)
{
	_width = 0;
	_height = 0;
	_top.setXY(0.f, 0.f);
	_bottom.setXY(0.f, 0.f);
}

BoxCollider::~BoxCollider(void)
{

}

void BoxCollider::setWidth(int width)
{
	_width = width;
}

int	 BoxCollider::getWidth() const
{
	return _width;
}

void BoxCollider::setHeight(int height)
{
	_height = height;
}

int	 BoxCollider::getHeight() const
{
	return _height;
}

void BoxCollider::setTop(Vector2<float> top)
{
	_top = top;
}

void BoxCollider::setTop(float x, float y)
{
	_top.setXY(x, y);
}

Vector2<float> BoxCollider::getTop() const
{
	return _top;
}

void BoxCollider::setBottom(Vector2<float> bottom)
{
	_bottom = bottom;
}

void BoxCollider::setBottom(float x, float y)
{
	_bottom.setXY(x, y);
}

Vector2<float> BoxCollider::getBottom() const
{
	return _bottom;
}