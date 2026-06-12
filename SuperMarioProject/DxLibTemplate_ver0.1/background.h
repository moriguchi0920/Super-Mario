#pragma once
#include "objectManager.h"
#include "Rect.h"

class Background : public Object
{
public:
	enum Type {
		CLOUD_1,
		CLOUD_2,
		CLOUD_3,
		MOUNTAIN_1,
		MOUNTAIN_2,
		PLANT_1,
		PLANT_2,
		PLANT_3,
	};

	Background();
	virtual ~Background();
	void update() override;

	static void setNextInfo(Type type, Point pos) {
		g_nextType = type;
		g_nextPos = pos; 
	}

private:
	static Type g_nextType;
	static Point g_nextPos; 
};