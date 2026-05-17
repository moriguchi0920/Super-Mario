#pragma once
#include"Float2.h"

// 中心座標を表すFloat2変数と、半径を表すfloat変数を保持する
// 円を表現するクラス
class Circle
{
public:
	// 中心座標
	Float2 pos;
	// 半径
	float radius;

public:
	// デフォルトコンストラクタ
	Circle();
	// 引数付きコンストラクタ
	Circle(Float2 _pos, float _radius);

};
