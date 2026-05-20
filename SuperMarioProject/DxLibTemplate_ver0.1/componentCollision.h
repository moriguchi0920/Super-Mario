#pragma once

#include"common_func.h"
#include"debug_color.h"
#include"componentTransform.h"
#include "dxlib.h"
#include "const.h"
#include "keyManager.h"
#include"imageManager.h"
#include"Float2.h"
#include"Line.h"
#include"Rect.h"
#include"Circle.h"
#include"componentBase.h"
#include<cmath>
#include<vector>
#include<memory>
#include<stdlib.h>

class ShapeSetParam;
struct ContactInfo;

// 当たり判定用の形クラスたちの基底となるクラス
class ComponentCollisionShape : public Component
{
public:
	enum OBJECTSHAPE
	{
		DEFAULT = -1,
		POINT,
		LINE,
		RECT,
		CIRCLE,

	};

	ComponentCollisionShape(int objectId);
	~ComponentCollisionShape();

protected:
	// CollisionInfo検索用の配列インデックス
	std::vector<int> colInfoId;

	bool isCollide;

public:
	// どんな形をしているかを返す関数
	virtual int getShapeType() = 0;
	// 位置および形ごとのパラメータを更新する関数(最新)
	virtual void paramUpdate(ShapeSetParam* param) = 0;
	// 当たり判定を形ごとで分けて行う関数
	virtual bool checkCollide(ComponentCollisionShape* shape, ContactInfo* pContact = NULL) = 0;

	void setInfoId(int id);
	void removeInfoId(int id);
	std::vector<int> getInfoId();

	bool getIsCollide();
	void setIsCollide(bool _isCollide);
};




// 点の当たり判定
class ComponentCollisionPoint : public ComponentCollisionShape
{
public:
	Point point;
	ComponentCollisionPoint(int objectId);
	ComponentCollisionPoint(int objectId,float _x, float _y);
	ComponentCollisionPoint(int objectId,const Point& pos);

	virtual int getShapeType()
	{
		return POINT;
	}

	virtual void paramUpdate(ShapeSetParam* param);
	virtual bool checkCollide(ComponentCollisionShape* shape, ContactInfo* pContact = NULL);

};

typedef  Point Vector2D;

// 線の当たり判定
class ComponentCollisionLine : public ComponentCollisionShape
{
public:
	Line line;
	ComponentCollisionLine(int objectId);
	ComponentCollisionLine(int objectId,const Point& _begin, const Point& _end);
	ComponentCollisionLine(int objectId,const Line& _line);

	virtual int getShapeType()
	{
		return LINE;
	}

	virtual void paramUpdate(ShapeSetParam* param);
	virtual bool checkCollide(ComponentCollisionShape* shape, ContactInfo* pContact = NULL);

};

// 円の当たり判定
class ComponentCollisionCircle :public ComponentCollisionShape
{
public:
	Circle circle;

	ComponentCollisionCircle(int objectId);
	ComponentCollisionCircle(int objectId,const Point& _pos, float _r);
	ComponentCollisionCircle(int objectId,const Circle& _circle);

	virtual int getShapeType()
	{
		return CIRCLE;
	}


	virtual void paramUpdate(ShapeSetParam* param);
	virtual bool checkCollide(ComponentCollisionShape* shape, ContactInfo* pContact = NULL);
};


// 四角の当たり判定
class ComponentCollisionRect : public ComponentCollisionShape
{
public:
	Rect rect;

	ComponentCollisionRect(int objectId);
	ComponentCollisionRect(int objectId,const Point& _begin, const Point& _size);
	ComponentCollisionRect(int objectId,const Rect& _rect);

	virtual int getShapeType()
	{
		return RECT;
	}


	virtual void paramUpdate(ShapeSetParam* param);
	virtual bool checkCollide(ComponentCollisionShape* shape, ContactInfo* pContact = NULL);

};

// 形ごとのパラメータ
struct ParamPoint
{
	Point point;
};
struct ParamR
{
	float r;
};
struct ParamPoint2
{
	Point point1;
	Point point2;
};
struct ParamCircle
{
	Point point;
	float r;
};


// 各Shape系オブジェクトの座標等のパラメータ設定用のクラス
class ShapeSetParam
{
public:
	enum ParamType
	{
		PT_XY,
		PT_WH,
		PT_RECT,
		PT_R,
		PT_CIRCLE,
		PT_LINE_BEGIN,
		PT_LINE_END,
		PT_LINE_BOTH,
	};

	ShapeSetParam(ShapeSetParam::ParamType type);
	int paramType;
	union Param
	{
		Param();
		ParamPoint paramPoint;
		ParamR paramR;
		ParamPoint2 paramPoint2;
		ParamCircle paramCircle;
	} param;
};








