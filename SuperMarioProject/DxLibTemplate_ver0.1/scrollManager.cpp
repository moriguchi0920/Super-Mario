#include"scrollManager.h"
#include"componentManager.h"
#include"componentTransform.h"
#include"componentGravity.h"
#include"const.h"
#include<vector>
#include<memory>

ScrollManager::ScrollManager()
{
	scrollOffset = 0.0f;

}

ScrollManager* ScrollManager::getInstance()
{
	static ScrollManager instance;
	return &instance;
}

void ScrollManager::scrollAll()
{
	ComponentManager* pComManager = ComponentManager::getInstance();
	std::vector<std::weak_ptr<ComponentTransform>> vector = pComManager->getComponentsByBase<ComponentTransform>();

	for (auto& comT : vector)
	{
		if (!comT.expired())
		{
			if (comT.lock()->getIsScroll())
			{
				comT.lock()->translate(Point(1.0f, 0.0f), scrollOffset);
			}
		}
	}

}

void ScrollManager::setScrollOffset(float offset)
{
	scrollOffset = offset;
}

