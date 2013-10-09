#ifndef PACMAN_STATICOBJECT_H
#define	PACMAN_STATICOBJECT_H

#include "gameobject.h"

class StaticObject :
	public GameObject
{
public:
	void	 setType(Type::Id type);
	Type::Id getType() const;

public:
	StaticObject(void);
	~StaticObject(void);

private:
	Type::Id _type;
};

#endif