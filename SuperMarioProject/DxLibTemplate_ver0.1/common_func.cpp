#include"const.h"
#include"dxlib.h"
#include<math.h>
#include"common_func.h"


//---------------------------------------------------------------------------------
//	型によらず値を入力された最小値、最大値に補正する
//---------------------------------------------------------------------------------

int fix(int val, int min, int max)
{
	int ret = val;
	if (ret < min)
	{
		ret = min;
	}
	if (max < ret)
	{
		ret = max;
	}
	return ret;
}


int MouseLeftFrame;
int MouseRightFrame;

//---------------------------------------------------------------------------------
//	マウスが押されているかを取得する
//---------------------------------------------------------------------------------
bool CheckMouseInput(int button)
{
	if (GetMouseInput() & button) {
		return true;
	}
	return false;
}



//---------------------------------------------------------------------------------
//	マウスの座標を取得する
//---------------------------------------------------------------------------------
void GetMouseXnY(Point* pPoint)
{
	int mouse_x;
	int mouse_y;
	GetMousePoint(&mouse_x, &mouse_y);
	pPoint->x = (float)mouse_x;
	pPoint->y = (float)mouse_y;
}
// 二点間の距離の取得
float GetDistance(float x1, float y1, float x2, float y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));


}
// 二点間の距離の取得(Point版)
float GetDistance(Point pos1, Point  pos2)
{
	float x = pos1.x - pos2.x;
	float y = pos1.y - pos2.y;

	return sqrt(x * x + y * y);


}



//---------------------------------------------------------------------------------
//	点同士の当たり判定
//---------------------------------------------------------------------------------
bool CheckPointHit(Point p1, Point p2, ContactInfo* pContact)
{
	if (p1.x == p2.x && p1.y == p2.y)
	{
		return true;
	}
	return false;
}


