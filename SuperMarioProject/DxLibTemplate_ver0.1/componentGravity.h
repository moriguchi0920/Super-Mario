#pragma once
#include"componentTransform.h"


class ComponentGravity : public ComponentTransform
{
public:
	ComponentGravity(int id, float acceleration = 0.10f, float terminal = 15.0f);
	virtual ~ComponentGravity();

protected:
	float gravitationalAcceleration;

	float terminalVelocity;

	bool isLanding;

	float nowVelocity;

public:
	void setAcceleration(float acceleration);

	void setTerminal(float terminal);

	void setLanding(bool isLand);

	void gravityUpdate();
};
