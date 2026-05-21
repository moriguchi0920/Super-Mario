#include "sampleObject.h"
#include"componentRenderable.h"
#include"componentTransform.h"
#include"componentGravity.h"

SampleObject::SampleObject() : Object(ObjectManager::makeId())
{
	this->addComponent<ComponentGravity>(this->id);
	this->addComponent<ComponentRenderableCircle>(this->id, 0.5f, Point(100.0f, 100.0f), 10.0f);
	auto transformG = this->getComponent<ComponentGravity>().lock();
	transformG->setLanding(false);
}

SampleObject::~SampleObject()
{
}

void SampleObject::update()
{
	auto transformG = this->getComponent<ComponentGravity>().lock();

	transformG->gravityUpdate();
	transformG->translate(Float2(1.0f, 0.0f), 2.0f);
	this->getComponent<ComponentRenderableCircle>().lock()->set(transformG->getPosition(), 10.0f);




}
