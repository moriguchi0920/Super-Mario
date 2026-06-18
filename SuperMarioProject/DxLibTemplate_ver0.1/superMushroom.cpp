#include "superMushroom.h"
#include"objectManager.h"
#include"collisionManager.h"

SuperMushroom::SuperMushroom(Rect rect) : Object(ObjectManager::makeId())
{
	// 重力込み移動コンポーネント追加
	this->addComponent<ComponentGravity>(id);
	auto transformG = this->getComponent<ComponentGravity>().lock();
	transformG->setPosition(rect.begin);
	transformG->setLanding(false);
	transformG->setSpeed(ITEM_SPEED);
	transformG->setScroll(true);

	transformG->setTranslation(Float2(-1.0f, 0.0f));

	// 当たり判定コンポーネント追加(タグも追加しないと動作がうまくいかない)
	this->addComponent<ComponentCollisionRect>(id, rect).lock()->addTag(ICollisionTag::ENEMY);


	// 描画コンポーネント追加
	this->addComponent<ComponentRenderableRect>(id, ComponentRenderable::PRIORITY_DEFAULT, rect);

	auto comR = getComponent<ComponentRenderableRect>();

	comR.lock()->setColor(255, 0, 0);
}

SuperMushroom::~SuperMushroom()
{
}

void SuperMushroom::update()
{
	// コンポーネント取得
	auto colRect = getComponent<ComponentCollisionRect>();
	auto transformG = getComponent<ComponentGravity>();
	auto renderRect = getComponent<ComponentRenderableRect>();


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
									// 座標を上辺＋サイズの値
									Rect trect = targetRectComp->get();
									transformG.lock()->setPosY(trect.begin.y - SPRITE_SIZE);
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
									// 座標を上辺＋サイズに
									Rect trect = targetRectComp->get();
									transformG.lock()->setPosY(trect.begin.y - SPRITE_SIZE);
									auto cur = transformG.lock()->getTranslation();
									// Y移動量を0に
									transformG.lock()->setTranslation(Float2(cur.x, 0.0f));
									// 接地しているとする
									transformG.lock()->setLanding(true);
								}
								// 当たっていない
								else if (colInfoSp->getExit())
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
									transformG.lock()->setPosX(trect.begin.x - SPRITE_SIZE);
									auto cur = transformG.lock()->getTranslation();
									// X移動量を逆に
									transformG.lock()->setTranslation(Float2(-1.0f, cur.y));

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
									// X移動量を逆に
									transformG.lock()->setTranslation(Float2(1.0f, cur.y));

								}
							}
						}
						break;
					}
					case ICollisionTag::MARIO:
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
								die();

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
	transformG.lock()->translate();

	// 描画の座標更新
	renderRect.lock()->syncFromTransform();
}

void SuperMushroom::eventProc(int from, std::string name, std::vector<Event::DataMap> datas)
{
}

void SuperMushroom::activateProc()
{
}

void SuperMushroom::deactivateProc()
{
}

void SuperMushroom::deathProc()
{
}
