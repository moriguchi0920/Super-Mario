#pragma once

#include"Float2.h"

// 2つのFloat2を内包し、線を表現するクラス
class Line
{
public:
	// 始点
	Float2 begin;
	// 終点
	Float2 end;


public:

	// デフォルトコンストラクタ
	Line();
	// 引数付きコンストラクタ
	Line(Float2 _begin, Float2 _end);

	// 長さの取得関数
	float GetLength();


};
