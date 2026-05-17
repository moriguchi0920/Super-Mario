#pragma once
#include"common_func.h"

//当たり判定を可視化するための色変更用クラス
class DebugColor
{
public:
	// 赤
	int r;
	// 緑
	int g;
	// 青
	int b;
	// アルファ値
	int a;

	// コンストラクタ
	DebugColor();

	// 引数付きコンストラクタ
	DebugColor(int _r, int _g, int _b);
	// 引数付きコンストラクタ(アルファ値指定あり)
	DebugColor(int _r, int _g, int _b, int _a);

	// 数値の設定
	void set(int _r, int _g, int _b);
	// 数値の設定(アルファ値指定あり)
	void set(int _r, int _g, int _b, int _a);

	// 演算子オーバーロード
	DebugColor& operator + (const DebugColor& otherColor);
	DebugColor& operator - (const DebugColor& otherColor);

	DebugColor& operator * (const double rate);

	bool operator == (const DebugColor& otherColor);
};
