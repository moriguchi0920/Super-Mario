#include "background.h"
#include "componentTransform.h"
#include "componentRenderable.h"
#include "imageManager.h"

Background::Type Background::g_nextType = Background::CLOUD_1;
Float2 Background::g_nextPos = Float2(0.0f, 0.0f);

Background::Background() : Object(ObjectManager::makeId())
{
	this->addComponent<ComponentTransform>(this->id);
	auto transform = this->getComponent<ComponentTransform>().lock();

	if (transform)
	{
		transform->setScroll(true);
		transform->setPosition(g_nextPos);
	}

	int imgHandle = 0;


	if (g_nextType == CLOUD_1)
	{
		imgHandle = LoadGraph("Stage/Cloud_1.png");
	}
	else if(g_nextType == CLOUD_2)
	{
		imgHandle = LoadGraph("Stage/Cloud_2.png");
	}
	else if (g_nextType == CLOUD_3)
	{
		imgHandle = LoadGraph("Stage/Cloud_3.png");
	}
	else if (g_nextType == MOUNTAIN_1)
	{
		imgHandle = LoadGraph("Stage/Background_Mountain_1.png");
	}

	else if (g_nextType == MOUNTAIN_2)
	{
		imgHandle = LoadGraph("Stage/Background_Mountain_2.png");
	}
	else if (g_nextType == PLANT_1)
	{
		imgHandle = LoadGraph("Stage/Background_Plant_1.png");
	}
	else if (g_nextType == PLANT_2)
	{
		imgHandle = LoadGraph("Stage/Background_Plant_2.png");
	}
	else if (g_nextType == PLANT_3)
	{
		imgHandle = LoadGraph("Stage/Background_Plant_3.png");
	}
	else if (g_nextType == CASTLE)
	{
		imgHandle = LoadGraph("Stage/Castle.png");
	}

	this->addComponent<ComponentRenderableImage>(this->id, ComponentRenderable::PRIORITY_MIN, imgHandle);

	auto renderable = this->getComponent<ComponentRenderableImage>().lock();
	if (renderable && transform) { renderable->bindToTransform(transform); }
}

Background::~Background()
{
}

void Background::update()
{
	auto renderable = this->getComponent<ComponentRenderableImage>().lock();
	if (renderable)
	{
		renderable->syncFromTransform();
	}


}
