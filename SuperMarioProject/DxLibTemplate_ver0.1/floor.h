#pragma once
#include"entityObject.h"


class Floor : public Object
{
public:
	Floor();
	virtual ~Floor();

	void update() override;

};
