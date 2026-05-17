#pragma once

#include "dxlib.h"
#include "const.h"
#include "keyManager.h"
#include"imageManager.h"
#include"Float2.h"
#include"Line.h"
#include"Rect.h"
#include"Circle.h"
#include<cmath>
#include<vector>
#include<memory>
#include<stdlib.h>

class ShapeSetParam;
struct ContactInfo;

// 当たり判定用の形クラスたちの基底となるクラス
class CollisionShape
{
	public:
		enum OBJECTSHAPE
		{
			DEFAULT = -1,
			POINT,
			LINE,
			RECT,
			CIRCLE,
			OVAL,
		};
	protected :

		//OBJECTSHAPE m_type;

		//Point	pos;
		//Point	size;
		//float	r;

	public:
		// どんな形をしているかを返す関数
		virtual int getShapeType() = 0;
		// 位置および形ごとのパラメータを更新する関数(最新)
		virtual void paramUpdate(ShapeSetParam* param) = 0;
		// 当たり判定を形ごとで分けて行う関数
		virtual bool checkCollide(CollisionShape* shape, ContactInfo* pContact = NULL) = 0;
};




// 点の当たり判定
class CPoint: public CollisionShape
{
	public:
		Point point;
		CPoint();
		CPoint(float _x, float _y);
		CPoint(const Point& pos);

		virtual int getShapeType()
		{
			return POINT;
		}

		virtual void paramUpdate(ShapeSetParam* param);
		virtual bool checkCollide(CollisionShape* shape, ContactInfo* pContact = NULL);

};

typedef  Point Vector2D;

// 線の当たり判定
class CLine : public CollisionShape
{
public:
	Line line;
	CLine();
	CLine(const Point& _begin, const Point& _end);
	CLine(const Line& _line);

	virtual int getShapeType()
	{
		return LINE;
	}

	virtual void paramUpdate(ShapeSetParam* param);
	virtual bool checkCollide(CollisionShape* shape, ContactInfo* pContact = NULL);

};

// 円の当たり判定
class CCircle :public CollisionShape
{
	public:
		Circle circle;

		CCircle();
		CCircle(const Point& _pos, float _r);
		CCircle(const Circle& _circle);

		virtual int getShapeType()
		{
			return CIRCLE;
		}


		virtual void paramUpdate(ShapeSetParam* param);
		virtual bool checkCollide(CollisionShape* shape, ContactInfo* pContact = NULL);
};


// 四角の当たり判定
class CRect  : public CollisionShape
{
	public:
		Rect rect;

		CRect();
		CRect(const Point& _begin, const Point& _size);
		CRect(const Rect& _rect);

		virtual int getShapeType()
		{
			return RECT;
		}


		virtual void paramUpdate(ShapeSetParam* param);
		virtual bool checkCollide(CollisionShape* shape, ContactInfo* pContact = NULL);

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

// 後々CollisionInfoに入れる情報をまとめた構造体
struct ContactInfo
{
	enum RECTCOLLIDESIDE
	{
		SIDE_DEFAULT = -1,
		SIDE_TOP,
		SIDE_RIGHT,
		SIDE_BOTTOM,
		SIDE_LEFT,
	};
	enum CROSSWISE
	{
		CROSS_DEFAULT = -1,
		CROSS_HORIZONTAL,
		CROSS_VERTICAL,
	};
	ContactInfo();

	Point position;
	bool hadContact;
	int side;
	int crosswise;
	Point lineColVector1;
	Point lineColVector2;
};

//void func()
//{
//	ShapeSetParam sp = {0};
//	sp.paramType = ShapeSetParam::PT_LINE_BEGIN;
//	sp.param.paramPoint.point.x= 0;
//
//}