#include"scrollManager.h"
#include"componentManager.h"
#include"componentTransform.h"
#include"componentGravity.h"


ScrollManager* ScrollManager::getInstance()
{
	static ScrollManager instance;
	return &instance;
}

void ScrollManager::scrollAll()
{
}

void ScrollManager::setScrollOffset(float offset)
{
}

void ScrollManager::setStandard(Float2* pos)
{
}
