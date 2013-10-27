#ifndef PACMAN_GAMEOBJECT_H
#define	PACMAN_GAMEOBJECT_H

#include "BoundingBox.h"
#include "Vector2.h"
#include "Enums.h"

class GameObject
{
public:
	void		 setPosition(int x, int y);
	void		 setPosition(Vector2<int> position);
	Vector2<int> getPosition() const;
	void		 setBoundingBox(Vector2<float> top, Vector2<float> bottom);
	void		 setBoundingBox(float topX, float topY, float bottomX, float bottomY);
	BoundingBox  getBoundingBox() const;
	void		 setTexture(Textures::Id texture);
	Textures::Id getTexture() const;

public:
	GameObject(void);
	virtual ~GameObject(void);

protected:
	BoundingBox	 _boundingBox;
	Vector2<int> _position;
	Textures::Id _texture;
};

#endif