#pragma once
#include"entityObject.h"
#include"blockBase.h"

class Floor : public BlockBase
{
	enum Type {
		Ground1,
		Ground2,
		Ground3,
		Ground4
	};

public:
	Floor(float x, float width);
	virtual ~Floor();

	void update() override;

private:
	static Type g_nextType;
	static Point g_nextPos;

};
