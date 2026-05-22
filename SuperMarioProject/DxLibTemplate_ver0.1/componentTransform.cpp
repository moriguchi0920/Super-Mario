#include "componentTransform.h"

ComponentTransform::ComponentTransform(int id) : Component(id)
{
	position.Clear();
	speed = 0.0f;
}

ComponentTransform::~ComponentTransform()
{
}



void ComponentTransform::translate(Float2 _normalizedVector, float _speed)
{
	position += _normalizedVector * _speed;
}

void ComponentTransform::translate(Float2 _normalizedVector)
{
	position += _normalizedVector * speed;
}

void ComponentTransform::setSpeed(float _speed)
{
	speed = _speed;
}



void ComponentTransform::setPosition(Float2 _position)
{
	position = _position;
}

Float2 ComponentTransform::getPosition()
{
	return position;
}
