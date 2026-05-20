#pragma once
#include<memory>
class Object;

class Component
{
protected:
	int entityId;


public:
	Component(int id);

	int getParentId();


	virtual ~Component();

};