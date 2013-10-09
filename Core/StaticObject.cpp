#include "StaticObject.h"


StaticObject::StaticObject(void)
{
}


StaticObject::~StaticObject(void)
{
}

void StaticObject::setType(Type::Id type)
{
	_type = type;
}

Type::Id StaticObject::getType() const
{
	return _type;
}