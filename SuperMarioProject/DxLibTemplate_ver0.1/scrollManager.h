#pragma once

#include"Float2.h"

// スクロールする座標コンポーネントすべてをスクロールさせるマネージャ
class ScrollManager
{
private:
	float scrollOffset;
	


public:
	static ScrollManager* getInstance();

	void scrollAll();
	void setScrollOffset(float offset);




private:
	ScrollManager();
	ScrollManager& operator = (const ScrollManager& other) = delete;
	ScrollManager(const ScrollManager& other) = delete;



};