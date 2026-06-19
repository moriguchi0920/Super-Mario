#include "goal.h"
#include"componentRenderable.h"
#include"componentTransform.h"
#include"objectManager.h"
#include"collisionManager.h"
#include"collisionInfo.h"

Goal::Goal(const Rect& rect) : Object(ObjectManager::makeId())
{
	this->addComponent<ComponentTransform>(this->id);
	auto transform = this->getComponent<ComponentTransform>().lock();

	if (transform)
	{
		transform->setScroll(true); 
		transform->setPosition(rect.begin);
	}



	int goalImage = LoadGraph("Stage/Goal_1_1.png");
	auto renderImage = addComponent<ComponentRenderableImage>(id, ComponentRenderable::PRIORITY_DEFAULT, goalImage);

	auto renderable = this->getComponent<ComponentRenderableImage>().lock();
	if (renderable && transform)
	{
		renderable->bindToTransform(transform);
	}
}

Goal::~Goal()
{
}

void Goal::update()
{

	auto renderable = this->getComponent<ComponentRenderableImage>().lock();
	if (renderable)
	{
		renderable->syncFromTransform();
	}




}
