#pragma once


#include"entityObject.h"


class SuperMushroom : public Object
{
public:
	SuperMushroom(Rect rect);
	virtual ~SuperMushroom();


public:

	void update() override;

	void eventProc(int from, std::string name, std::vector<Event::DataMap> datas) override;

	void activateProc() override;

	void deactivateProc() override;

	void deathProc() override;
};