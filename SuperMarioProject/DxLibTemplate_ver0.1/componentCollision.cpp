#include"componentCollision.h"
#include"componentTransform.h"
#include"collisionManager.h"

// コンストラクタ
ComponentCollisionShape::ComponentCollisionShape(int objectId) : Component(objectId)
{
	prevPos = Point(0.0f, 0.0f);
}
// デストラクタ
ComponentCollisionShape::~ComponentCollisionShape()
{


}

void ComponentCollisionShape::addTag(int _tag)
{
	switch (_tag)
	{
	case ICollisionTag::TAG::FLOOR:
		collisionTag = std::make_unique<CollisionTagFloor>();
		break;
	case ICollisionTag::TAG::MARIO:
		collisionTag = std::make_unique<CollisionTagMario>();
		break;
	case ICollisionTag::TAG::FIREBALL:
		collisionTag = std::make_unique<CollisionTagFireBall>();
		break;
	case ICollisionTag::TAG::ENEMY:
		collisionTag = std::make_unique<CollisionTagEnemy>();
		break;
	case ICollisionTag::TAG::SHELL:
		collisionTag = std::make_unique<CollisionTagShell>();
		break;
	case ICollisionTag::TAG::BLOCK:
		collisionTag = std::make_unique<CollisionTagBlock>();
		break;
	}
}

void ComponentCollisionShape::changeTag(int _tag)
{
	collisionTag.reset();
	switch (_tag)
	{
	case ICollisionTag::TAG::FLOOR:
		collisionTag = std::make_unique<CollisionTagFloor>();
		break;
	case ICollisionTag::TAG::MARIO:
		collisionTag = std::make_unique<CollisionTagMario>();
		break;
	case ICollisionTag::TAG::FIREBALL:
		collisionTag = std::make_unique<CollisionTagFireBall>();
		break;
	case ICollisionTag::TAG::ENEMY:
		collisionTag = std::make_unique<CollisionTagEnemy>();
		break;
	case ICollisionTag::TAG::SHELL:
		collisionTag = std::make_unique<CollisionTagShell>();
		break;
	case ICollisionTag::TAG::BLOCK:
		collisionTag = std::make_unique<CollisionTagBlock>();
		break;
	}
}

ICollisionTag* ComponentCollisionShape::getTag()
{
	return collisionTag.get();
}

void ComponentCollisionShape::setInfoId(int id)
{
	colInfoId.push_back(id);
}

void ComponentCollisionShape::removeInfoId(int id)
{
	if (colInfoId.size() <= 0) return;

	auto it = std::find(colInfoId.begin(), colInfoId.end(), id);
	if (it == colInfoId.end()) return;
	colInfoId.erase(it);
}
std::vector<int> ComponentCollisionShape::getInfoId()
{


	return colInfoId;
}

void ComponentCollisionShape::bindToTransform(std::weak_ptr<ComponentTransform> wpTransform)
{
	transformRef = wpTransform;

	if (!transformRef.expired())
	{
		syncFromTransform();
	}
}

bool ComponentCollisionShape::getEnterByTag(int collisionTag)
{
	auto infoIds = getInfoId();
	for (int i = 0; i < infoIds.size(); i++)
	{
		auto info = CollisionManager::getColInfoFromId(infoIds[i]);
		auto target = info.lock()->getTarget(getParentId());
		if (info.lock()->getEnter())
		{
			if (!target.expired())
			{
				if (target.lock()->getTag()->tag == collisionTag)
				{
					return true;
				}

			}
		}
	}
	return false;
}

bool ComponentCollisionShape::getStayByTag(int collisionTag)
{
	auto infoIds = getInfoId();
	for (int i = 0; i < infoIds.size(); i++)
	{
		auto info = CollisionManager::getColInfoFromId(infoIds[i]);
		auto target = info.lock()->getTarget(getParentId());
		if (info.lock()->getColliding())
		{
			if (!target.expired())
			{
				if (target.lock()->getTag()->tag == collisionTag)
				{
					return true;
				}

			}
		}
	}
	return false;
}

