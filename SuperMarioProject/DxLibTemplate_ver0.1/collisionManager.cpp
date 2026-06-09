#include"collisionManager.h"
#include"componentManager.h"


std::vector<std::shared_ptr<CollisionInfo>> CollisionManager::collisionInfoArray;

// コンストラクタ
CollisionManager::CollisionManager()
{

	infoId = 0;
}
// デストラクタ
CollisionManager::~CollisionManager()
{
	collisionInfoArray.clear();
}

// シングルトンのポインタ入手関数
CollisionManager* CollisionManager::getInstance()
{
	static CollisionManager colManager;
	return &colManager;
}





// 当たり判定関数
void CollisionManager::flexibleCollision()
{
	// コンポーネントマネージャーのインスタンス取得
	ComponentManager* pComManager = ComponentManager::getInstance();

	// 走査用の可変長配列を基底クラスComponentCollisionShapeから取得
	std::vector<std::weak_ptr<ComponentCollisionShape>> vector = pComManager->getComponentsByBase<ComponentCollisionShape>();

	// 当たったかどうかの判定用変数
	bool isCollide = false;


	// 配列の走査
	for (size_t i = 0; i < vector.size(); i++)
	{
		if (!vector[i].expired())
		{

			if (!vector[i].lock()->getIsActive())
			{
				continue;
			}
			// Update the i-th component so prevPos is current
			vector[i].lock()->update();
			// 二重forで総当たり(初期値をi + 1にすることで重複を発生させない)
			for (size_t j = i + 1; j < vector.size(); j++)
			{
				// どちらも存在したら(nullチェック)
				if (!vector[j].expired())
				{
					if (!vector[j].lock()->getIsActive())
					{
						continue;
					}

					vector[j].lock()->update();

					if (!(vector[i].lock()->getTag()->canCollide(vector[j].lock()->getTag()->tag))) continue;

					// 同じCollisionInfoがあったらcontinueで弾く
					if (knownReject(vector[i].lock()->getParentId(), vector[j].lock()->getParentId())) continue;

					// 接触情報保存用変数を宣言
					ContactInfo contact;
					// 判定用変数にcheckCollideの結果を代入
					isCollide = vector[i].lock()->checkCollide(vector[j].lock().get(), &contact);
					// あたっていたら
					if (isCollide)
					{


						// CollisionInfoの動的生成
						int id = generateInfoId();
						std::shared_ptr<CollisionInfo> spInfo = std::make_shared<CollisionInfo>(vector[i].lock(), vector[j].lock(), id);
						// 接触情報をセット
						spInfo->setStatus(contact);
						spInfo->firstCollision();
						// 可変長配列に追加
						collisionInfoArray.push_back(std::move(spInfo));
						// CollisionInfo検索用idを当たったコンポーネント同士にセット
						vector[i].lock()->setInfoId(id);
						vector[j].lock()->setInfoId(id);



					}
				}
			}
		}


	}


	return ;
}
/// <summary>
///  当たり判定の更新関数
/// </summary>
void CollisionManager::collisionUpdate()
{
	updateInfo();
	// まず当たり判定を取るオブジェクトを取る

	flexibleCollision();

}



// 当たり判定情報の更新
void CollisionManager::updateInfo()
{
	ComponentManager* pComManager = ComponentManager::getInstance();

	// collisionInfoArrayの走査
	for (int i = 0; i < collisionInfoArray.size(); i++)
	{
		// NULLじゃなかったら

		CollisionInfo* pColInfo = collisionInfoArray[i].get();
		if (pColInfo != nullptr)
		{
			// getCol1()が消去済みの場合
			if (pColInfo->getCol1().expired())
			{
				// getCol2()が残っていた場合
				if (!pColInfo->getCol2().expired())
				{
					pColInfo->getCol2().lock()->removeInfoId(pColInfo->getId());
				}
				//破壊と登録解除
				collisionInfoArray.erase(collisionInfoArray.begin() + i);
				continue;
			}
			// getCol2()が消去済みの場合
			if (pColInfo->getCol2().expired())
			{
				// getCol1()が残っていた場合
				if (!pColInfo->getCol1().expired())
				{
					pColInfo->getCol1().lock()->removeInfoId(pColInfo->getId());
				}
				//破壊と登録解除
				collisionInfoArray.erase(collisionInfoArray.begin() + i);
				continue;
			}
			// 接触点の更新のために宣言
			ContactInfo contact;
			if (pColInfo->getCol1().expired() || pColInfo->getCol2().expired()) continue;

			if (!pColInfo->getCol1().expired()) pColInfo->getCol1().lock()->update();
			if (!pColInfo->getCol2().expired()) pColInfo->getCol2().lock()->update();

			// 継続して当たっていたら
			if (pColInfo->getCol1().lock()->checkCollide(pColInfo->getCol2().lock().get(), &contact))
			{
				if (!pColInfo->getColliding())
				{
					pColInfo->firstCollision();
				}
				else
				{
					pColInfo->secondCollision();
				}
				// その他接触点などの設定
				// 更新された接触情報で状態を上書き
				pColInfo->setStatus(contact);


			}
			// 当たっていない場合
			else
			{
				if (pColInfo->getExit())
				{
					pColInfo->noCollide();
				}
				else if(pColInfo->getColliding())
				{
					pColInfo->exitCollision();
				}

				//pColInfo->setStatus(contact);
				
			}
		}
	}
}

// idから検索して削除する関数
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

}

// すでに接触情報が保存されている場合に弾く間数
bool CollisionManager::knownReject(int idBase, int idTarget)
{
	for (int i = 0; i < collisionInfoArray.size(); i++)
	{
		CollisionInfo* pColInfo = collisionInfoArray[i].get();
		if (pColInfo != NULL)
		{
			if (pColInfo->getObjectIdCol1() == idBase && pColInfo->getObjectIdCol2() == idTarget)
			{
				return true;
			}
			if (pColInfo->getObjectIdCol1() == idTarget && pColInfo->getObjectIdCol2() == idBase)
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
	collisionInfoArray.clear();
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


int CollisionManager::generateInfoId()
{
	return infoId++;
}
