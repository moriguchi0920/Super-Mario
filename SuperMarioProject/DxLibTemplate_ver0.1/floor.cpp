#include "floor.h"
#include"objectManager.h"
#include"componentCollision.h"
#include"componentRenderable.h"
#include"componentTransform.h"
#include"const.h"

Floor::Floor(float x, float width) : BlockBase(Rect(Point(x, FLOOR_BASE_Y), Point(width, WINDOW_HEIGHT)))
{
	addComponent<ComponentTransform>(id).lock()->setScroll(true);
	auto comT = getComponent<ComponentTransform>();
	comT.lock()->setPosition(Point(x, FLOOR_BASE_Y));
	auto transform = this->getComponent<ComponentTransform>().lock();
	if (transform)
	{
		transform->setScroll(true);
		transform->setPosition(g_nextPos);
	}

	int imgHandle = 0;


	if (g_nextType == Ground1)
	{
		imgHandle = LoadGraph("Stage/Ground_1.png");
	}
	else if (g_nextType == Ground2)
	{
		imgHandle = LoadGraph("Stage/Ground_2.png");
	}
	else if (g_nextType == Ground3)
	{
		imgHandle = LoadGraph("Stage/Ground_3.png");
	}
	else if (g_nextType == Ground4)
	{
		imgHandle = LoadGraph("Stage/Ground_4.png");
	}



	Rect rect(Point(x, FLOOR_BASE_Y),Point(width, WINDOW_HEIGHT));
	getComponent<ComponentCollisionRect>().lock()->addTag(ICollisionTag::FLOOR);

	addComponent<ComponentRenderableRect>(this->id,ComponentRenderable::PRIORITY_DEFAULT,  rect);

	auto comR = getComponent<ComponentRenderableRect>();

	comR.lock()->setColor(128, 64, 32);
}

Floor::~Floor()
{
}

void Floor::update()
{
	BlockBase::update();
	auto comR = getComponent<ComponentRenderableRect>();
	auto comC = getComponent<ComponentCollisionRect>();

	comR.lock()->syncFromTransform();
	comC.lock()->update();
}
