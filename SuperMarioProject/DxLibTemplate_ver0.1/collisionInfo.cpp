#include"collisionInfo.h"



CollisionInfo::CollisionInfo(CollisionObject* pBase, CollisionObject* pTarget, int newId)
{
	pCol1 = pBase;
	pCol2 = pTarget;
	crosswise = INFO_VAR_DEFAULT;
	intersection = { 0.0, 0.0 };
	intersection = { 0.0, 0.0 };
	isColliding = false;
	isEnter = false;
	rectCollideSide = INFO_VAR_DEFAULT;
	lineColVector1 = { INFO_VAR_DEFAULT, INFO_VAR_DEFAULT };
	lineColVector2 = { INFO_VAR_DEFAULT, INFO_VAR_DEFAULT };
	id = newId;
}

// CollisionInfoにアクセスする際に当たった相手をもらうための関数
CollisionObject* CollisionInfo::getTarget(CollisionObject* pBase)
{
	if (pBase == getColPtr1())
	{
		return getColPtr2();
	}
	else if (pBase == getColPtr2())
	{
		return getColPtr1();
	}
	return nullptr;
}

CollisionObject* CollisionInfo::getColPtr1()
{

	return pCol1;
}
CollisionObject* CollisionInfo::getColPtr2()
{
	return pCol2;
}
void CollisionInfo::setStatus(ContactInfo contact)
{
	crosswise = contact.crosswise;
	isColliding = true;
	isEnter = true;
	lineColVector1 = contact.lineColVector1;
	lineColVector2 = contact.lineColVector2;
	intersection = contact.position;
	rectCollideSide = contact.side;
}
void CollisionInfo::removeCol(CollisionObject* pCol)
{
	if (this->getColPtr1() == pCol)
	{
		pCol1 = nullptr;

	}
	if (this->getColPtr2() == pCol)
	{
		pCol2 = nullptr;
	}
}

void CollisionInfo::secondCollision()
{
	isColliding = true;
	isEnter = false;
}

bool CollisionInfo::getEnter()
{
	return isEnter;
}

bool CollisionInfo::getColliding()
{
	return isColliding;
}

Point CollisionInfo::getIntersection()
{
	return intersection;
}

Point CollisionInfo::getLineColVector1()
{
	return lineColVector1;
}

Point CollisionInfo::getLineColVector2()
{
	return lineColVector2;
}



int CollisionInfo::getId()
{
	return id;
}
