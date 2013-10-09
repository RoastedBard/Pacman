#include "Pacman.h"
#include <iostream>

Pacman::Pacman(void)
{
	_life  = 3;
	_score = 0;
	_texture = Textures::PACMAN;
	_velocity = 100.f;
	_realWidth = 0;
	_realHeight = 0;
	_direction = Direction::STOP;
	_movingVector.setXY(0.0f, 0.0f);
}


Pacman::~Pacman(void)
{
}

void Pacman::setLife(int life)
{
	if(life >= 0 && life<=3)
		_life = life;
	else
		std::cout<<"[]Pacman.h - wrong life number. life = "<<life<<std::endl;
}

int	 Pacman::getLife() const
{
	return _life;
}

void Pacman::setScore(int score)
{
	_score = score;
}

int  Pacman::getScore() const
{
	return _score;
}

void Pacman::setRealWidth(int width)
{
	_realWidth = width;
}

int  Pacman::getRealWidth() const
{
	return _realWidth;
}

void Pacman::setRealHeight(int height)
{
	_realHeight = height;
}

int  Pacman::getRealHeight() const
{
	return _realHeight;
}

void Pacman::setMovingVector()
{
	_movingVector.setXY(0.0f, 0.0f);

	switch(_direction)
	{
		case Direction::UP:
			_movingVector.y -= _velocity;
			break;

		case Direction::DOWN:
			_movingVector.y += _velocity;
			break;

		case Direction::LEFT:
			_movingVector.x -= _velocity;
			break;

		case Direction::RIGHT:
			_movingVector.x += _velocity;
			break;

		case Direction::STOP:
			_movingVector.setXY(0.0f, 0.0f);
			break;

	}
}