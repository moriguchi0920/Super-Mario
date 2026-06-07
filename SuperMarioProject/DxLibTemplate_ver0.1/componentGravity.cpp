#include "componentGravity.h"

ComponentGravity::ComponentGravity(int id, float acceleration, float terminal): ComponentTransform(id)
{
	gravitationalAcceleration = acceleration;
	terminalVelocity = terminal;
	isLanding = true;
	nowVelocity =0.0f;
}

ComponentGravity::~ComponentGravity()
{
}

void ComponentGravity::setAcceleration(float acceleration)
{
	gravitationalAcceleration = acceleration;
}

void ComponentGravity::setTerminal(float terminal)
{
	terminalVelocity = terminal;
}

void ComponentGravity::setLanding(bool isLand)
{
	isLanding = isLand;
}


void ComponentGravity::gravityUpdate()
{
	if (!isLanding)
	{
		if (nowVelocity <= terminalVelocity)
		{
			translation.y += gravitationalAcceleration;
		}

		nowVelocity = translation.y;
	}
	else
	{
		nowVelocity =0.0f;
		translation.y =0.0f;
	}
}


bool ComponentGravity::getLanding()
{
	return isLanding;
}
