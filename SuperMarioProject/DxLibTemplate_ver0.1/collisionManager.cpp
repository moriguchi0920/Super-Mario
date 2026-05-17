#include"collisionManager.h"




// コンストラクタ
CollisionManager::CollisionManager()
{
	for (int i = 0; i < CollisionObject::CollisionMark::COLLISION_MARK_NUM; i++)
	{
		collisionObjectTable[i].resize(OBJECT_MAX);
		for (size_t j = 0; j < collisionObjectTable[i].size(); j++)
		{
			collisionObjectTable[i][j] = nullptr;
		}
	}
	lastId = COLLISION_GENERATE_START_ID;

	infoId = 0;
}
// デストラクタ
CollisionManager::~CollisionManager()
{
	nullAll();
}

// シングルトンのポインタ入手関数
CollisionManager* CollisionManager::getInstance()
{
	static CollisionManager colManager;
	return &colManager;
}
// マネージャーにCollisionObjectを登録
void CollisionManager::addObject(CollisionObject* _Object)
{
	collisionObjectTable[_Object->getMark()].push_back(_Object);
}


// CollisionObjectの登録解除
void CollisionManager::removeObject(CollisionObject* _pObject)
{
	if (_pObject == nullptr)return ;
	CollisionObject::CollisionMark mark = _pObject->getMark();

	for (size_t i = 0; i < collisionObjectTable[mark].size(); i++)
	{
		CollisionObject* c = collisionObjectTable[mark][i];
		if(c == _pObject)
		{
			deleteInfoFromCol(_pObject);

			break;
		}

	}

	collisionObjectTable[mark].erase(std::remove_if(collisionObjectTable[mark].begin(), collisionObjectTable[mark].end(), [_pObject](CollisionObject* ptr) {return ptr == _pObject; }), collisionObjectTable[mark].end());

}

// CollisionOBjectの登録解除、CllisionInfoの破壊
void CollisionManager::nullAll()
{
	for (int i = 0; i < CollisionObject::COLLISION_MARK_NUM; i++)
	{
		collisionObjectTable[i].clear();
	}
	for (int i = 0; i < collisionInfoArray.size(); i++)
	{
		collisionInfoArray[i].reset();
	}
}

// 当たり判定関数
void CollisionManager::flexibleCollision(CollisionObject* Ob1, CollisionObject* Ob2)
{
	// 接触情報保存用変数を宣言
	ContactInfo contact;
	// 当たっていないなら抜ける
	if(!Ob1->getShape()->checkCollide(Ob2->getShape(), &contact)) return;
	// すでにあるCollisionInfoと被っていても抜ける
	if (knownReject(Ob1, Ob2)) return ;
	
	// 分かりやすいように色を変更
	Ob1->color.set(255, 255, 0);
	Ob2->color.set(255, 255, 0);
	// CollisionInfoの動的生成
	int id = generateInfoId();

	std::shared_ptr<CollisionInfo> spInfo = std::make_shared< CollisionInfo>(Ob1, Ob2, id);
	spInfo->setStatus(contact);
	collisionInfoArray.push_back(std::move(spInfo));
	Ob1->setInfoId(id);
	Ob2->setInfoId(id);


	return ;
}
/// <summary>
///  当たり判定の更新関数
/// </summary>
void CollisionManager::collisionUpdate()
{
	updateInfo();
	// まず当たり判定を取るオブジェクトを取る
	for (int i = 0; i < CollisionObject::CollisionMark::COLLISION_MARK_NUM; i++)
	{
		CollisionObject** pPObjectArrayBase = collisionObjectTable[i].data();
		for (size_t j = 0; j < collisionObjectTable[i].size(); j++)
		{
			CollisionObject* pCollisionBase = pPObjectArrayBase[j];
			// NULLチェック
			if (pCollisionBase == nullptr)
			{
				continue;
			}
			if (pCollisionBase->getIsCollide() == false)
			{
				continue;
			}

	
			
			//// すでに接触したターゲットがいたら
			//if (pCollisionBase->target != NULL && pCollisionBase->target->getShape() != NULL)
			//{
			//	// 接触判定(初回のみ)をオフに
			//	pCollisionBase->collisionEnter = false;
			//	// 継続接触判定を行う
			//	if (flexibleCollision(pCollisionBase, pCollisionBase->target))
			//	{
			//		pCollisionBase->isCollideNow = true;
			//		pCollisionBase->color.set(255, 255, 0);
			//		break;
			//	}
			//	// ターゲットがいるが当たっていない場合は
			//	else
			//	{
			//		// 継続判定もオフに
			//		// ターゲットも初期化
			//		pCollisionBase->isCollideNow = false;
			//		pCollisionBase->target = NULL;
			//		pCollisionBase->color.set(255, 255, 255);
			//	}
			//}
			//// 接触したターゲットがいない場合も同じく初期化
			//else
			//{
			//	pCollisionBase->isCollideNow = false;
			//	pCollisionBase->target = NULL;
			//	pCollisionBase->color.set(255, 255, 255);
			//}
			// その後、あたる相手を探す
			for (int k = 0; k < CollisionObject::CollisionMark::COLLISION_MARK_NUM; k++)
			{
				CollisionObject** pPObjectArrayTarget = collisionObjectTable[k].data();
				if (pCollisionBase->isCollideTarget(static_cast<CollisionObject::CollisionMark>(k)) == false)
				{
					continue;
				}
				for (size_t l = 0; l < collisionObjectTable[k].size(); l++)
				{
					CollisionObject* pCollisionTarget = pPObjectArrayTarget[l];
					// NULLチェック
					if (pCollisionTarget == nullptr || pCollisionBase == pCollisionTarget)
					{
						continue;
					}
					if (pCollisionTarget->getIsCollide() == false)
					{
						continue;
					}
					if (pCollisionBase->getShape() == nullptr || pCollisionTarget->getShape() == nullptr)
					{
						continue;
					}
					// 当たり判定を取る
					flexibleCollision(pCollisionBase, pCollisionTarget);

					
					//else
					//{
					//	pCollisionBase->target = pCollisionTarget;
					//	pCollisionBase->isCollideNow = false;
					//	pCollisionTarget->isCollideNow = false;
					//	pCollisionBase->color.set(255, 255, 255);
					//	pCollisionTarget->color.set(255, 255, 255);
					//	break;

					//}

				}
			}


		}

	}


}