std::vector<std::weak_ptr<CollisionInfo>> ComponentCollisionShape::getInfo()
{
	std::vector<std::weak_ptr<CollisionInfo>> infoVector;
	auto infoIds = getInfoId();
	for (int i = 0; i < infoIds.size(); i++)
	{
		auto info = CollisionManager::getColInfoFromId(infoIds[i]);
		if (!info.expired())
		{
			infoVector.push_back(info);
		}
	}
	return infoVector;
}












ComponentCollisionPoint::ComponentCollisionPoint(int objectId) : ComponentCollisionShape(objectId), point()
{

}

ComponentCollisionPoint::ComponentCollisionPoint(int objectId, float _x, float _y) : ComponentCollisionShape(objectId), point(_x, _y)
{
}

ComponentCollisionPoint::ComponentCollisionPoint(int objectId, const Point& pos): ComponentCollisionShape(objectId), point(pos)
{
}

void ComponentCollisionPoint::paramUpdate(ShapeSetParam* param)
{
	if (param->paramType == ShapeSetParam::ParamType::PT_XY)
	{
		point = param->param.paramPoint.point;
	}
}

bool ComponentCollisionPoint::checkCollide(ComponentCollisionShape* shape, ContactInfo* pContact)
{
	if (shape->getShapeType() == OBJECTSHAPE::POINT)
	{
		ComponentCollisionPoint* pTarget = dynamic_cast<ComponentCollisionPoint*>(shape);
		if (pContact)return CheckPointHit(this->point, pTarget->point, pContact);
		return CheckPointHit(this->point, pTarget->point);
	}
	if (shape->getShapeType() == OBJECTSHAPE::CIRCLE)
	{
		ComponentCollisionCircle* pTarget = dynamic_cast<ComponentCollisionCircle*>(shape);
		if (pContact)return CheckPointCircleHit(this->point, pTarget->circle, pContact);
		return CheckPointCircleHit(this->point, pTarget->circle);
	}
	if (shape->getShapeType() == OBJECTSHAPE::RECT)
	{
		ComponentCollisionRect* pTarget = dynamic_cast<ComponentCollisionRect*>(shape);
		if (pContact)return CheckPointBoxHit(this->point, pTarget->rect, pContact);
		return CheckPointBoxHit(this->point, pTarget->rect);
	}
	if (shape->getShapeType() == OBJECTSHAPE::LINE)
	{
		ComponentCollisionLine* pTarget = dynamic_cast<ComponentCollisionLine*>(shape);
		if (pContact)return CheckLinePointHit(pTarget->line, this->point, pContact);
		return CheckLinePointHit(pTarget->line, this->point);
	}
	return false;
}

void ComponentCollisionPoint::syncFromTransform()
{
	if (!transformRef.expired())
	{
		point = transformRef.lock()->getPosition();
	}
}

void ComponentCollisionPoint::update()
{
	prevPos = point;
	syncFromTransform();
}

Point ComponentCollisionPoint::getTranslation()
{
	return point - prevPos;
}





ComponentCollisionLine::ComponentCollisionLine(int objectId) : ComponentCollisionShape(objectId), line()
{

}
ComponentCollisionLine::ComponentCollisionLine(int objectId,const Point& _begin, const Point& _end) : ComponentCollisionShape(objectId), line(_begin, _end)
{

}
ComponentCollisionLine::ComponentCollisionLine(int objectId,const Line& _line) : ComponentCollisionShape(objectId), line(_line)
{

}


void ComponentCollisionLine::paramUpdate(ShapeSetParam* param)
{
	if (param->paramType == ShapeSetParam::PT_LINE_BEGIN)
	{
		this->line.begin = param->param.paramPoint.point;
	}
	else if (param->paramType == ShapeSetParam::PT_LINE_END)
	{
		this->line.end = param->param.paramPoint.point;
	}
	else if (param->paramType == ShapeSetParam::PT_LINE_BOTH)
	{
		this->line.begin = param->param.paramPoint2.point1;
		this->line.end = param->param.paramPoint2.point2;
	}
	else
	{
		return;
	}
}

