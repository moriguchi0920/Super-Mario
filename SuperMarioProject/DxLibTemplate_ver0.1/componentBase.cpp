#include"componentBase.h"

Component::Component(int id)
{
	entityId = id;
}

int Component::getParentId()
{
	return entityId;
}



Component::~Component()
{
}

