#include "mario.h"
#include"componentGravity.h"
#include"componentCollision.h"
#include"componentRenderable.h"
#include"collisionManager.h"
#include"floor.h"
#include"objectManager.h"
#include"scrollManager.h"
#include "hatenablock.h"
#include"DxLib.h"
#include"soundManager.h"


Mario::Mario() : Object(ObjectManager::makeId())
{
	// とりあえず座標は0,0で初期化
	Rect rect(Point(0, -6.0f), Point(MARIO_SIZE, MARIO_SIZE ));

	// 重力込み移動コンポーネント追加
	this->addComponent<ComponentGravity>(id);
	auto transformG = this->getComponent<ComponentGravity>().lock();
	transformG->setLanding(false);
	transformG->setSpeed(1.0f);

	jumpTranslationY = JUMP_FIRST_SPEED;
	jumpHoldCount = 0;

	// 当たり判定コンポーネント追加(タグも追加しないと動作がうまくいかない)
	this->addComponent<ComponentCollisionRect>(id, rect).lock()->addTag(ICollisionTag::MARIO);

	LoadDivGraph("mario/mario01-01.png", 7, 7, 1, 18, 16, marioImages);

	walkAnim[0] = 0;
	walkAnim[1] = 1;
	walkAnim[2] = 2;

	jumpAnim[0] = 3;

	idleAnim[0] = 4;

	auto renderImage =
		this->addComponent<ComponentRenderableImage>(id, ComponentRenderable::PRIORITY_DEFAULT, marioImages[0]);

	// ステートマシンにステートと関数を追加
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
	auto renderImage = getComponent<ComponentRenderableImage>();

	if (!renderImage.expired())
	{
		renderImage.lock()->syncFromTransform();
	}

	// -------------------------------------------------------------------------
	// 1. 当たり判定座標更新と当たった時の処理
	// -------------------------------------------------------------------------
	if (colRect.lock())
	{
		colRect.lock()->update();

		bool isTouchingTop = false;

		// すべての衝突情報を1つのループでシンプルかつ確実に処理する
		for (auto& colInfo : colRect.lock()->getInfo())
		{
			if (colInfo.expired()) continue;
			auto colInfoSp = colInfo.lock();
			if (colInfoSp->getTarget(id).expired()) continue;
			if (!colInfoSp->getColliding()) continue; 

			
			int side = colInfoSp->getRectCollideSide();
			if (colInfoSp->getObjectIdCol1() != id)
			{
				if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_LEFT) side = ContactInfo::RECTCOLLIDESIDE::SIDE_RIGHT;
				else if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_RIGHT) side = ContactInfo::RECTCOLLIDESIDE::SIDE_LEFT;
				else if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_TOP) side = ContactInfo::RECTCOLLIDESIDE::SIDE_BOTTOM;
				else if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_BOTTOM) side = ContactInfo::RECTCOLLIDESIDE::SIDE_TOP;
			}

			auto targetTag = colInfoSp->getTarget(id).lock()->getTag()->tag;

		
			if (targetTag == ICollisionTag::FLOOR || targetTag == ICollisionTag::RENGA || targetTag == ICollisionTag::BLOCK)
			{
				auto targetShape = colInfoSp->getTarget(id).lock();
				auto targetRectComp = std::dynamic_pointer_cast<ComponentCollisionRect>(targetShape);
				if (targetRectComp)
				{
					Rect trect = targetRectComp->get();

					
					float marioBottom = transformG.lock()->getPosition().y + MARIO_SIZE;
					float marioLeft = transformG.lock()->getPosition().x;
					float marioRight = marioLeft + MARIO_SIZE;

					
					if (marioBottom <= trect.begin.y + 8.0f &&marioBottom >= trect.begin.y - 8.0f)
					{

						if (marioRight > trect.begin.x - 1.5f && marioLeft < trect.begin.x + trect.size.x + 1.5f)
						{
							side = ContactInfo::RECTCOLLIDESIDE::SIDE_TOP;
						}
					}

					
					if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_TOP)
					{
						transformG.lock()->setPosY(trect.begin.y - MARIO_SIZE + 5.5f);
						auto cur = transformG.lock()->getTranslation();
						transformG.lock()->setTranslation(Float2(cur.x, 0.0f));
						transformG.lock()->setLanding(true);
						isTouchingTop = true;
					}
				
					else if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_BOTTOM)
					{
						if (colInfoSp->getEnter()) // ぶつかった瞬間のみ
						{
							if (targetTag == ICollisionTag::RENGA)
							{
								int targetId =
									(colInfoSp->getObjectIdCol1() == id)
									? colInfoSp->getObjectIdCol2()
									: colInfoSp->getObjectIdCol1();

								auto targetObj = ObjectManager::getObjectById(targetId);

								if (!targetObj.expired())
								{
									targetObj.lock()->die();
								}
							}
							else if (targetTag == ICollisionTag::BLOCK)
							{
								int targetId =
									(colInfoSp->getObjectIdCol1() == id)
									? colInfoSp->getObjectIdCol2()
									: colInfoSp->getObjectIdCol1();

								auto targetObj = ObjectManager::getObjectById(targetId);

								if (!targetObj.expired())
								{
									auto hatena =
										std::dynamic_pointer_cast<hatenablock>(
											targetObj.lock());

									if (hatena)
									{
										hatena->hitFromBottom();
									}
								}
							}
						}
					}
					
					else if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_LEFT)
					{
						
						float marioBottom = transformG.lock()->getPosition().y + MARIO_SIZE;
						float cornerBuffer = 6.0f; 

						if (marioBottom - 5.5f > trect.begin.y && (marioBottom - 5.5f - trect.begin.y) < cornerBuffer)
						{
							transformG.lock()->setPosY(trect.begin.y - MARIO_SIZE + 5.5f);
							auto cur = transformG.lock()->getTranslation();
							transformG.lock()->setTranslation(Float2(cur.x, cur.y)); // Y速度（ジャンプの勢い）は殺さない！
							transformG.lock()->setLanding(true);
							isTouchingTop = true;
						}
						else
						{
							
							transformG.lock()->setPosX(trect.begin.x - MARIO_SIZE);
							auto cur = transformG.lock()->getTranslation();
							transformG.lock()->setTranslation(Float2(0.0f, cur.y)); // ここでもY速度は殺さず維持！
						}
					}
					else if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_RIGHT)
					{
						
						float marioBottom = transformG.lock()->getPosition().y + MARIO_SIZE;
						float cornerBuffer = 6.0f;

						if (marioBottom - 5.5f > trect.begin.y && (marioBottom - 5.5f - trect.begin.y) < cornerBuffer)
						{
							transformG.lock()->setPosY(trect.begin.y - MARIO_SIZE + 5.5f);
							auto cur = transformG.lock()->getTranslation();
							transformG.lock()->setTranslation(Float2(cur.x, cur.y));
							transformG.lock()->setLanding(true);
							isTouchingTop = true;
						}
						else
						{
							transformG.lock()->setPosX(trect.begin.x + trect.size.x);
							auto cur = transformG.lock()->getTranslation();
							transformG.lock()->setTranslation(Float2(0.0f, cur.y)); // Y速度は維持！
						}
					}
				}
			}
		} 

		if (!isTouchingTop)
		{
			transformG.lock()->setLanding(false);
		}
	}

	transformG.lock()->gravityUpdate();

	if (transformG.lock()->getLanding())
	{
		if (KeyManager::pushHitKey(KEY_INPUT_SPACE))
		{
			jumpHoldCount = 0;
			jumpTranslationY = JUMP_FIRST_SPEED;
			moveStateMachine.changeState(MOVESTATE::MOV_JUMP);
			transformG.lock()->setTranslation(Float2(transformG.lock()->getTranslation().x, jumpTranslationY));
			transformG.lock()->setLanding(false);

			int jumpHandle = SoundManager::getInstance()->getSoundHandle(SoundManager::SE_JUMP);
			if (jumpHandle != -1)
			{
				// 効果音（SE）なので、1回だけ流す「DX_PLAYTYPE_BACK」を指定します
				PlaySoundMem(jumpHandle, DX_PLAYTYPE_BACK);
			}

		}
		else if (KeyManager::checkHitKey(KEY_INPUT_LSHIFT))
		{
			if (moveStateMachine.getStateId() != MOVESTATE::MOV_DASH)
			{
				moveStateMachine.changeState(MOVESTATE::MOV_DASH);
			}
			transformG.lock()->setTranslation(Float2(transformG.lock()->getTranslation().x, 0.0f));
		}
		else
		{
			if (moveStateMachine.getStateId() != MOVESTATE::MOV_WALK)
			{
				moveStateMachine.changeState(MOVESTATE::MOV_WALK);
			}
			transformG.lock()->setTranslation(Float2(transformG.lock()->getTranslation().x, 0.0f));
		}
	}

	
	moveStateMachine.update(this);
	varyStateMachine.update(this);
	starStateMachine.update(this);

	
	if (!transformG.expired())
	{
		Float2 v = transformG.lock()->getTranslation();

		if (fabsf(v.x) < 0.05f)
			v.x = 0.0f;

		if (fabsf(v.y) < 0.05f)
			v.y = 0.0f;

		transformG.lock()->setTranslation(v);
	}

	
	animTimer++;

	if (colRect.lock())
	{
		int currentStart = idleStart;
		int currentCount = idleCount;

		auto gravity = getComponent<ComponentGravity>();
		bool isGrounded = (!gravity.expired() && gravity.lock()->getLanding());
		Float2 vel = Float2(0.0f, 0.0f);

		if (!gravity.expired())
		{
			vel = gravity.lock()->getTranslation();
		}

		float speedX = fabsf(vel.x);

		if (!isGrounded)
		{
			currentStart = jumpStart;
			currentCount = jumpCount;
		}
		else
		{
			if (speedX < 0.1f)
			{
				currentStart = idleStart;
				currentCount = idleCount;
			}
			else
			{
				currentStart = walkStart;
				currentCount = walkCount;
			}
		}

		if (currentCount > 0)
		{
			if (currentCount == 1)
			{
				animFrame = 0;
			}
			else if (animTimer % 3 == 0)
			{
				animFrame++;
				if (animFrame >= currentCount)
					animFrame = 0;
			}

			int targetImageIndex = currentStart + animFrame;

			if (!renderImage.expired())
			{
				renderImage.lock()->setImage(marioImages[targetImageIndex]);
			}
		}
	}
}
void Mario::eventProc(int from, std::string name, std::vector<Event::DataMap> datas)
{


}

