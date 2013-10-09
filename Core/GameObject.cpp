#include "GameObject.h"	


GameObject::GameObject(void)
{
}


GameObject::~GameObject(void)
{
}

void GameObject::setPosition(int x, int y)
{
	_position.x = x;
	_position.y = y;
}

Vector2<int> GameObject::getPosition() const
{
	return _position;
}

void GameObject::setBoundingBox(Vector2<float> top, Vector2<float> bottom)
{
	_boundingBox.top = top;
	_boundingBox.bottom = bottom;
	_boundingBox.center.setXY(_boundingBox.bottom.x - (_boundingBox.bottom.x - _boundingBox.top.x / 2), 
							  _boundingBox.top.y - (_boundingBox.top.y - _boundingBox.bottom.y / 2));
}

void GameObject::setBoundingBox(float topX, float topY, float bottomX, float bottomY)
{
	_boundingBox.top.x = topX;
	_boundingBox.top.y = topY;

	_boundingBox.bottom.x = bottomX;
	_boundingBox.bottom.y = bottomY;

	_boundingBox.center.setXY(_boundingBox.bottom.x - (_boundingBox.bottom.x - _boundingBox.top.x / 2), 
							  _boundingBox.top.y - (_boundingBox.top.y - _boundingBox.bottom.y / 2));
}

BoundingBox  GameObject::getBoundingBox() const
{
	return _boundingBox;
}

void GameObject::setTexture(Textures::Id texture)
{
	_texture = texture;
}

Textures::Id GameObject::getTexture() const
{
	return _texture;
}