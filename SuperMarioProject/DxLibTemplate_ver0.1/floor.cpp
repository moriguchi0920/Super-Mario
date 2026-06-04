#include "floor.h"
#include"objectManager.h"
#include"componentCollision.h"
#include"componentRenderable.h"
#include"componentTransform.h"
#include"const.h"

Floor::Floor(float x, float width): Object(ObjectManager::makeId())
{
	addComponent<ComponentTransform>(id).lock()->setScroll(true);
	auto comT = getComponent<ComponentTransform>();
	comT.lock()->setPosition(Point(x, FLOOR_BASE_Y));


	Rect rect(Point(x, FLOOR_BASE_Y),Point(width, WINDOW_HEIGHT));
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
