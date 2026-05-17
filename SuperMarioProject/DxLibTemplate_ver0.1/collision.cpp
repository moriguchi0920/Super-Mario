#include"collision.h"

// コンストラクタ
CollisionObject::CollisionObject()
{
	damage = 1;
	isCollide = true;
}
// デストラクタ
CollisionObject::~CollisionObject()
{


}

void CollisionObject::setInfoId(int id)
{
	colInfoId.push_back(id);
}

void CollisionObject::removeInfoId(int id)
{
	if (colInfoId.size() <= 0) return;

	auto it = std::find(colInfoId.begin(), colInfoId.end(), id);
	if (it == colInfoId.end()) return;
	colInfoId.erase(it);
}
std::vector<int> CollisionObject::getInfoId()
{


	return colInfoId;
}
void CollisionObject::setShape(CollisionShape* _pShape)
{
	pShape.reset(_pShape);
}

CollisionShape* CollisionObject::getShape()
{
	return pShape.get();
}

void CollisionObject::setIsCollide(bool _isCollide)
{
	isCollide = _isCollide;
}

bool CollisionObject::getIsCollide()
{
	return isCollide;
}



void CollisionObject::setDamage(int _damage)
{
	damage = _damage;
}
int CollisionObject::getDamage()
{
	return damage;
}

CollisionObject::CollisionMark CWall::getMark()
{
	return CollisionMark::WALL;
}

bool CWall::isCollideTarget(CollisionMark mark)
{
	bool ret = false;

	if (mark == CollisionMark::BUBBLE)
	{
		ret = true;
	}

	return ret;
}

CollisionObject::CollisionMark CCeiling::getMark()
{
	return CollisionMark::CEILING;
}

bool CCeiling::isCollideTarget(CollisionMark mark)
{
	bool ret = false;

	if (mark == CollisionMark::BUBBLE)
	{
		ret = true;
	}

	return ret;

}

CollisionObject::CollisionMark CBubble::getMark()
{
	return CollisionMark::BUBBLE;
}

bool CBubble::isCollideTarget(CollisionMark mark)
{
	bool ret = false;

	if (mark == CollisionMark::BUBBLE || mark == CollisionMark::WALL || mark == CollisionMark::CEILING)
	{
		ret = true;
	}

	return ret;

}
CollisionObject::CollisionMark CStageBubble::getMark()
{
	return CollisionMark::STAGEBUBBLE;
}

bool CStageBubble::isCollideTarget(CollisionMark mark)
{
	bool ret = false;

	if (mark == CollisionMark::SHOOTBUBBLE)
	{
		ret = true;
	}

	return ret;

}
CollisionObject::CollisionMark CShootBubble::getMark()
{
	return CollisionMark::SHOOTBUBBLE;
}

bool CShootBubble::isCollideTarget(CollisionMark mark)
{
	bool ret = false;

	if (mark == CollisionMark::STAGEBUBBLE || mark == CollisionMark::CEILING || mark == CollisionMark::WALL)
	{
		ret = true;
	}

	return ret;

}
