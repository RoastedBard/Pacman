#include "Collider.h"


Collider::Collider(void)
{
	_center.setXY(0.f, 0.f);
}


Collider::~Collider(void)
{
}

void Collider::setCenter(Vector2<float> center)
{
	_center = center;
}

void Collider::setCenter(float x, float y)
{
	_center.setXY(x, y);
}

Vector2<float> Collider::getCenter() const
{
	return _center;
}