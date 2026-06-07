#include "mario.h"
#include"componentGravity.h"
#include"componentCollision.h"
#include"componentRenderable.h"
#include"collisionManager.h"
#include"floor.h"
#include"objectManager.h"
#include"scrollManager.h"
#include"DxLib.h"


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
	auto colRect = getComponent<ComponentCollisionRect>();
	auto transformG = getComponent<ComponentGravity>();
	auto renderRect = getComponent<ComponentRenderableRect>();


	// 重力更新
	transformG.lock()->gravityUpdate();


	// 接地しているときのダッシュ、ジャンプ切り替え処理
	if (transformG.lock()->getLanding())
	{
		if (KeyManager::pushHitKey(KEY_INPUT_SPACE))
		{
			jumpHoldCount = 0;
			jumpTranslationY = JUMP_FIRST_SPEED;
			moveStateMachine.changeState(MOVESTATE::MOV_JUMP);
			transformG.lock()->setTranslation(Float2(transformG.lock()->getTranslation().x, jumpTranslationY));
			transformG.lock()->setLanding(false);
			
		}
		else if (KeyManager::checkHitKey(KEY_INPUT_LSHIFT))
		{

			moveStateMachine.changeState(MOVESTATE::MOV_DASH);
			transformG.lock()->setTranslation(Float2(transformG.lock()->getTranslation().x, 0.0f));
		}
		else
		{

			moveStateMachine.changeState(MOVESTATE::MOV_WALK);
			transformG.lock()->setTranslation(Float2(transformG.lock()->getTranslation().x, 0.0f));
		}

	}


	moveStateMachine.update(this);
	varyStateMachine.update(this);
	starStateMachine.update(this);


	// 描画の座標更新
	renderRect.lock()->syncFromTransform();

	// 当たり判定座標更新と当たった時の処理
	// 当たり判定更新
	if (colRect.lock())
	{
		colRect.lock()->update();
		for (auto& colInfo : colRect.lock()->getInfo())
		{
			if (!colInfo.expired())
			{
				auto colInfoSp = colInfo.lock();
				if (!colInfoSp->getTarget(id).expired())
				{
					int side = colInfoSp->getRectCollideSide();
					if (colInfoSp->getObjectIdCol1() != id)
					{
						if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_LEFT) side = ContactInfo::RECTCOLLIDESIDE::SIDE_RIGHT;
						else if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_RIGHT) side = ContactInfo::RECTCOLLIDESIDE::SIDE_LEFT;
						else if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_TOP) side = ContactInfo::RECTCOLLIDESIDE::SIDE_BOTTOM;
						else if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_BOTTOM) side = ContactInfo::RECTCOLLIDESIDE::SIDE_TOP;
					}
					
					switch (colInfoSp->getTarget(id).lock()->getTag()->tag)
					{
					case ICollisionTag::FLOOR:
					{
						if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_TOP)
						{
							auto targetShape = colInfoSp->getTarget(id).lock();
							auto targetRectComp = std::dynamic_pointer_cast<ComponentCollisionRect>(targetShape);
							if (targetRectComp)
							{
								Rect trect = targetRectComp->get();
								transformG.lock()->setPosY(trect.begin.y - MARIO_SIZE);
								auto cur = transformG.lock()->getTranslation();
								transformG.lock()->setTranslation(Float2(cur.x,0.0f));

									transformG.lock()->setLanding(true);

								
							}
						}
						break;
					}
					case ICollisionTag::BLOCK:
					{
						if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_TOP)
						{
							auto targetShape = colInfoSp->getTarget(id).lock();
							auto targetRectComp = std::dynamic_pointer_cast<ComponentCollisionRect>(targetShape);
							if (targetRectComp)
							{
								Rect trect = targetRectComp->get();
								transformG.lock()->setPosY(trect.begin.y - MARIO_SIZE);
								auto cur = transformG.lock()->getTranslation();
								transformG.lock()->setTranslation(Float2(cur.x,0.0f));

									transformG.lock()->setLanding(true);

							}
						}
						else if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_BOTTOM)
						{
							auto targetShape = colInfoSp->getTarget(id).lock();
							auto targetRectComp = std::dynamic_pointer_cast<ComponentCollisionRect>(targetShape);
							if (targetRectComp)
							{
								Rect trect = targetRectComp->get();
								transformG.lock()->setPosY(trect.begin.y + trect.size.y);
								auto cur = transformG.lock()->getTranslation();
								transformG.lock()->setTranslation(Float2(cur.x,0.0f));
							}
						}
						else if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_LEFT)
						{
							auto targetShape = colInfoSp->getTarget(id).lock();
							auto targetRectComp = std::dynamic_pointer_cast<ComponentCollisionRect>(targetShape);
							if (targetRectComp)
							{
								Rect trect = targetRectComp->get();
								transformG.lock()->setPosX(trect.begin.x + trect.size.x);
								auto cur = transformG.lock()->getTranslation();
								transformG.lock()->setTranslation(Float2(0.0f, cur.y));
							}
						}
						else if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_RIGHT)
						{
							auto targetShape = colInfoSp->getTarget(id).lock();
							auto targetRectComp = std::dynamic_pointer_cast<ComponentCollisionRect>(targetShape);
							if (targetRectComp)
							{
								Rect trect = targetRectComp->get();
								transformG.lock()->setPosX(trect.begin.x - MARIO_SIZE);
								auto cur = transformG.lock()->getTranslation();
								transformG.lock()->setTranslation(Float2(0.0f, cur.y));
							}
						}
						break;
					}
					}
				}
			}
		}
	}
}

