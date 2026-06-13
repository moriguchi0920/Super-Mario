#include "goal.h"
#include"componentRenderable.h"
#include"componentTransform.h"
#include"objectManager.h"
#include"collisionManager.h"
#include"collisionInfo.h"

Goal::Goal(const Rect& rect) : Object(ObjectManager::makeId())
{
	this->addComponent<ComponentTransform>(this->id);
	auto transform = this->getComponent<ComponentTransform>();
	transform.lock()->setPosition(rect.begin);
	
	this->addComponent<ComponentCollisionRect>(this->id, rect);
}

Goal::~Goal()
{
}

void Goal::update()
{




}
