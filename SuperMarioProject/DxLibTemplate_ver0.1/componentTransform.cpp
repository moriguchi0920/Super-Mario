#include "componentTransform.h"

ComponentTransform::ComponentTransform(int id) : Component(id)
{
	position.Clear();
	speed = 0.0f;
	translation.Clear();
	isScroll = false;
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

void ComponentTransform::translate()
{
	position += translation * speed;
}

void ComponentTransform::setSpeed(float _speed)
{
	speed = _speed;
}

void ComponentTransform::setTranslation(Float2 _translation)
{
	translation = _translation;
}



void ComponentTransform::setPosition(Float2 _position)
{
	position = _position;
}

void ComponentTransform::setScroll(bool _isScroll)
{
	isScroll = _isScroll;
}

Float2 ComponentTransform::getTranslation()
{
	return translation;
}

float ComponentTransform::getSpeed()
{
	return speed;
}

Float2 ComponentTransform::getPosition()
{
	return position;
}

bool ComponentTransform::getIsScroll()
{
	return isScroll;
}
