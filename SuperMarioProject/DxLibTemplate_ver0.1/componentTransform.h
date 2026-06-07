#pragma once
#include"componentBase.h"
#include"Float2.h"

class ComponentTransform : public Component
{
protected:
	Float2 position;
	float speed;
	Float2 translation;

	bool isScroll;

public:
	ComponentTransform(int id);
	
	virtual ~ComponentTransform();


	void translate(Float2 _normalizedVector, float _speed);

	void translate(Float2 _normalizedVector);

	void translate();

	void setSpeed(float _speed);

	void setTranslation(Float2 _translation);

	void addTranslation(Float2 add);

	void setPosition(Float2 _position);

	void setPosX(float x);
	void setPosY(float y);

	void setScroll(bool _isScroll);

	Float2 getTranslation();

	float getSpeed();

	Float2 getPosition();

	bool getIsScroll();

	void revertTranslation(float revertRate);

	void revertTranslationX(float revertRate);
	void revertTranslationY(float revertRate);
};