void Mario::eventProc(int from, std::string name, std::vector<Event::DataMap> datas)
{


}

void Mario::walk()
{

	auto transformG = this->getComponent<ComponentGravity>();

	if (!transformG.expired())
	{
		if (KeyManager::checkHitKey(KEY_INPUT_A))
		{
			if (-MARIO_WALK_SPEED_MAX < transformG.lock()->getTranslation().x)
			{
				transformG.lock()->addTranslation(Float2(-MARIO_WALK_ACCELERATION, 0.0f));
			}
		}
		else if (transformG.lock()->getTranslation().x < 0.0f)
		{
			transformG.lock()->addTranslation(Float2(MARIO_WALK_ACCELERATION, 0.0f));
		}
		if (KeyManager::checkHitKey(KEY_INPUT_D))
		{
			if (transformG.lock()->getTranslation().x < MARIO_WALK_SPEED_MAX)
			{
				transformG.lock()->addTranslation(Float2(MARIO_WALK_ACCELERATION, 0.0f));
			}

		}
		else if (0.0f < transformG.lock()->getTranslation().x)
		{
			transformG.lock()->addTranslation(Float2(-MARIO_WALK_ACCELERATION, 0.0f));
		}

		if (fabsf(transformG.lock()->getTranslation().x) <= 0.05f)
		{
			auto cur = transformG.lock()->getTranslation();
			transformG.lock()->setTranslation(Float2(0.0f, cur.y));
		}


		transformG.lock()->translate();
		if (WINDOW_WIDTH / 2 <= transformG.lock()->getPosition().x + SPRITE_SIZE / 2)
		{
			transformG.lock()->setPosition(Point(WINDOW_WIDTH / 2.0f - SPRITE_SIZE / 2, transformG.lock()->getPosition().y));
			ScrollManager::getInstance()->setScrollOffset(-transformG.lock()->getTranslation().x);
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

	auto transformG = getComponent<ComponentGravity>();
	if (!transformG.expired())
	{
		//transformG.lock()->setTranslation(Float2(transformG.lock()->getTranslation().x, jumpTranslationY));
		transformG.lock()->translate();
		if (WINDOW_WIDTH / 2 <= transformG.lock()->getPosition().x + SPRITE_SIZE / 2)
		{
			transformG.lock()->setPosition(Point(WINDOW_WIDTH / 2.0f - SPRITE_SIZE / 2, transformG.lock()->getPosition().y));
			ScrollManager::getInstance()->setScrollOffset(-transformG.lock()->getTranslation().x);
		}
		else
		{
			ScrollManager::getInstance()->setScrollOffset(0.0f);
		}
	}

}

void Mario::dash()
{

	auto transformG = this->getComponent<ComponentGravity>();

	if (!transformG.expired())
	{
		if (KeyManager::checkHitKey(KEY_INPUT_A))
		{
			if (-MARIO_DASH_SPEED_MAX <= transformG.lock()->getTranslation().x)
			{
				transformG.lock()->addTranslation(Float2(-MARIO_DASH_ACCELERATION, 0.0f));
			}
		}
		else if (transformG.lock()->getTranslation().x < 0.0f)
		{
			transformG.lock()->addTranslation(Float2(MARIO_DASH_ACCELERATION, 0.0f));
		}
		if (KeyManager::checkHitKey(KEY_INPUT_D))
		{
			if (transformG.lock()->getTranslation().x <= MARIO_DASH_SPEED_MAX)
			{
				transformG.lock()->addTranslation(Float2(MARIO_DASH_ACCELERATION, 0.0f));
			}

		}
		else if (0.0f < transformG.lock()->getTranslation().x)
		{
			transformG.lock()->addTranslation(Float2(-MARIO_DASH_ACCELERATION, 0.0f));
		}


		if (fabsf(transformG.lock()->getTranslation().x) <= 0.1)
		{
			// Only zero horizontal translation, preserve vertical velocity set by gravity/jump
			auto cur = transformG.lock()->getTranslation();
			transformG.lock()->setTranslation(Float2(0.0f, cur.y));
		}


		transformG.lock()->translate();
		if (WINDOW_WIDTH / 2 <= transformG.lock()->getPosition().x + SPRITE_SIZE / 2)
		{
			transformG.lock()->setPosition(Point(WINDOW_WIDTH / 2.0f - SPRITE_SIZE / 2, transformG.lock()->getPosition().y));
			ScrollManager::getInstance()->setScrollOffset(-transformG.lock()->getTranslation().x);
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
