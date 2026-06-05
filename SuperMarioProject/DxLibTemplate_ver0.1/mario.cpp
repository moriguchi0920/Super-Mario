#include "mario.h"
#include"componentGravity.h"
#include"componentCollision.h"
#include"componentRenderable.h"
#include"collisionManager.h"
#include"floor.h"
#include"objectManager.h"
#include"scrollManager.h"

Mario::Mario() : Object(ObjectManager::makeId())
{
	Rect rect(Point(0, 0), Point(MARIO_SIZE, MARIO_SIZE));

	this->addComponent<ComponentGravity>(id);
	auto transformG = this->getComponent<ComponentGravity>().lock();
	transformG->setLanding(false);
	transformG->setSpeed(1.0f);

	jumpTranslationY = JUMP_FIRST_SPEED;
	jumpHoldCount = 0;

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

	// コンポーネント取得
	auto comCR = getComponent<ComponentCollisionRect>();
	auto comG = getComponent<ComponentGravity>();
	auto comR = getComponent<ComponentRenderableRect>();


	// 重力更新
	comG.lock()->gravityUpdate();


	// 接地しているときのダッシュ、ジャンプ切り替え処理
	if (comG.lock()->getLanding())
	{
		if (KeyManager::pushHitKey(KEY_INPUT_SPACE))
		{
			jumpHoldCount = 0;
			jumpTranslationY = JUMP_FIRST_SPEED;
			moveStateMachine.changeState(MOVESTATE::MOV_JUMP);
			comG.lock()->setTranslation(Float2(comG.lock()->getTranslation().x, jumpTranslationY));
			comG.lock()->setLanding(false);
			
		}
		else if (KeyManager::checkHitKey(KEY_INPUT_LSHIFT))
		{

			moveStateMachine.changeState(MOVESTATE::MOV_DASH);
			comG.lock()->setTranslation(Float2(comG.lock()->getTranslation().x, 0.0f));
		}
		else
		{

			moveStateMachine.changeState(MOVESTATE::MOV_WALK);
			comG.lock()->setTranslation(Float2(comG.lock()->getTranslation().x, 0.0f));
		}

	}


	moveStateMachine.update(this);
	varyStateMachine.update(this);
	starStateMachine.update(this);


	// 描画の座標更新
	comR.lock()->syncFromTransform();

	// 当たり判定座標更新と当たった時の処理
	// 当たり判定更新
	if (comCR.lock())
	{
		comCR.lock()->update();

		if (comCR.lock()->getEnterByTag(ICollisionTag::FLOOR))
		{
			comG.lock()->setLanding(true);

			// ★ここだけ：1回だけ補正
			comG.lock()->setPosition(
				Point(comG.lock()->getPosition().x, FLOOR_BASE_Y - MARIO_SIZE)
			);
		}

		if (!comCR.lock()->getStayByTag(ICollisionTag::FLOOR))
		{
			comG.lock()->setLanding(false);
		}
	}
}

void Mario::walk()
{

	auto comG = this->getComponent<ComponentGravity>();

	if (!comG.expired())
	{
		if (KeyManager::checkHitKey(KEY_INPUT_A))
		{
			if (-MARIO_WALK_SPEED_MAX < comG.lock()->getTranslation().x)
			{
				comG.lock()->addTranslation(Float2(-MARIO_WALK_ACCELERATION, 0.0f));
			}
		}
		else if (comG.lock()->getTranslation().x < 0.0f)
		{
			comG.lock()->addTranslation(Float2(MARIO_WALK_ACCELERATION, 0.0f));
		}
		if (KeyManager::checkHitKey(KEY_INPUT_D))
		{
			if (comG.lock()->getTranslation().x < MARIO_WALK_SPEED_MAX)
			{
				comG.lock()->addTranslation(Float2(MARIO_WALK_ACCELERATION, 0.0f));
			}

		}
		else if (0.0f < comG.lock()->getTranslation().x)
		{
			comG.lock()->addTranslation(Float2(-MARIO_WALK_ACCELERATION, 0.0f));
		}

		if (fabsf(comG.lock()->getTranslation().x) <= 0.1)
		{
			comG.lock()->setTranslation(Point(0.0f, 0.0f));
		}


		comG.lock()->translate();
		if (WINDOW_WIDTH / 2 <= comG.lock()->getPosition().x + SPRITE_SIZE / 2)
		{
			comG.lock()->setPosition(Point(WINDOW_WIDTH / 2.0f - SPRITE_SIZE / 2, comG.lock()->getPosition().y));
			ScrollManager::getInstance()->setScrollOffset(-comG.lock()->getTranslation().x);
		}
		else
		{
			ScrollManager::getInstance()->setScrollOffset(0.0f);
		}
	}


}

void Mario::jump()
{
	if (KeyManager::checkHitKey(KEY_INPUT_SPACE) && jumpHoldCount <= 30)
	{
		jumpHoldCount++;
	}
	else
	{
		if (jumpTranslationY <= 0)
		{
			jumpTranslationY += 0.35;
		}
		
	}

	auto comG = getComponent<ComponentGravity>();
	if (!comG.expired())
	{
		comG.lock()->setTranslation(Float2(comG.lock()->getTranslation().x, jumpTranslationY));
		comG.lock()->translate();
		if (WINDOW_WIDTH / 2 <= comG.lock()->getPosition().x + SPRITE_SIZE / 2)
		{
			comG.lock()->setPosition(Point(WINDOW_WIDTH / 2.0f - SPRITE_SIZE / 2, comG.lock()->getPosition().y));
			ScrollManager::getInstance()->setScrollOffset(-comG.lock()->getTranslation().x);
		}
		else
		{
			ScrollManager::getInstance()->setScrollOffset(0.0f);
		}
	}

}

void Mario::dash()
{

	auto comG = this->getComponent<ComponentGravity>();

	if (!comG.expired())
	{
		if (KeyManager::checkHitKey(KEY_INPUT_A))
		{
			if (-MARIO_DASH_SPEED_MAX <= comG.lock()->getTranslation().x)
			{
				comG.lock()->addTranslation(Float2(-MARIO_DASH_ACCELERATION, 0.0f));
			}
		}
		else if (comG.lock()->getTranslation().x < 0.0f)
		{
			comG.lock()->addTranslation(Float2(MARIO_DASH_ACCELERATION, 0.0f));
		}
		if (KeyManager::checkHitKey(KEY_INPUT_D))
		{
			if (comG.lock()->getTranslation().x <= MARIO_DASH_SPEED_MAX)
			{
				comG.lock()->addTranslation(Float2(MARIO_DASH_ACCELERATION, 0.0f));
			}

		}
		else if (0.0f < comG.lock()->getTranslation().x)
		{
			comG.lock()->addTranslation(Float2(-MARIO_DASH_ACCELERATION, 0.0f));
		}


		if (fabsf(comG.lock()->getTranslation().x) <= 0.1)
		{
			comG.lock()->setTranslation(Point(0.0f, 0.0f));
		}


		comG.lock()->translate();
		if (WINDOW_WIDTH / 2 <= comG.lock()->getPosition().x + SPRITE_SIZE / 2)
		{
			comG.lock()->setPosition(Point(WINDOW_WIDTH / 2.0f - SPRITE_SIZE / 2, comG.lock()->getPosition().y));
			ScrollManager::getInstance()->setScrollOffset(-comG.lock()->getTranslation().x);
		}
		else
		{
			ScrollManager::getInstance()->setScrollOffset(0.0f);
		}
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
