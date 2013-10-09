#ifndef PACMAN_ENUMS_H
#define	PACMAN_ENUMS_H

namespace Textures
{
	enum Id
	{
		WALL = 0,
		PILL,
		BONUS,
		PACMAN,
		GHOST
	};
}

namespace Direction
{
	enum Id
	{
		UP = 0,
		DOWN,
		LEFT,
		RIGHT,
		STOP
	};
}

namespace Type
{
	enum Id
	{
		WALL = 0,
		PILL,
		BONUS,
		NOTHING
	};
}
#endif