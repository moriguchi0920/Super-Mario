#pragma once

#include"entityObject.h"
#include"Rect.h"

class BlockBase : public Object
{
public: 
	BlockBase(int id, const Rect& rect);
	virtual ~BlockBase();

	virtual void update() override;

};