//---------------------------------------------------------------------------------
//	円同士の当たり判定
//---------------------------------------------------------------------------------
bool CheckCircleHit(float x1, float y1, float r1, float x2, float y2, float r2)
{
	float distance = GetDistance(x1, y1, x2, y2);
	float radius = r1 + r2;
	if (distance <= radius) {
		return true;
	}
	return false;
}
bool CheckCircleHit(Circle c1, Circle c2, ContactInfo* pContact)
{
	float distance = GetDistance(c1.pos.x, c1.pos.y, c2.pos.x, c2.pos.y);
	float radius = c1.radius + c2.radius;
	if (distance <= radius) {
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	点と円の当たり判定
//---------------------------------------------------------------------------------
bool CheckPointCircleHit(float point_x, float point_y, float circle_x, float circle_y, float circle_r)
{
	float distance = GetDistance(point_x, point_y, circle_x, circle_y);
	if (distance <= circle_r) {
		return true;
	}
	return false;
}
bool CheckPointCircleHit(Point p1, Circle c1, ContactInfo* pContact )
{
	float distance = GetDistance(p1.x, p1.y, c1.pos.x, c1.pos.y);
	if (distance <= c1.radius) {
		return true;
	}
	return false;
}



//---------------------------------------------------------------------------------
//	四角同士の当たり判定
//---------------------------------------------------------------------------------
bool CheckBoxHit(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	if (x1 + w1 >= x2 && x1 <= x2 + w2) {
		if (y1 + h1 >= y2 && y1 <= y2 + h2) {
			return true;
		}
	}
	return false;
}
bool CheckBoxHit(Rect b1, Rect b2, ContactInfo* pContact)
{
	if (b1.begin.x + b1.size.x >= b2.begin.x && b1.begin.x <= b2.begin.x + b2.size.x) {
		if (b1.begin.y  + b1.size.y >= b2.begin.y && b1.begin.y <= b2.begin.y + b2.size.y) {
			return true;
		}
	}
	return false;
}

//---------------------------------------------------------------------------------
//	点と四角の当たり判定
//---------------------------------------------------------------------------------
bool CheckPointBoxHit(float point_x, float point_y, float box_x, float box_y, float box_w, float box_h)
{
	if (point_x >= box_x && point_x <= box_x + box_w) {
		if (point_y >= box_y && point_y <= box_y + box_h) {
			return true;
		}
	}
	return false;
}
bool CheckPointBoxHit(Point p1, Rect b1, ContactInfo* pContact)
{
	if (p1.x >= b1.begin.x && p1.x <= b1.begin.x + b1.size.x) {
		if (p1.y >= b1.begin.y && p1.y <= b1.begin.y + b1.size.y) {
			return true;
		}
	}
	return false;
}

//---------------------------------------------------------------------------------
//	円と四角の当たり判定
//---------------------------------------------------------------------------------
bool CheckCircleBoxHit(float circle_x, float circle_y, float circle_r, float box_x, float box_y, float box_w, float box_h)
{
	float near_x = circle_x;
	if (near_x < box_x)			near_x = box_x;
	if (near_x > box_x + box_w)	near_x = box_x + box_w;

	float near_y = circle_y;
	if (near_y < box_y)			near_y = box_y;
	if (near_y > box_y + box_h)	near_y = box_y + box_h;

	if (CheckPointCircleHit(near_x, near_y, circle_x, circle_y, circle_r)) {
		return true;
	}

	return false;
}
bool CheckCircleBoxHit(Circle c1, Rect b1, ContactInfo* pContact)
{
	Point vertex1(b1.begin.x, b1.begin.y);
	Point vertex2(b1.begin.x + b1.size.x, b1.begin.y);
	Point vertex3(b1.begin.x, b1.begin.y + b1.size.y);
	Point vertex4(b1.begin.x + b1.size.x, b1.begin.y + b1.size.y);
	Line side1(vertex1, vertex2);
	Line side2(vertex2, vertex4);
	Line side3(vertex3, vertex4);
	Line side4(vertex3, vertex1);
	if (pContact)
	{
		if (CheckLineCircleHit(side1, c1, pContact))
			return true;
		if (CheckLineCircleHit(side2, c1, pContact))
			return true;
		if (CheckLineCircleHit(side3, c1, pContact))
			return true;
		if (CheckLineCircleHit(side4, c1, pContact))
			return true;

	}



	Point near_pos(c1.pos);
	if (near_pos.x < b1.begin.x)			near_pos.x = b1.begin.x;
	if (near_pos.x > b1.begin.x + b1.size.x)	near_pos.x = b1.begin.x + b1.size.x;

	if (near_pos.y < b1.begin.y)			near_pos.y = b1.begin.y;
	if (near_pos.y > b1.begin.y + b1.size.y)	near_pos.y = b1.begin.y + b1.size.y;

	if (CheckPointCircleHit(near_pos, c1)) {
		return true;
	}

	return false;
}
//---------------------------------------------------------------------------------
//	線同士の当たり判定
//---------------------------------------------------------------------------------
bool CheckLineHit(Line l1, Line l2, ContactInfo* pContact)
{
	// 一次関数の公式
	// 点A,Bがあるとしてその二線を結ぶ方程式は
	// y - Ay = (Ay - By) / (Ax - Bx) * (x - Ax)
	// 変形すると(y - Ay) * (Ax - Bx) - (Ay - By) * (x - Ax) = 0
	// これに判定をしたい線分CDの端二点を代入し、
	// (Cy - Ay) * (Ax - Bx) - (Ay - By) * (Cx - Ax) = ??
	// (Dy - Ay) * (Ax - Bx) - (Ay - By) * (Dx - Ax) = ??
	// 得られた結果を掛け、
	// 負だった場合は端二点は線分ABを境として違う領域に居ることになる。
	// 違う領域にいるだけだと、接触していない可能性がある(線分ABの延長線を境としている可能性)。
	// そのため、同じ判定を線分CDを基準にABを代入して行い、
	// 掛けた結果が両方とも負だった場合は二つの線分の端点が互いに違う領域にいる
	// (交わっている)ことがわかるので、二つの線分の接触判定ができる。
	float s, t;
	// l1基準での交差
	// s, tはそれぞれl1の方程式にl2の端二点を代入したもので、ベクトルの外積でもある
	s = (l1.begin.x - l1.end.x) * (l2.begin.y - l1.begin.y) - (l1.begin.y - l1.end.y) * (l2.begin.x - l1.begin.x);
	t = (l1.begin.x - l1.end.x) * (l2.end.y - l1.begin.y) - (l1.begin.y - l1.end.y) * (l2.end.x - l1.begin.x);
	if (0.0 <= s * t) return false;

	// l2基準での交差
	s = (l2.begin.x - l2.end.x) * (l1.begin.y - l2.begin.y) - (l2.begin.y - l2.end.y) * (l1.begin.x - l2.begin.x);
	t = (l2.begin.x - l2.end.x) * (l1.end.y - l2.begin.y) - (l2.begin.y - l2.end.y) * (l1.end.x - l2.begin.x);
	if (0.0 <= s * t) return false;

	if (pContact)
	{
		// 交差点の座標
		// 今回はl2基準
		// 上で交差判定は終わっているので、
		// 交差していることが確定している
		// よってs-tで割ったs(外積の面積比)を出し、それぞれのベクトルのx, yに足すことで交点座標が出せる
		float x = l2.begin.x + ((l2.end.x - l2.begin.x) * s / (s-t));
		float y = l2.begin.y + ((l2.end.y - l2.begin.y) * s / (s-t));
		Point intersection(x, y);
		pContact->position = intersection;

		pContact->lineColVector1 = GetNormalize(l1.end - l1.begin);
		pContact->lineColVector2 = GetNormalize(l2.end - l2.begin);

		// 当たり判定先が横か縦かの保存
		// (反射板の向きを変更できるようにする準備)
		//if (abs(l2.begin.x - l2.end.x) < 0.01 || abs(l1.begin.x - l1.end.x) < 0.01)
		//{
		//	pContact->crosswise = ContactInfo::CROSSWISE::CROSS_VERTICAL;
		//}
		//else if (abs(l2.begin.y - l2.end.y) < 0.01 || abs(l1.begin.y - l1.end.y) < 0.01)
		//{
		//	pContact->crosswise = ContactInfo::CROSSWISE::CROSS_HORIZONTAL;
		//}
	}

	return true;

}
//---------------------------------------------------------------------------------
//	線と四角の当たり判定
//---------------------------------------------------------------------------------
bool CheckLineBoxHit(Line l1, Rect b1, ContactInfo* pContact )
{


	Point vertex1(b1.begin.x, b1.begin.y);
	Point vertex2(b1.begin.x + b1.size.x, b1.begin.y);
	Point vertex3(b1.begin.x, b1.begin.y + b1.size.y);
	Point vertex4(b1.begin.x + b1.size.x, b1.begin.y + b1.size.y);
	Line side1(vertex1, vertex2);
	Line side2(vertex2, vertex4);
	Line side3(vertex3, vertex4);
	Line side4(vertex3, vertex1);
	if (pContact)
	{
		if (CheckLineHit(side1, l1, pContact))
  			return true;
		if (CheckLineHit(side2, l1, pContact))
			return true;
		if (CheckLineHit(side3, l1, pContact))
			return true;
		if (CheckLineHit(side4, l1, pContact))
			return true;
	}
	else
	{
		if (CheckLineHit(side1, l1))
			return true;
		if (CheckLineHit(side2, l1))
			return true;
		if (CheckLineHit(side3, l1))
			return true;
		if (CheckLineHit(side4, l1))
			return true;

	}
	if (CheckPointBoxHit(l1.begin, b1)) return true;
	if (CheckPointBoxHit(l1.end, b1)) return true;
	return false;
}
//---------------------------------------------------------------------------------
//	線と円の当たり判定
//---------------------------------------------------------------------------------
bool CheckLineCircleHit(Line l1, Circle c1, ContactInfo* pContact)
{
	// 線分の始点から円の中心のベクトル
	Point start_to_center(c1.pos.x - l1.begin.x, c1.pos.y - l1.begin.y);
	// 線分の終点から円の中心のベクトル
	Point end_to_center(c1.pos.x - l1.end.x, c1.pos.y - l1.end.y);
	// 線分の始点から終点のベクトル
	Point start_to_end(l1.end.x - l1.begin.x, l1.end.y - l1.begin.y);
	float dis = GetDistance(l1.begin.x, l1.begin.y, l1.end.x, l1.end.y);
	if (dis <= 1.0) return false;

	// 外積を用いて線分と円の最短距離を求める
	float shortest_dis = (start_to_center.x * start_to_end.y - start_to_end.x * start_to_center.y) / dis;

	// 始点から円の中心、始点から終点のベクトルの内積(なす角のコサイン * ベクトルの長さ)
	float dotS = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;
	// 終点から円の中心、始点から終点のベクトルの内積(なす角のコサイン * ベクトルの長さ)
	float dotE = end_to_center.x * start_to_end.x + end_to_center.y * start_to_end.y;

	if (pContact)
	{
		float lengthStoE = dis;
		float lengthStoC = GetDistance(c1.pos.x, c1.pos.y, l1.begin.x, l1.begin.y);
		float theta = dotS / (lengthStoC * lengthStoE);
		Point roughIntersection(c1.pos.x + shortest_dis * cos(theta), c1.pos.y + shortest_dis * sin(theta));
		pContact->position = roughIntersection;
		if (abs(l1.begin.x - l1.end.x) < 0.01)
		{
			pContact->crosswise = ContactInfo::CROSSWISE::CROSS_VERTICAL;
		}
		else if (abs(l1.begin.y - l1.end.y) < 0.01)
		{
			pContact->crosswise = ContactInfo::CROSSWISE::CROSS_HORIZONTAL;
		}
		pContact->lineColVector1 = l1.end - l1.begin;
	}

	// 最短距離ベクトルの絶対値が円の半径より大きかったら当たっていない
	if (  c1.radius < abs(shortest_dis))
	{
		return false;
	}


	// 内積同士の掛け算した結果が0以下(なす角が鋭角と鈍角になっている)なら当たっている
	if (dotS * dotE <= 0.0)
	{
		return true;
	}
	// 最後に線分の端点と円の中心の長さが円の半径より大きかったら当たっている
	if (GetDistance(l1.begin.x, l1.begin.y, c1.pos.x, c1.pos.y) < c1.radius)
	{
		return true;
	}
	if (GetDistance(l1.end.x, l1.end.y, c1.pos.x, c1.pos.y) < c1.radius)
	{
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	線と点の当たり判定
//---------------------------------------------------------------------------------
bool CheckLinePointHit(Line l1, Point p1, ContactInfo* pContact)
{
	// 線分の始点から点までのベクトル
	Point start_to_point(p1.x - l1.begin.x, p1.y - l1.begin.y);
	// 始点から終点までのベクトル
	Point start_to_end(l1.end.x - l1.begin.x, l1.end.y - l1.begin.y);

	// ベクトルの内積
	float dot = start_to_point.x * start_to_end.x + start_to_point.y * start_to_end.y;
	// 内積が0より下だったら垂線を下ろせない(当たっていない)
	if (dot < 0.0)
	{
		return false;
	}
	// 始点から点までの長さ
	float lengthStoP = GetDistance(p1.x, p1.y, l1.begin.x, l1.begin.y);
	// 始点から終点までの長さ
	float lengthStoE = GetDistance(l1.begin.x, l1.begin.y, l1.end.x, l1.end.y);

	// 垂線の長さは始点から点までの長さ * sin始点から点への角度
	// 上で求めた内積は始点から点 * 始点から終点の長さ * cos始点から点への角度
	// 内積の公式よりベクトルのなす角θを求めるには内積 / 各ベクトルの長さを掛けたもの
	float theta = dot / (lengthStoP * lengthStoE);
	float perpendicular = abs(lengthStoP * sin(theta));

	if (0.1 < perpendicular)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// ディグリー角からラジアン角に
float degToRad(float deg)
{
	return deg / 180 * PI_F;
}
// ラジアン角からディグリー角に
float radToDeg(float rad)
{
	return rad / PI_F * 180;
}

// 二点間の角度から第三引数に指定した範囲にランダムな角度を取る関数
float GetRandomPositiveAngleFromPoint(Point* pPos1, Point* pPos2, float range)
{
	float angle = atan2(pPos2->y - pPos1->y, pPos2->x - pPos1->x);
	float r = degToRad(GetRand(range * 2) - range);
	return angle + r;
	
}

void smoothMoving(Point* pMovingPos, Point* pEndPos, float speed)
{
	float angle = atan2(pMovingPos->y - pEndPos->y, pMovingPos->x - pEndPos->x);
	pMovingPos->x += cos(angle) * speed;
	pMovingPos->y += sin(angle) * speed;
}
// その点が画面外に出ているかの判定
bool isOutScreen(Point pos)
{
	if (pos.x <= -SPRITE_SIZE || WINDOW_WIDTH <= pos.x + SPRITE_SIZE
		|| pos.y <= -SPRITE_SIZE || WINDOW_HEIGHT <= pos.y + SPRITE_SIZE)
	{
		return true;
	}
	return false;
}
//その点が画面外に出ているかの判定(矩形バージョン)
bool isOutScreen(Point pos, Point size)
{
	if (pos.x <= -size.x || WINDOW_WIDTH <= pos.x + size.x
		|| pos.y <= -size.y || WINDOW_HEIGHT <= pos.y + size.y)
	{
		return true;
	}
	return false;
}
bool isOutScreen(Point pos, float r)
{
	if (pos.x <= r * 2 || WINDOW_WIDTH <= pos.x - r * 2
		|| pos.y <= r * 2 || WINDOW_HEIGHT <= pos.y - r * 2)
	{
		return true;
	}
	return false;
}
// 左側にスクロールしたかどうかの判定
bool isScrolled(float pos_x, float width)
{
	if (pos_x <= -width)
	{
		return true;
	}
	return false;
}


// 浮動小数点型のランダムを取る
float getRandomfloatWithDigits(int beforeDecimal, int afterDecimalDigit)
{
	float result = GetRand(beforeDecimal);
	int divideNum = 10;
	for (int i = 0; i < afterDecimalDigit; i++)
	{
		result += GetRand(9) / divideNum;
		divideNum *= 10;
	}
	return result;
}
// ベクトル正規化関数
Vector2D GetNormalize(Vector2D vec)
{
	float length = sqrt(vec.x * vec.x + vec.y * vec.y);
	return vec / length;
}
// ベクトルを法線に変換する関数
Vector2D GetNormal(Vector2D vec)
{
	Vector2D ret;
	ret.x = -vec.y;
	ret.y = vec.x;
	return ret;
}

// ベクトル外積関数
float GetCross(Vector2D vec1, Vector2D vec2)
{
	float ret;
	ret = (vec1.x * vec2.y) - (vec1.y * vec2.x);
	return ret;
}
// ベクトル内積関数
float GetDot(Vector2D vec1, Vector2D vec2)
{
	float ret;
	ret = (vec1.x * vec2.x) + (vec1.y * vec2.y);
	return ret;
}


// ベクトルをあるベクトルをもとに反射する関数
Vector2D specularReflection(Vector2D refVec, Vector2D baseVec)
{
	// 正規化した鏡面ベクトルの法線を出す
	Vector2D NormalizedBaseNormal = GetNormalize(GetNormal(baseVec));

	// 鏡面の法線ベクトルと反射元ベクトルの内積を取り、値が正だったらなす角が鋭角である(同じ方向を向いている)ため
	// ベクトルを反転させ反射する向きに合わせる
	if (0 <  GetDot(NormalizedBaseNormal, refVec))
	{
		NormalizedBaseNormal *= -1;
	}
	// 法線ベクトルの長さを内積で取り、それを正規化ベクトルに掛けることで
	// 反射に使う横移動量のベクトルを出すための対象軸のベクトルを出す
	Vector2D baseNormal = NormalizedBaseNormal * abs(GetDot(refVec, NormalizedBaseNormal));

	// 法線ベクトルと反射元ベクトルを足すことで、鏡面ベクトルに平行なベクトルができる。
	Vector2D parallel = refVec + baseNormal;

	// 法線ベクトルに平行ベクトルを足すことで、反射後のベクトルを出す。
	Vector2D ret = parallel + baseNormal;

	// 後でスカラーを掛けることを考えて正規化
	ret = GetNormalize(ret);
	
	return ret;
	
}
bool isSameOrNegativeVector(Vector2D vec1, Vector2D vec2)
{
	bool ret = false;
	if (abs(vec1.x) - abs(vec2.x) <= 0.01 && abs(vec1.y) - abs(vec2.y) <= 0.01)
	{
		ret = true;
	}
	return ret;
}


