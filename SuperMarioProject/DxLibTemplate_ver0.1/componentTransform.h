#pragma once
#include"componentBase.h"
#include"Float2.h"

class ComponentTransform : public Component
{
protected:
	Float2 position;

public:
	ComponentTransform(int id);
	virtual ~ComponentTransform();


	void translate(Float2 _normalizedVector, float _speed);

	void setPosition(Float2 _position);

	Float2 getPosition();

};