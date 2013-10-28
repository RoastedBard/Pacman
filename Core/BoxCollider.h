#ifndef PACMAN_BOXCOLLIDER_H
#define	PACMAN_BOXCOLLIDER_H

#include "Collider.h"

class BoxCollider :
	public Collider
{
public:
	void		   setWidth(int width);
	int			   getWidth() const;
	void		   setHeight(int height);
	int			   getHeight() const;
	void		   setTop(Vector2<float> top);
	void		   setTop(float x, float y);
	Vector2<float> getTop() const;
	void		   setBottom(Vector2<float> bottom);
	void		   setBottom(float x, float y);
	Vector2<float> getBottom() const;

public:
	BoxCollider(void);
	~BoxCollider(void);

private:
	int			   _width;
	int			   _height;
	Vector2<float> _top;
	Vector2<float> _bottom;
};

#endif