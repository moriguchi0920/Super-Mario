#include"collisionInfo.h"
#include"objectManager.h"


CollisionInfo::CollisionInfo(std::weak_ptr<ComponentCollisionShape> pColBase, std::weak_ptr<ComponentCollisionShape> pColTarget, int newInfoId)
{
	col1 = pColBase;
	col2 = pColTarget;
	intersection = { 0.0, 0.0 };
	intersection = { 0.0, 0.0 };
	rectCollideSide = -1;
	crosswise = -1;
	isColliding = false;
	isEnter = false;
	penetrateRate = 1.0f;
	id = newInfoId;
}

// CollisionInfoにアクセスする際に当たった相手をもらうための関数
std::weak_ptr<ComponentCollisionShape> CollisionInfo::getTarget(int idBase)
{
	 if (idBase == getObjectIdCol1())
	 {
		 return col2;
	 }
	 else if(idBase == getObjectIdCol2())
	 {
		 return col1;
	 }
	 else
	 {
		 return std::weak_ptr<ComponentCollisionShape>();
	 }

}



 int CollisionInfo::getObjectIdCol1()
 {
	 if (col1.expired()) return -1;
	 return col1.lock()->getParentId();
 }

 int CollisionInfo::getObjectIdCol2()
 {
	 if (col2.expired()) return -1;
	 return col2.lock()->getParentId();
 }

 std::weak_ptr<ComponentCollisionShape> CollisionInfo::getCol1()
 {
	 return col1;
 }

 std::weak_ptr<ComponentCollisionShape> CollisionInfo::getCol2()
 {
	 return col2;
 }



void CollisionInfo::setStatus(ContactInfo contact)
{
	crosswise = contact.crosswise;
	isColliding = true;
	isEnter = true;
	penetrateRate = contact.penetrateRate;
	lineColVector1 = contact.lineColVector1;
	lineColVector2 = contact.lineColVector2;
	intersection = contact.position;
	rectCollideSide = contact.side;
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

int CollisionInfo::getRectCollideSide()
{
	return rectCollideSide;
}



int CollisionInfo::getId()
{
	return id;
}

float CollisionInfo::getPenetrateRate()
{
	return penetrateRate;
}
