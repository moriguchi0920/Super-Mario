#pragma once
#include "collisionInfo.h"

#include<vector>
#include<memory>

// 当たり判定マネージャー
// 当たり判定コンポーネントをComponentManagerから取り出し、
// 全オブジェクトの当たり判定を行う。
class CollisionManager
{
private:
	CollisionManager();
	CollisionManager& operator = (const CollisionManager& other){}
	CollisionManager(const CollisionManager& other) {}
	static const int COLLISION_GENERATE_START_ID = 32;

private:
	

	// 接触情報保存配列
	static std::vector<std::shared_ptr<CollisionInfo>> collisionInfoArray;


	int infoId;

public:
	// シングルトン
	static CollisionManager* getInstance();
	~CollisionManager();


	// 当たり判定を行う関数
	void flexibleCollision();
	// 当たり判定の更新関数
	void collisionUpdate();

	
	// 当たり判定情報の更新関数
	void updateInfo();

	// インデックスから当たり判定情報を検索する関数
	static std::weak_ptr<CollisionInfo> getColInfoFromId(int id);

	// すでに情報として保存されている当たり判定を弾く関数
	bool knownReject(int idBase, int idTarget);


	// IDから当たり判定情報を削除
	void deleteInfoFromId(int id);

	// 当たり判定情報すべてを削除する関数
	void deleteAllInfo();


	int generateInfoId();
};