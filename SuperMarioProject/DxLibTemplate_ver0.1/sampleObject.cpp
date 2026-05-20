#include "sampleObject.h"
#include"componentRenderable.h"
#include"componentTransform.h"

SampleObject::SampleObject() : Object(ObjectManager::makeId())
{
	this->addComponent<ComponentTransform>(this->id);
	this->addComponent<ComponentRenderableCircle>(this->id, 0.5f, Point(100.0f, 100.0f), 10.0f);
}

SampleObject::~SampleObject()
{
}

void SampleObject::update()
{
	auto transform = this->getComponent<ComponentTransform>().lock();

	transform->translate(Float2(1.0f, 1.0f), 2.0f);
	this->getComponent<ComponentRenderableCircle>().lock()->set(transform->getPosition(), 10.0f);

}
