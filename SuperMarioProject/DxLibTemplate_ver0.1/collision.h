#pragma once
#include"common_type.h"
#include"common_func.h"
#include"debug_color.h"

// 全てのオブジェクトの当たり判定の種類、種類ごとに当たるかどうか、今当たっているかどうか、当たった相手を保存するクラス
class CollisionObject
{

protected:
	// 形オブジェクトのポインタ
	std::unique_ptr<CollisionShape> pShape;

	// CollisionInfo検索用の配列インデックス
	std::vector<int> colInfoId;
	// 当たった時のダメージ
	int damage;
	// 当たり判定をとるかどうか(無敵などの処理用)
	bool isCollide;

	public:
		enum CollisionMark
		{
			DEFAULT = -1,
			WALL,
			CEILING,
			BUBBLE,
			STAGEBUBBLE,
			SHOOTBUBBLE,
			COLLISION_MARK_NUM
		};
		
		CollisionObject();
		virtual ~CollisionObject();
		virtual CollisionMark getMark() = 0;
		virtual bool isCollideTarget(CollisionMark mark) = 0;
		void setInfoId(int id);
		void removeInfoId(int id);
		std::vector<int> getInfoId();
		CollisionShape* getShape();
		void setShape(CollisionShape* _pShape);
		bool getIsCollide();
		void setDamage(int _damage);
		int getDamage();
		void setIsCollide(bool _isCollide);


public:
		// 当たり判定描画用の色
		DebugColor color;
};

class CWall : public CollisionObject
{
public:
	virtual CollisionMark getMark() override;
	virtual bool isCollideTarget(CollisionMark mark) override;
};

class CCeiling : public CollisionObject
{
public:
	virtual CollisionMark getMark() override;
	virtual bool isCollideTarget(CollisionMark mark) override;
};

class CBubble : public CollisionObject
{
public:
	virtual CollisionMark getMark() override;
	virtual bool isCollideTarget(CollisionMark mark) override;
};


class CStageBubble : public CBubble
{
public:
	virtual CollisionMark getMark() override;
	virtual bool isCollideTarget(CollisionMark mark) override;
};

class CShootBubble : public CBubble
{
public:
	virtual CollisionMark getMark() override;
	virtual bool isCollideTarget(CollisionMark mark) override;
};



