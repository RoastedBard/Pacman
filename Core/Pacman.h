#ifndef PACMAN_PACMAN_H
#define	PACMAN_PACMAN_H

#include "movingobject.h"

class Pacman :
	public MovingObject
{
public:
	void setLife(int life);
	int	 getLife() const;
	void setScore(int score);
	int  getScore() const;
	void setRealWidth(int width);
	int  getRealWidth() const;
	void setRealHeight(int height);
	int  getRealHeight() const;

public:
	Pacman(void);
	~Pacman(void);

private:

	int _life;
	int _score;
	int _realWidth;
	int _realHeight;
};

#endif