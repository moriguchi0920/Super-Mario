#ifndef __COMMON_FUNC_H__
#define __COMMON_FUNC_H__

#include "const.h"
#include "common_type.h"
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
bool CheckPointHit(Point p1, Point p2, ContactInfo* pContact = NULL);
bool CheckCircleHit(float x1, float y1, float r1, float x2, float y2, float r2);
bool CheckCircleHit(Circle c1, Circle c2, ContactInfo* pContact = NULL);
bool CheckPointCircleHit(float point_x, float point_y, float circle_x, float circle_y, float circle_r);
bool CheckPointCircleHit(Point p1, Circle c1, ContactInfo* pContact = NULL);
bool CheckBoxHit(Rect b1, Rect b2, ContactInfo* pContact = NULL);
bool CheckBoxHit(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
bool CheckPointBoxHit(Point p1, Rect b1, ContactInfo* pContact = NULL);
bool CheckPointBoxHit(float point_x, float point_y, float box_x, float box_y, float box_w, float box_h);
bool CheckCircleBoxHit(float circle_x, float circle_y, float circle_r, float box_x, float box_y, float box_w, float box_h);
bool CheckCircleBoxHit(Circle c1, Rect b1, ContactInfo* pContact = NULL);

bool CheckLineHit(Line l1, Line l2, ContactInfo* pContact = NULL);
bool CheckLineBoxHit(Line l1, Rect b1, ContactInfo* pContact = NULL);
bool CheckLineCircleHit(Line l1, Circle c1, ContactInfo* pContact = NULL);
bool CheckLinePointHit(Line l1, Point p1, ContactInfo* pContact = NULL);

float radToDeg(float rad);
float degToRad(float deg);

float GetRandomPositiveAngleFromPoint(Point* pPos1, Point* pPos2, float range);
bool isOutScreen(Point pos);
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
