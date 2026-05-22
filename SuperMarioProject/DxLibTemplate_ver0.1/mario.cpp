#include "mario.h"
#include"componentGravity.h"
#include"componentCollision.h"
#include"componentRenderable.h"

Mario::Mario(int id, Circle cir) : Object(id)
{
	this->addComponent<ComponentCollisionCircle>(id, cir);
	this->addComponent<ComponentGravity>(id);
	this->addComponent<ComponentRenderableCircle>(id,0.5f, cir);

	moveStateMachine.addState(MOVESTATE::MOV_WALK, nullptr, &Mario::walk, nullptr);
	moveStateMachine.addState(MOVESTATE::MOV_DASH, nullptr, &Mario::dash, nullptr);
	moveStateMachine.addState(MOVESTATE::MOV_JUMP, nullptr, &Mario::jump, nullptr);

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
}

void Mario::walk()
{
	Float2 vec(0.0f, 0.0f);
	if (KeyManager::checkHitKey(KEY_INPUT_W))
	{
		vec.y = 1.0f;
	}
	if (KeyManager::checkHitKey(KEY_INPUT_A))
	{
		vec.x = -1.0f;
	}
	if (KeyManager::checkHitKey(KEY_INPUT_S))
	{
		vec.y = -1.0f;
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
