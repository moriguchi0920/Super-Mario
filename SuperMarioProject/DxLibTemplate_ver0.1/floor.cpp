#include "floor.h"
#include"objectManager.h"
#include"componentCollision.h"
#include"componentRenderable.h"
#include"componentTransform.h"
#include"const.h"

Floor::Floor() : Object(ObjectManager::makeId())
{
	addComponent<ComponentTransform>(id).lock()->setScroll(true);
	auto comT = getComponent<ComponentTransform>();
	comT.lock()->setPosition(Point(0, FLOOR_BASE_Y));


	Rect rect(Point(0, FLOOR_BASE_Y), Point(WINDOW_WIDTH, WINDOW_HEIGHT));
	addComponent<ComponentCollisionRect>(this->id, rect).lock()->addTag(ICollisionTag::FLOOR);

	addComponent<ComponentRenderableRect>(this->id,0.5,  rect);

	auto comR = getComponent<ComponentRenderableRect>();

	comR.lock()->setColor(128, 64, 32);
}

Floor::~Floor()
{
}

void Floor::update()
{
	auto comR = getComponent<ComponentRenderableRect>();
	auto comC = getComponent<ComponentCollisionRect>();

	comR.lock()->syncFromTransform();
	comC.lock()->update();
}
