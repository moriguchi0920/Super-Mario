#pragma once
#include"Float2.h"

// 左上座標を表すFloat2変数と、XYの大きさを表すFloat2変数を保持する
// 四角を表現するクラス
class Rect
{
public:
	// 左上座標
	Float2 begin;
	// 大きさ
	Float2 size;

public:

	// デフォルトコンストラクタ
	Rect();
	// 引数付きコンストラクタ
	Rect(Float2 _leftTop, Float2 _size);



};


