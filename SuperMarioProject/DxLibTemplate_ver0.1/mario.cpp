#include "mario.h"
#include"componentGravity.h"
#include"componentCollision.h"
#include"componentRenderable.h"
#include"collisionManager.h"
#include"floor.h"
#include"objectManager.h"

Mario::Mario() : Object(ObjectManager::makeId())
{
	Circle cir(Point(0, 0), MARIO_RADIUS);

	this->addComponent<ComponentGravity>(id);
	auto transformG = this->getComponent<ComponentGravity>().lock();
	transformG->setLanding(false);

	this->addComponent<ComponentCollisionCircle>(id, cir).lock()->addTag(ICollisionTag::MARIO);

	Circle cirTop(Point(0, 0 - MARIO_RADIUS), MARIO_COL_TOP_RADIUS);
	this->addComponent<ComponentCollisionCircle>(id, cirTop);

	

	this->addComponent<ComponentRenderableCircle>(id,0.5f, cir);



	moveStateMachine.addState(MOVESTATE::MOV_WALK, nullptr, &Mario::walk, nullptr);
	moveStateMachine.addState(MOVESTATE::MOV_DASH, nullptr, &Mario::dash, nullptr);
	moveStateMachine.addState(MOVESTATE::MOV_JUMP, nullptr, &Mario::jump, nullptr);
	moveStateMachine.changeState(MOVESTATE::MOV_WALK);

	varyStateMachine.addState(VARYSTATE::VARY_DEFAULT, &Mario::defaultStateInit, &Mario::defaultStateUpdate, nullptr);
	varyStateMachine.addState(VARYSTATE::VARY_TALL, &Mario::tallStateInit, &Mario::tallStateUpdate, nullptr);
	varyStateMachine.addState(VARYSTATE::VARY_FIRE, &Mario::fireBallStateInit, &Mario::fireBallStateUpdate, nullptr);

	starStateMachine.addState(STARSTATE::STAR_DEFAULT, nullptr, nullptr, nullptr);
	starStateMachine.addState(STARSTATE::STAR_INVINCIBLE, nullptr, &Mario::starStateUpdate, nullptr);

}

Mario::~Mario()
{



}

void Mario::update()
{
	moveStateMachine.update(this);
	varyStateMachine.update(this);
	starStateMachine.update(this);

	auto comCC = getComponent<ComponentCollisionCircle>();
	auto comT = getComponent<ComponentGravity>();
	auto comR = getComponent<ComponentRenderableCircle>();
	comT.lock()->gravityUpdate();

	comR.lock()->syncFromTransform();

	if (comCC.lock())
	{
		comCC.lock()->syncFromTransform();
		if (comCC.lock()->getEnterByTag(ICollisionTag::FLOOR))
		{
			comT.lock()->setLanding(true);
		}
		
	}
	
}

void Mario::walk()
{
	Float2 vec(0.0f, 0.0f);
	if (KeyManager::checkHitKey(KEY_INPUT_A))
	{
		vec.x = -1.0f;
	}
	if (KeyManager::checkHitKey(KEY_INPUT_D))
	{
		vec.x = 1.0f;
	}

	auto comG = this->getComponent<ComponentGravity>();

	comG.lock()->translate(vec, 2.0f);

}

void Mario::jump()
{
}

void Mario::dash()
{
}

void Mario::starStateUpdate()
{
}

void Mario::defaultStateInit()
{
}

void Mario::defaultStateUpdate()
{
}

void Mario::tallStateInit()
{
}

void Mario::tallStateUpdate()
{
}

void Mario::fireBallStateInit()
{
}

void Mario::fireBallStateUpdate()
{
}
