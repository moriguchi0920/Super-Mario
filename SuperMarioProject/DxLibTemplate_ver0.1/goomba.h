#pragma once

#include"entityObject.h"


class Goomba : public Object
{
public:
	Goomba(Rect rect);
	virtual ~Goomba();


public:

	void update() override;

	void eventProc(int from, std::string name, std::vector<Event::DataMap> datas) override;

	void activateProc() override;

	void deactivateProc() override;

	void deathProc() override;
};
