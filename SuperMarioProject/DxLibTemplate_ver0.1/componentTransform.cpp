#include "componentTransform.h"

ComponentTransform::ComponentTransform(int id) : Component(id)
{
	position.Clear();
}

ComponentTransform::~ComponentTransform()
{
}



void ComponentTransform::translate(Float2 _normalizedVector, float _speed)
{
	position += _normalizedVector * _speed;
}



void ComponentTransform::setPosition(Float2 _position)
{
	position = _position;
}

Float2 ComponentTransform::getPosition()
{
	return position;
}
