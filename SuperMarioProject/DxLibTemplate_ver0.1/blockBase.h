#pragma once

#include"entityObject.h"
#include"Rect.h"

class BlockBase : public Object
{
public: 
	BlockBase( const Rect& rect);
	virtual ~BlockBase();

	virtual void update() override;
	virtual void eventProc(int from, std::string name, std::vector<Event::DataMap> datas) override;
	virtual void hitFromBottom();

};



