#pragma once
#include "collisionInfo.h"

// 当たり判定マネージャー
// 当たり判定オブジェクトのポインタ配列を保持し、
// 全オブジェクトの当たり判定を行う。
class CollisionManager
{
private:
	CollisionManager();
	CollisionManager& operator = (const CollisionManager& other){}
	CollisionManager(const CollisionManager& other) {}
	static const int COLLISION_GENERATE_START_ID = 32;

private:
	

	// 当たり判定をとる全オブジェクトの二次元配列(種類ごとにオブジェクト最大数分用意)
	std::vector<CollisionObject*> collisionObjectTable[CollisionObject::CollisionMark::COLLISION_MARK_NUM];

	// 接触情報保存配列
	std::vector<std::shared_ptr<CollisionInfo>> collisionInfoArray;

	int lastId;

	int infoId;

public:
	// シングルトン
	static CollisionManager* getInstance();
	~CollisionManager();



	// オブジェクトの追加関数
	void addObject(CollisionObject* _Object);
	// オブジェクトを取り除く関数
	void removeObject(CollisionObject* _pObject);
	// 全部NULLにする関数
	void nullAll();
	// 当たり判定を行う関数
	void flexibleCollision(CollisionObject* Ob1, CollisionObject* Ob2);
	// 当たり判定の更新関数
	void collisionUpdate();

	void deleteInfoFromCol(CollisionObject* pCol);
	// 当たり判定情報の更新関数
	void updateInfo();

	// インデックスから当たり判定情報を検索する関数
	std::weak_ptr<CollisionInfo> getColInfoFromId(int id);

	// すでに情報として保存されている当たり判定を弾く関数
	bool knownReject(CollisionObject* Ob1, CollisionObject* Ob2);


	// IDから当たり判定情報を削除
	void deleteInfoFromId(int id);

	// 当たり判定情報すべてを削除する関数
	void deleteAllInfo();

	int generateId();

	int generateInfoId();
};