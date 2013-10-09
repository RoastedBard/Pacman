#ifndef PACMAN_VECTOR2_H
#define	PACMAN_VECTOR2_H

template <typename T>
class Vector2
{
public:
	T x;
	T y;
	Vector2(){}
	Vector2(T xx, T yy)
	{
		x = xx;
		y = yy;
	}

	void setXY(T xx, T yy)
	{
		x = xx;
		y = yy;
	}
	Vector2& operator * (T value)
	{
		x*=value;
		y*=value;

		return *this;
	}
};

#endif         