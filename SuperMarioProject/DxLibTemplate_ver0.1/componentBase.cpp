#include"componentBase.h"

Component::Component(int id)
{
	entityId = id;
	isActive = true;
}

int Component::getParentId()
{
	return entityId;
}

bool Component::getIsActive()
{
	return isActive;
}

void Component::setActive(bool active)
{
	isActive = active;
}



Component::~Component()
{
}

