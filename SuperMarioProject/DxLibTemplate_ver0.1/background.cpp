#include "background.h"
#include "componentTransform.h"
#include "componentRenderable.h"
#include "imageManager.h"

Background::Background() : Object(ObjectManager::makeId())
{
	this->addComponent<ComponentTransform>(this->id, Point(0.0f, 0.0f));
	

	auto transform = this->getComponent<ComponentTransform>().lock();
	
}

Background::~Background()
{
}

void Background::update()
{
	auto transformG = this->getComponent<ComponentGravity>().lock();

	transformG->gravityUpdate();
	transformG->translate(Float2(1.0f, 0.0f), 2.0f);
	this->getComponent<ComponentRenderableCircle>().lock()->set(transformG->getPosition(), 10.0f);




}
