#pragma once
#include "objectManager.h"

class Background : public Object
{
public:
	Background();
	virtual ~Background();

	void update() override;
};