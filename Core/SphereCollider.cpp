#include "SphereCollider.h"


SphereCollider::SphereCollider(void)
{
	_radius = 0;
}


SphereCollider::~SphereCollider(void)
{
}

void SphereCollider::setRadius(int radius)
{
	_radius = radius;
}

int SphereCollider::getRadius() const
{
	return _radius;
}