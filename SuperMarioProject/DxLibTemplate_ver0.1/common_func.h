#ifndef __COMMON_FUNC_H__
#define __COMMON_FUNC_H__

#include "const.h"

#include"Float2.h"
#include"Line.h"
#include"Circle.h"
#include"Rect.h"
// å„ÅXCollisionInfoÇ…ì¸ÇÍÇÈèÓïÒÇÇ‹Ç∆ÇﬂÇΩç\ë¢ëÃ
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

template <typename _T_>
inline void fixValue(_T_* pValue, _T_ min, _T_ max)
{
	if (*pValue < min)
	{
		*pValue = min;
	}
	if (max < *pValue)
	{
		*pValue = max;
	}
}
int fix(int val, int min, int max);

bool CheckMouseInput(int button);
void GetMouseXnY(Point* pPoint);
float GetDistance(float x1, float y1, float x2, float y2);
float GetDistance(Point pos1, Point  pos2);
bool CheckPointHit(Point p1, Point p2, ContactInfo* pContact = nullptr);
bool CheckCircleHit(float x1, float y1, float r1, float x2, float y2, float r2);
bool CheckCircleHit(Circle c1, Circle c2, ContactInfo* pContact = nullptr);
bool CheckPointCircleHit(float point_x, float point_y, float circle_x, float circle_y, float circle_r);
bool CheckPointCircleHit(Point p1, Circle c1, ContactInfo* pContact = nullptr);
bool CheckBoxHit(Rect b1, Rect b2, ContactInfo* pContact = nullptr);
bool CheckBoxHit(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
bool CheckPointBoxHit(Point p1, Rect b1, ContactInfo* pContact = nullptr);
bool CheckPointBoxHit(float point_x, float point_y, float box_x, float box_y, float box_w, float box_h);
bool CheckCircleBoxHit(float circle_x, float circle_y, float circle_r, float box_x, float box_y, float box_w, float box_h);
bool CheckCircleBoxHit(Circle c1, Rect b1, ContactInfo* pContact = nullptr);

bool CheckLineHit(Line l1, Line l2, ContactInfo* pContact = nullptr);
bool CheckLineBoxHit(Line l1, Rect b1, ContactInfo* pContact = nullptr);
bool CheckLineCircleHit(Line l1, Circle c1, ContactInfo* pContact = nullptr);
bool CheckLinePointHit(Line l1, Point p1, ContactInfo* pContact = nullptr);

float radToDeg(float rad);
float degToRad(float deg);

float GetRandomPositiveAngleFromPoint(Point* pPos1, Point* pPos2, float range);
bool isOutScreen(Point pos, Point size);
bool isOutScreen(Point pos, float r);
bool isScrolled(float pos_x, float width);
float getRandomfloatWithDigits(int beforeDecimal, int afterDecimalDigit);

Vector2D GetNormalize(Vector2D vec);
Vector2D GetNormal(Vector2D vec);
float GetCross(Vector2D vec1, Vector2D vec2);
float GetDot(Vector2D vec1, Vector2D voec2);
Vector2D specularReflection(Vector2D refVec, Vector2D baseVec);
bool isSameOrNegativeVector(Vector2D vec1, Vector2D vec2);

#endif