bool ComponentCollisionLine::checkCollide(ComponentCollisionShape* shape, ContactInfo* pContact)
{
	if (shape->getShapeType() == OBJECTSHAPE::POINT)
	{
		ComponentCollisionPoint* pTarget = dynamic_cast<ComponentCollisionPoint*>(shape);
		if (pContact)return CheckLinePointHit(this->line, pTarget->point, pContact);
		return CheckLinePointHit(this->line, pTarget->point);
	}
	if (shape->getShapeType() == OBJECTSHAPE::CIRCLE)
	{
		ComponentCollisionCircle* pTarget = dynamic_cast<ComponentCollisionCircle*>(shape);
		if (pContact)return CheckLineCircleHit(this->line, pTarget->circle, pContact);
		return CheckLineCircleHit(this->line, pTarget->circle);
	}
	if (shape->getShapeType() == OBJECTSHAPE::RECT)
	{
		ComponentCollisionRect* pTarget = dynamic_cast<ComponentCollisionRect*>(shape);
		if (pContact)return CheckLineBoxHit(this->line, pTarget->rect, pContact);
		return CheckLineBoxHit(this->line, pTarget->rect);
	}
	if (shape->getShapeType() == OBJECTSHAPE::LINE)
	{
		ComponentCollisionLine* pTarget = dynamic_cast<ComponentCollisionLine*>(shape);
		if (pContact)return CheckLineHit(this->line, pTarget->line, pContact);
		return CheckLineHit(this->line, pTarget->line);
	}
	return false;
}

void ComponentCollisionLine::syncFromTransform()
{
	if (!transformRef.expired())
	{
		Point beginPos = transformRef.lock()->getPosition();
		Point endPos = beginPos + (line.end - line.begin);

		line.begin = beginPos;
		line.end = endPos;
	}
}

void ComponentCollisionLine::update()
{
	prevPos = line.begin;
	syncFromTransform();
}

Point ComponentCollisionLine::getTranslation()
{
	return line.begin - prevPos;
}


ComponentCollisionCircle::ComponentCollisionCircle(int objectId) : ComponentCollisionShape(objectId), circle()
{

}
ComponentCollisionCircle::ComponentCollisionCircle(int objectId,const Point& _pos, float _r) : ComponentCollisionShape(objectId), circle(_pos, _r)
{

}
ComponentCollisionCircle::ComponentCollisionCircle(int objectId,const Circle& _circle) : ComponentCollisionShape(objectId), circle(_circle)
{

}



void ComponentCollisionCircle::paramUpdate(ShapeSetParam* param)
{
	if (param->paramType == ShapeSetParam::PT_XY)
	{
		this->circle.pos = param->param.paramPoint.point;
	}
	else if (param->paramType == ShapeSetParam::PT_R)
	{
		this->circle.radius = param->param.paramR.r;
	}
	else if (param->paramType == ShapeSetParam::PT_CIRCLE)
	{
		this->circle.pos = param->param.paramCircle.point;
		this->circle.radius = param->param.paramCircle.r;
	}
	else
	{
		return;
	}
}

bool ComponentCollisionCircle::checkCollide(ComponentCollisionShape* shape, ContactInfo* pContact)
{
	if (shape->getShapeType() == OBJECTSHAPE::POINT)
	{
		ComponentCollisionPoint* pTarget = dynamic_cast<ComponentCollisionPoint*>(shape);
		if (pContact) return CheckPointCircleHit(pTarget->point, this->circle, pContact);
		return CheckPointCircleHit(pTarget->point, this->circle);
	}
	if (shape->getShapeType() == OBJECTSHAPE::CIRCLE)
	{
		ComponentCollisionCircle* pTarget = dynamic_cast<ComponentCollisionCircle*>(shape);
		if (pContact)return CheckCircleHit(this->circle, pTarget->circle, pContact);
		return CheckCircleHit(this->circle, pTarget->circle);
	}
	if (shape->getShapeType() == OBJECTSHAPE::RECT)
	{
		ComponentCollisionRect* pTarget = dynamic_cast<ComponentCollisionRect*>(shape);
		if (pContact)return CheckCircleBoxHit(this->circle, pTarget->rect, pContact);
		return CheckCircleBoxHit(this->circle, pTarget->rect);
	}
	if (shape->getShapeType() == OBJECTSHAPE::LINE)
	{
		ComponentCollisionLine* pTarget = dynamic_cast<ComponentCollisionLine*>(shape);
		if (pContact)return CheckLineCircleHit(pTarget->line, this->circle, pContact);
		return CheckLineCircleHit(pTarget->line, this->circle);
	}
	return false;
}

