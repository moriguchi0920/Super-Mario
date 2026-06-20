#include "blockBase.h"
#include"componentCollision.h"
#include"componentRenderable.h"
#include"componentTransform.h"
#include"objectManager.h"
#include"collisionManager.h"

BlockBase::BlockBase(const Rect& rect) : Object(ObjectManager::makeId())
{
	this->addComponent<ComponentTransform>(this->id);
	auto transform = getComponent<ComponentTransform>();
	transform.lock()->setPosition(rect.begin);
	this->addComponent<ComponentCollisionRect>(this->id, rect);

}

BlockBase::~BlockBase()
{
}

void BlockBase::update()
{
	auto comCR = getComponent<ComponentCollisionRect>();
	auto comT = getComponent<ComponentTransform>();

	
}

void BlockBase::eventProc(int from, std::string name, std::vector<Event::DataMap> datas)
{
}

void BlockBase::hitFromBottom()
{
}
