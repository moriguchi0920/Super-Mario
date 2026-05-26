#include "mario.h"
#include"componentGravity.h"
#include"componentCollision.h"
#include"componentRenderable.h"
#include"collisionManager.h"
#include"floor.h"
#include"objectManager.h"

Mario::Mario() : Object(ObjectManager::makeId())
{
	Rect rect(Point(0, 0), Point(MARIO_SIZE, MARIO_SIZE));

	this->addComponent<ComponentGravity>(id);
	auto transformG = this->getComponent<ComponentGravity>().lock();
	transformG->setLanding(false);
	transformG->setSpeed(1.0f);

	this->addComponent<ComponentCollisionRect>(id, rect).lock()->addTag(ICollisionTag::MARIO);

	//Circle cirTop(Point(0, 0 - MARIO_RADIUS), MARIO_COL_TOP_RADIUS);
	//this->addComponent<ComponentCollisionCircle>(id, cirTop).lock()->addTag(ICollisionTag::MARIO);

	

	this->addComponent<ComponentRenderableRect>(id,0.5f, rect);



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


	auto comCR = getComponent<ComponentCollisionRect>();
	auto comG = getComponent<ComponentGravity>();
	auto comR = getComponent<ComponentRenderableRect>();


	comR.lock()->syncFromTransform();

	if (comCR.lock())
	{
		comCR.lock()->syncFromTransform();
		if (comCR.lock()->getEnterByTag(ICollisionTag::FLOOR))
		{
			comG.lock()->setLanding(true);
			comG.lock()->setBaseY(FLOOR_BASE_Y - MARIO_SIZE);
		}
		
	}
	comG.lock()->gravityUpdate();

	if (comG.lock()->getLanding())
	{
		if (KeyManager::pushHitKey(KEY_INPUT_SPACE))
		{
			moveStateMachine.changeState(MOVESTATE::MOV_JUMP);
			comG.lock()->setTranslation(Float2(comG.lock()->getTranslation().x, JUMP_FIRST_SPEED));
			comG.lock()->setLanding(false);
			
		}
		else if (KeyManager::checkHitKey(KEY_INPUT_LSHIFT))
		{

			moveStateMachine.changeState(MOVESTATE::MOV_DASH);
		}
		else
		{

			moveStateMachine.changeState(MOVESTATE::MOV_WALK);
		}

	}


	moveStateMachine.update(this);
	varyStateMachine.update(this);
	starStateMachine.update(this);


}

void Mario::walk()
{
	Float2 vec(0.0f, 0.0f);
	if (KeyManager::checkHitKey(KEY_INPUT_A))
	{
		vec.x = -MARIO_WALK_SPEED;
	}
	if (KeyManager::checkHitKey(KEY_INPUT_D))
	{
		vec.x = MARIO_WALK_SPEED;
	}

	auto comG = this->getComponent<ComponentGravity>();

	if (!comG.expired())
	{
		comG.lock()->setTranslation(vec);
		comG.lock()->translate();
	}
	

}

void Mario::jump()
{
	auto comG = getComponent<ComponentGravity>();
	if (!comG.expired())
	{
		comG.lock()->translate();
	}

}

void Mario::dash()
{
	Float2 vec(0.0f, 0.0f);
	if (KeyManager::checkHitKey(KEY_INPUT_A))
	{
		vec.x = -MARIO_DASH_SPEED;
	}
	if (KeyManager::checkHitKey(KEY_INPUT_D))
	{
		vec.x = MARIO_DASH_SPEED;
	}

	auto comG = this->getComponent<ComponentGravity>();

	if (!comG.expired())
	{
		comG.lock()->setTranslation(vec);
		comG.lock()->translate();
	}
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