void ComponentCollisionCircle::syncFromTransform()
{
	if (!transformRef.expired())
	{
		circle.pos = transformRef.lock()->getPosition();
	}
}

void ComponentCollisionCircle::update()
{
	prevPos = circle.pos;
	syncFromTransform();
}

Point ComponentCollisionCircle::getTranslation()
{
	return circle.pos - prevPos;
}




ComponentCollisionRect::ComponentCollisionRect(int objectId) : ComponentCollisionShape(objectId)
{
}
ComponentCollisionRect::ComponentCollisionRect(int objectId, const Point& _begin, const Point& _size) : ComponentCollisionShape(objectId),rect(_begin, _size)
{

}
ComponentCollisionRect::ComponentCollisionRect(int objectId,const Rect& _rect) : ComponentCollisionShape(objectId), rect(_rect)
{
}


void ComponentCollisionRect::paramUpdate(ShapeSetParam* param)
{
	if (param->paramType == ShapeSetParam::PT_XY)
	{
		this->rect.begin = param->param.paramPoint.point;
	}
	else if (param->paramType == ShapeSetParam::PT_WH)
	{
		this->rect.size = param->param.paramPoint.point;
	}
	else if (param->paramType == ShapeSetParam::PT_RECT)
	{
		this->rect.begin = param->param.paramPoint2.point1;
		this->rect.size = param->param.paramPoint2.point2;
	}
	else
	{
		return;
	}
}

void ComponentCollisionRect::syncFromTransform()
{
	if (!transformRef.expired())
	{
		rect.begin = transformRef.lock()->getPosition();
	}
}

bool ComponentCollisionRect::checkCollide(ComponentCollisionShape* shape, ContactInfo* pContact)
{
	if (shape->getShapeType() == OBJECTSHAPE::POINT)
	{
		ComponentCollisionPoint* pTarget = dynamic_cast<ComponentCollisionPoint*>(shape);
		if (pContact)return CheckPointBoxHit(pTarget->point, this->rect, pContact);
		return CheckPointBoxHit(pTarget->point, this->rect);
	}
	if (shape->getShapeType() == OBJECTSHAPE::CIRCLE)
	{
		ComponentCollisionCircle* pTarget = dynamic_cast<ComponentCollisionCircle*>(shape);
		if (pContact)return CheckCircleBoxHit(pTarget->circle, this->rect, pContact);
		return CheckCircleBoxHit(pTarget->circle, this->rect);
	}
	if (shape->getShapeType() == OBJECTSHAPE::RECT)
	{
		ComponentCollisionRect* pTarget = dynamic_cast<ComponentCollisionRect*>(shape);
		Point tThis = this->getTranslation();
		Point tTarget = pTarget->getTranslation();
		if (pContact) return CheckBoxHit(this->rect, pTarget->rect, tThis, tTarget, pContact);
		return CheckBoxHit(this->rect, pTarget->rect);
	}
	if (shape->getShapeType() == OBJECTSHAPE::LINE)
	{
		ComponentCollisionLine* pTarget = dynamic_cast<ComponentCollisionLine*>(shape);
		if (pContact)return CheckLineBoxHit(pTarget->line, this->rect, pContact);
		return CheckLineBoxHit(pTarget->line, this->rect);
	}
	return false;
}

void ComponentCollisionRect::update()
{
	prevPos = rect.begin;
	syncFromTransform();
}

Point ComponentCollisionRect::getTranslation()
{
	return rect.begin - prevPos;
}

Rect ComponentCollisionRect::get()
{
	return rect;
}


ShapeSetParam::Param::Param()
{
	this->paramR.r = 0.0;
}


ShapeSetParam::ShapeSetParam(ShapeSetParam::ParamType type)
{
	paramType = type;
}
