#include "coin.h" 
#include "objectManager.h"
#include "collisionManager.h"
#include "componentTransform.h" 
#include "componentRenderable.h" 
#include "const.h"             

Coin::Coin(Rect rect) : Object(ObjectManager::makeId())
{
	
	int coinImage = LoadGraph("Item/Coin2-1.png");

	this->addComponent<ComponentGravity>(id);
	auto transformG = this->getComponent<ComponentGravity>().lock();
	transformG->setPosition(rect.begin);
	transformG->setLanding(false);
	transformG->setSpeed(0.0f);
	transformG->setScroll(true);

	transformG->setTranslation(Float2(0.0f, -6.0f));

	
	auto renderImage = this->addComponent<ComponentRenderableImage>(id, ComponentRenderable::PRIORITY_DEFAULT, coinImage);

	
	if (transformG && !renderImage.expired())
	{
		renderImage.lock()->bindToTransform(transformG);
	}
}

Coin::~Coin()
{
}

void Coin::update()
{
	auto transformG = getComponent<ComponentGravity>();
	auto comR = getComponent<ComponentRenderableImage>();

	transformG.lock()->gravityUpdate();
	transformG.lock()->translate();

	auto vel = transformG.lock()->getTranslation();
	if (vel.y > 2.0f)
	{
		die();
	}

	
	if (!comR.expired())
	{
		comR.lock()->syncFromTransform();

		float offset = SPRITE_SIZE / 2.0f;

		if (!transformG.expired())
		{
			Float2 basePos = transformG.lock()->getPosition();
			comR.lock()->setPos(Float2(basePos.x + offset, basePos.y + offset));
		}
	}
}

void Coin::eventProc(int from, std::string name, std::vector<Event::DataMap> datas) {}
void Coin::activateProc() {}
void Coin::deactivateProc() {}
void Coin::deathProc() {}