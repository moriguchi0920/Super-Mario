#pragma once

#include "entityObject.h"
#include "componentGravity.h"
#include "componentCollision.h"
#include "componentRenderable.h"


class Coin : public Object
{
public:
	Coin(Rect rect);
	virtual ~Coin();

	void update() override;

	void eventProc(int from, std::string name, std::vector<Event::DataMap> datas) override;

	void activateProc() override;

	void deactivateProc() override;

	void deathProc() override;
};