#ifndef PACMAN_VECTOR2_H
#define	PACMAN_VECTOR2_H

template <typename T>
class Vector2;

template <typename T>
bool operator < (Vector2<T> vectl, Vector2<T> vectr)
{
	if(vectl.x == vectr.x && vectl.y == vectr.y)
		return true;
	else
		return false;
}

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

	friend bool operator < <>(Vector2<T> vectl, Vector2<T> vectr);
	
	bool operator == (Vector2<T> vect)
	{
		if(this->x == vect.x && this->y == vect.y)
			return true;
		else
			return false;
	}

	Vector2& operator * (T value)
	{
		x*=value;
		y*=value;

		return *this;
	}
};



#endif         