#pragma once
#include"componentCollision.h"

// 当たり判定の接触情報をまとめて一時保存するクラス
// 当たり判定が発生するときにこのクラスのオブジェクトを作り、
// 接触点や四角の辺、今までに当たったかどうか、
// 今当たっているか、接触した瞬間などを保存する。
class CollisionInfo
{
public:
	// コンストラクタ
	CollisionInfo(std::weak_ptr<ComponentCollisionShape> pColBase, std::weak_ptr<ComponentCollisionShape> pColTarget, int _newInfoId);

	// あたった相手を検索する関数
	std::weak_ptr<ComponentCollisionShape>  getTarget(int idBase);

	int getObjectIdCol1();
	int getObjectIdCol2();

	std::weak_ptr<ComponentCollisionShape> getCol1();
	std::weak_ptr<ComponentCollisionShape> getCol2();

	// 初期作成時値を設定する関数
	void setStatus(ContactInfo contact);
	void firstCollision();
	// 二回目以降に当たった場合に、Enterをfalseにする
	void secondCollision();
	void exitCollision();

	void noCollide();

	bool getEnter();

	bool getColliding();

	bool getExit();

	Point getIntersection();

	Point getLineColVector1();

	Point getLineColVector2();

	int getRectCollideSide();

	int getId();

	float getPenetrateRate();

private:
	// 当たったオブジェクト同士
	std::weak_ptr<ComponentCollisionShape> col1;
	std::weak_ptr<ComponentCollisionShape> col2;

	// 今当たっているか
	bool isColliding;
	// 当たった瞬間かどうか
	bool isEnter;
	// 当たりを抜けたか
	bool isExit;
	// 接触点
	Point intersection;
	// 四角形のどの辺に当たったか
	int rectCollideSide;
	// 横線、縦線のどちらに当たったか(反射板や壁での反射用)
	int crosswise;

	float penetrateRate;

	Point lineColVector1;
	Point lineColVector2;

	int id;
};
