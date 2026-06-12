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
	// とりあえず座標は0,0で初期化
	Rect rect(Point(0, 0), Point(MARIO_SIZE, MARIO_SIZE));

	// 重力込み移動コンポーネント追加
	this->addComponent<ComponentGravity>(id);
	auto transformG = this->getComponent<ComponentGravity>().lock();
	transformG->setLanding(false);
	transformG->setSpeed(1.0f);

	jumpTranslationY = JUMP_FIRST_SPEED;
	jumpHoldCount = 0;

	// 当たり判定コンポーネント追加(タグも追加しないと動作がうまくいかない)
	this->addComponent<ComponentCollisionRect>(id, rect).lock()->addTag(ICollisionTag::MARIO);
	// 描画コンポーネント追加
	this->addComponent<ComponentRenderableRect>(id,ComponentRenderable::PRIORITY_DEFAULT, rect);


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

	// 描画の座標更新
	renderRect.lock()->syncFromTransform();

	// 当たり判定座標更新と当たった時の処理
	// 当たり判定更新
	if (colRect.lock())
	{
		// 一度当たり判定の更新
		colRect.lock()->update();
		// 当たり判定情報があったら
		for (auto& colInfo : colRect.lock()->getInfo())
		{
			// nullチェック
			if (!colInfo.expired())
			{
				auto colInfoSp = colInfo.lock();
				// 当たった相手が存在したら
				if (!colInfoSp->getTarget(id).expired())
				{
					// 四角形当たり判定の当たった辺を取得
					int side = colInfoSp->getRectCollideSide();
					// 当たった辺が自分から見てなのか相手から見てなのかで辺を切り替え
					if (colInfoSp->getObjectIdCol1() != id)
					{
						if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_LEFT) side = ContactInfo::RECTCOLLIDESIDE::SIDE_RIGHT;
						else if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_RIGHT) side = ContactInfo::RECTCOLLIDESIDE::SIDE_LEFT;
						else if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_TOP) side = ContactInfo::RECTCOLLIDESIDE::SIDE_BOTTOM;
						else if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_BOTTOM) side = ContactInfo::RECTCOLLIDESIDE::SIDE_TOP;
					}
					// タグで区別
					switch (colInfoSp->getTarget(id).lock()->getTag()->tag)
					{
					// 床
					case ICollisionTag::FLOOR:
					{
						// 床の上辺に当たっている
						if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_TOP)
						{
							// 形情報を取得
							auto targetShape = colInfoSp->getTarget(id).lock();
							auto targetRectComp = std::dynamic_pointer_cast<ComponentCollisionRect>(targetShape);
							// 四角なら
							if (targetRectComp)
							{
								// 当たった(瞬間)
								if (colInfoSp->getEnter())
								{


								}
								// 当たっている(継続)
								if (colInfoSp->getColliding())
								{
									// 座標を上辺＋マリオのサイズの値に
									Rect trect = targetRectComp->get();
									transformG.lock()->setPosY(trect.begin.y - MARIO_SIZE);
									auto cur = transformG.lock()->getTranslation();
									// Y移動量を0に
									transformG.lock()->setTranslation(Float2(cur.x, 0.0f));
									// 接地しているとする
									transformG.lock()->setLanding(true);
								}
								// 当たっていない
								else
								{
									// 接地していないとする
									transformG.lock()->setLanding(false);
								}
							}
						}
						break;
					}

					// レンガブロック
					case ICollisionTag::RENGA:
					{
						// 上辺
						if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_TOP)
						{
							auto targetShape = colInfoSp->getTarget(id).lock();
							auto targetRectComp = std::dynamic_pointer_cast<ComponentCollisionRect>(targetShape);

							if (targetRectComp)
							{
								if (colInfoSp->getColliding())
								{
									Rect trect = targetRectComp->get();

									transformG.lock()->setPosY(trect.begin.y - MARIO_SIZE);

									auto cur = transformG.lock()->getTranslation();

									transformG.lock()->setTranslation(Float2(cur.x, 0.0f));

									transformG.lock()->setLanding(true);
								}
								else if (colInfoSp->getExit())
								{
									transformG.lock()->setLanding(false);
								}
							}
						}

						// 下辺
						else if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_BOTTOM)
						{
							auto targetShape = colInfoSp->getTarget(id).lock();
							auto targetRectComp = std::dynamic_pointer_cast<ComponentCollisionRect>(targetShape);

							if (targetRectComp)
							{
								if (colInfoSp->getEnter())
								{
									int targetId;

									if (colInfoSp->getObjectIdCol1() == id)
									{
										targetId = colInfoSp->getObjectIdCol2();
									}
									else
									{
										targetId = colInfoSp->getObjectIdCol1();
									}

									auto targetObj = ObjectManager::getObjectById(targetId);

									if (!targetObj.expired())
									{
										targetObj.lock()->die();
									}

									Rect trect = targetRectComp->get();

									transformG.lock()->setPosY(trect.begin.y + trect.size.y);

									auto cur = transformG.lock()->getTranslation();

									transformG.lock()->setTranslation(Float2(cur.x, 0.0f));
								}
							}
						}

						// 左辺
						else if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_LEFT)
						{
							auto targetShape = colInfoSp->getTarget(id).lock();
							auto targetRectComp = std::dynamic_pointer_cast<ComponentCollisionRect>(targetShape);

							if (targetRectComp)
							{
								if (colInfoSp->getColliding())
								{
									Rect trect = targetRectComp->get();

									transformG.lock()->setPosX(trect.begin.x - MARIO_SIZE);

									auto cur = transformG.lock()->getTranslation();

									transformG.lock()->setTranslation(Float2(0.0f, cur.y));
								}
							}
						}

						// 右辺
						else if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_RIGHT)
						{
							auto targetShape = colInfoSp->getTarget(id).lock();
							auto targetRectComp = std::dynamic_pointer_cast<ComponentCollisionRect>(targetShape);

							if (targetRectComp)
							{
								if (colInfoSp->getColliding())
								{
									Rect trect = targetRectComp->get();

									transformG.lock()->setPosX(trect.begin.x + trect.size.x);

									auto cur = transformG.lock()->getTranslation();

									transformG.lock()->setTranslation(Float2(0.0f, cur.y));
								}
							}
						}

						break;
					}

					// ブロック
					case ICollisionTag::BLOCK:
					{
						// 上辺
						if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_TOP)
						{
							// 形情報取得
							auto targetShape = colInfoSp->getTarget(id).lock();
							auto targetRectComp = std::dynamic_pointer_cast<ComponentCollisionRect>(targetShape);
							// 四角なら
							if (targetRectComp)
							{
								// 当たった(瞬間)
								if (colInfoSp->getEnter())
								{


								}
								// 当たっている(継続)
								if (colInfoSp->getColliding())
								{
									// 座標を上辺＋マリオのサイズに
									Rect trect = targetRectComp->get();
									transformG.lock()->setPosY(trect.begin.y - MARIO_SIZE);
									auto cur = transformG.lock()->getTranslation();
									// Y移動量を0に
									transformG.lock()->setTranslation(Float2(cur.x, 0.0f));
									// 接地しているとする
									transformG.lock()->setLanding(true);
								}
								// 当たっていない
								else if(colInfoSp->getExit())
								{
									// 接地していないとする
									transformG.lock()->setLanding(false);
								}

							}
						}

						// 下辺
						else if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_BOTTOM)
						{
							// 形情報取得
							auto targetShape = colInfoSp->getTarget(id).lock();
							auto targetRectComp = std::dynamic_pointer_cast<ComponentCollisionRect>(targetShape);
							// 四角なら
							if (targetRectComp)
							{
								// 当たった(瞬間)
								// 当たった瞬間のみにしないと天井に張り付くような見た目になるため処理は当たった瞬間のみ
								if (colInfoSp->getEnter())
								{
									// 座標を下辺に合わせる
									Rect trect = targetRectComp->get();
									transformG.lock()->setPosY(trect.begin.y + trect.size.y);
									auto cur = transformG.lock()->getTranslation();
									// Y移動量を0に
									transformG.lock()->setTranslation(Float2(cur.x, 0.0f));

								}

							}
						}
						// 左辺
						else if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_LEFT)
						{
							// 形情報取得
							auto targetShape = colInfoSp->getTarget(id).lock();
							auto targetRectComp = std::dynamic_pointer_cast<ComponentCollisionRect>(targetShape);
							// 四角なら
							if (targetRectComp)
							{
								// 当たっている(継続)
								if (colInfoSp->getColliding())
								{
									// 座標を左辺＋マリオの横サイズに合わせる
									Rect trect = targetRectComp->get();
									transformG.lock()->setPosX(trect.begin.x - MARIO_SIZE);
									auto cur = transformG.lock()->getTranslation();
									// X移動量を0に
									transformG.lock()->setTranslation(Float2(0.0f, cur.y));

								}
							}
						}
						// 右辺
						else if (side == ContactInfo::RECTCOLLIDESIDE::SIDE_RIGHT)
						{
							// 形情報取得
							auto targetShape = colInfoSp->getTarget(id).lock();
							auto targetRectComp = std::dynamic_pointer_cast<ComponentCollisionRect>(targetShape);
							// 四角なら
							if (targetRectComp)
							{
								//当たっている(継続)
								if (colInfoSp->getColliding())
								{
									// 座標を右辺に合わせる
									Rect trect = targetRectComp->get();
									transformG.lock()->setPosX(trect.begin.x + trect.size.x);
									auto cur = transformG.lock()->getTranslation();
									// X移動量を0に
									transformG.lock()->setTranslation(Float2(0.0f, cur.y));

								}
							}
						}
						break;
					}
					}

				}
			}
		}
	}



	// 重力更新
	transformG.lock()->gravityUpdate();
	// 接地しているときのダッシュ、ジャンプ切り替え処理
	if (transformG.lock()->getLanding())
	{
		// スペースキーが押されたら
		if (KeyManager::pushHitKey(KEY_INPUT_SPACE))
		{
			// スペースキーホールド時のジャンプ高変更のための変数を初期化
			jumpHoldCount = 0;
			jumpTranslationY = JUMP_FIRST_SPEED;
			// ステート変更
			moveStateMachine.changeState(MOVESTATE::MOV_JUMP);
			// Y移動量を設定
			transformG.lock()->setTranslation(Float2(transformG.lock()->getTranslation().x, jumpTranslationY));
			// 接地はしていないとする
			transformG.lock()->setLanding(false);

		}
		// シフトが押されたら
		else if (KeyManager::checkHitKey(KEY_INPUT_LSHIFT))
		{
			// ステート変更
			moveStateMachine.changeState(MOVESTATE::MOV_DASH);
			// X移動量を設定
			transformG.lock()->setTranslation(Float2(transformG.lock()->getTranslation().x, 0.0f));
		}
		// スペースもシフトも押されていない(歩き)
		else
		{
			// ステート変更
			moveStateMachine.changeState(MOVESTATE::MOV_WALK);
			// X移動量を設定
			transformG.lock()->setTranslation(Float2(transformG.lock()->getTranslation().x, 0.0f));
		}

	}

	// 各状態の更新処理
	moveStateMachine.update(this);
	varyStateMachine.update(this);
	starStateMachine.update(this);
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
