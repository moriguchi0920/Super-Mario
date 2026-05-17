#pragma once
#include"collision.h"

// 当たり判定の接触情報をまとめて一時保存するクラス
// 当たり判定が発生するときにこのクラスのオブジェクトを作り、
// 接触点や四角の辺、今までに当たったかどうか、
// 今当たっているか、接触した瞬間などを保存する。
class CollisionInfo
{
public:
	// コンストラクタ
	CollisionInfo(CollisionObject* pBase, CollisionObject* pTarget,int _newId);

	// あたった相手を検索する関数
	CollisionObject* getTarget(CollisionObject* pBase);
	// 当たり判定情報に保存されている当たり判定オブジェクトの一つ目を返す関数
	CollisionObject* getColPtr1();
	// 当たり判定情報に保存されている当たり判定オブジェクトの二つ目を返す関数
	CollisionObject* getColPtr2();

	// 指定されたポインタがあった場合当たり判定情報から取り除き、削除する準備をする
	void removeCol(CollisionObject* pCol);
	// 初期作成時値を設定する関数
	void setStatus(ContactInfo contact);
	// 二回目以降に当たった場合に、Enterをfalseにする
	void secondCollision();

	bool getEnter();

	bool getColliding();

	Point getIntersection();

	Point getLineColVector1();

	Point getLineColVector2();


	int getId();

private:
	// 当たったオブジェクト同士
	CollisionObject* pCol1;
	CollisionObject* pCol2;
	// 今当たっているか
	bool isColliding;
	// 当たった瞬間かどうか
	bool isEnter;
	// 接触点
	Point intersection;
	// 四角形のどの辺に当たったか
	int rectCollideSide;
	// 横線、縦線のどちらに当たったか(反射板や壁での反射用)
	int crosswise;

	Point lineColVector1;
	Point lineColVector2;

	int id;
};