// 
void CollisionManager::deleteInfoFromCol(CollisionObject* pCol)
{
	for (int i = 0; i < collisionInfoArray.size(); i++)
	{
		CollisionInfo* info = collisionInfoArray[i].get();
		if (info->getColPtr1() == pCol)
		{
			info->getColPtr2()->removeInfoId(info->getId());

		}
		else if (info->getColPtr2() == pCol)
		{
			info->getColPtr1()->removeInfoId(info->getId());
		}

	}

	collisionInfoArray.erase(std::remove_if(collisionInfoArray.begin(), collisionInfoArray.end(), [pCol](std::shared_ptr<CollisionInfo>& ptr) { return ptr->getColPtr1() == pCol || ptr->getColPtr2() == pCol; }), collisionInfoArray.end());
}

// 当たり判定情報の更新
void CollisionManager::updateInfo()
{
	// collisionInfoArrayの走査
	for (int i = 0; i < collisionInfoArray.size(); i++)
	{
		// NULLじゃなかったら

		CollisionInfo* pColInfo = collisionInfoArray[i].get();
		if (pColInfo != nullptr)
		{
			// getColPtr1()が消去済みの場合
			if (pColInfo->getColPtr1() == nullptr || pColInfo->getColPtr1()->getShape() == nullptr)
			{
				// getColPtr2()が残っていた場合
				if (pColInfo->getColPtr2() != nullptr)
				{
					// 色変更
					pColInfo->getColPtr2()->color.set(255, 255, 255);
					// インデックスの登録を解除
					pColInfo->getColPtr2()->removeInfoId(collisionInfoArray[i]->getId());
				}
				// 破壊と登録解除
				collisionInfoArray.erase(collisionInfoArray.begin() + i);
				//deleteInfoFromIdx(i);
				continue;
			}
			// getColPtr2()が消去済みの場合
			if (pColInfo->getColPtr2() == nullptr || pColInfo->getColPtr2()->getShape() == nullptr)
			{
				if (pColInfo->getColPtr1() != nullptr)
				{
					pColInfo->getColPtr1()->color.set(255, 255, 255);
					// インデックスの登録を解除
					pColInfo->getColPtr1()->removeInfoId(collisionInfoArray[i]->getId());

				}

				collisionInfoArray.erase(collisionInfoArray.begin() + i);
				/*deleteInfoFromIdx(i);*/
				continue;
			}
			// 接触点の更新のために宣言
			ContactInfo contact;
			// 継続して当たっていたら
			if (pColInfo->getColPtr1()->getShape()->checkCollide(pColInfo->getColPtr2()->getShape(), &contact))
			{

				// 継続判定はtrueのまま
				// 初回接触はfalseに
				pColInfo->secondCollision();
				// その他接触点などの設定
				

			}
			// 当たっていない場合
			else
			{

				deleteInfoFromId(collisionInfoArray[i]->getId());
			}
		}
	}
}

// インデックスから検索して削除する関数
void CollisionManager::deleteInfoFromId(int id)
{
	int idx = -1;
	for (int i = 0; i < collisionInfoArray.size(); i++)
	{
		if (collisionInfoArray[i]->getId() == id)
		{
			idx = i;
		}
	}

	if (idx == -1)
	{
		return;
	}

	collisionInfoArray[idx]->getColPtr1()->removeInfoId(id);
	collisionInfoArray[idx]->getColPtr2()->removeInfoId(id);
	collisionInfoArray.erase(collisionInfoArray.begin() + idx);
}

// すでに接触情報が保存されている場合に弾く間数
bool CollisionManager::knownReject(CollisionObject* Ob1, CollisionObject* Ob2)
{
	for (int i = 0; i < collisionInfoArray.size(); i++)
	{
		CollisionInfo* pColInfo = collisionInfoArray[i].get();
		if (pColInfo != NULL)
		{
			if (pColInfo->getColPtr1() == Ob1 && collisionInfoArray[i]->getColPtr2() == Ob2)
			{
				return true;
			}
			if (pColInfo->getColPtr2() == Ob1 && collisionInfoArray[i]->getColPtr1() == Ob2)
			{
				return true;
			}

		}
	}
	return false;
}

// 全削除の関数
void CollisionManager::deleteAllInfo()
{
	for (int i = 0; i < COLLISION_SAVE_MAX; i++)
	{
		collisionInfoArray.clear();
	}
}

// オブジェクトのメンバpColに持たせたインデックスからCollisionInfoを取り出す関数
std::weak_ptr<CollisionInfo> CollisionManager::getColInfoFromId(int id)
{
	int idx = -1;
	for (int i = 0; i < collisionInfoArray.size(); i++)
	{
		if (collisionInfoArray[i]->getId() == id)
		{
			idx = i;
		}
	}

	if (idx == -1)
	{
		return std::weak_ptr<CollisionInfo>();
	}

	std::weak_ptr<CollisionInfo> wpColInfo(collisionInfoArray[idx]);
	return wpColInfo;
}

int CollisionManager::generateId()
{
	return lastId++;
}

int CollisionManager::generateInfoId()
{
	return infoId++;
}
