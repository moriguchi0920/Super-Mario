#pragma once
#include"objectManager.h"

class SampleObject : public Object
{
public:
	SampleObject();
	virtual ~SampleObject();

	void update() override;
};