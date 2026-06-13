#pragma once
#include"objectManager.h"

class Goal : public Object
{
public:
	Goal(const Rect& rect);
	virtual ~Goal();

	void update() override;
};