void Mario::activateProc()
{
}

void Mario::deactivateProc()
{
}

void Mario::deathProc()
{
}

void Mario::walk()
{
	auto transformG = this->getComponent<ComponentGravity>();
	if (transformG.expired()) return;

	auto tg = transformG.lock();

	// 入力
	bool left = KeyManager::checkHitKey(KEY_INPUT_A);
	bool right = KeyManager::checkHitKey(KEY_INPUT_D);

	auto gravity = getComponent<ComponentGravity>();
	bool isGrounded = (!gravity.expired() && gravity.lock()->getLanding());


	Float2 vel = Float2(0.0f, 0.0f);
	if (!gravity.expired())
	{
		vel = gravity.lock()->getTranslation();
	}

	float vx = vel.x;
	float vy = vel.y;

	
	if (left)
	{
		if (vx > -MARIO_WALK_SPEED_MAX)
			tg->addTranslation(Float2(-MARIO_WALK_ACCELERATION, 0.0f));
	}
	else if (right)
	{
		if (vx < MARIO_WALK_SPEED_MAX)
			tg->addTranslation(Float2(MARIO_WALK_ACCELERATION, 0.0f));
	}
	else
	{
		if (fabsf(vx) < 0.05f)
			tg->setTranslation(Float2(0.0f, vy));
		else if (vx > 0.0f)
			tg->addTranslation(Float2(-MARIO_WALK_ACCELERATION, 0.0f));
		else
			tg->addTranslation(Float2(MARIO_WALK_ACCELERATION, 0.0f));
	}

	tg->translate();


	if (tg->getPosition().x <= 0.0f)
	{
		tg->setPosition(Point(0.0f, tg->getPosition().y));
	}

	if (WINDOW_WIDTH / 2 <= tg->getPosition().x + SPRITE_SIZE / 2)
	{
		tg->setPosition(Point(WINDOW_WIDTH / 2.0f - SPRITE_SIZE / 2,
			tg->getPosition().y));

		ScrollManager::getInstance()->setScrollOffset(-tg->getTranslation().x);
	}
	else
	{
		ScrollManager::getInstance()->setScrollOffset(0.0f);
	}
}

void Mario::jump()
{
	auto transformG = getComponent<ComponentGravity>();
	if (KeyManager::checkHitKey(KEY_INPUT_SPACE) && jumpHoldCount <= 30)
	{
		jumpHoldCount++;
	}
	else
	{
		if (!transformG.expired())
		{
			transformG.lock()->addTranslation(Float2(0.0f, 0.35f));
		}
		
	}

	if (!transformG.expired())
	{
		//transformG.lock()->setTranslation(Float2(transformG.lock()->getTranslation().x, jumpTranslationY));
		transformG.lock()->translate();
		if (transformG.lock()->getPosition().x <= 0.0f)
		{
			transformG.lock()->setPosition(Point(0.0f, transformG.lock()->getPosition().y));
		}

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
		if (transformG.lock()->getPosition().x <= 0.0f)
		{
			transformG.lock()->setPosition(Point(0.0f, transformG.lock()->getPosition().y));
		}

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
