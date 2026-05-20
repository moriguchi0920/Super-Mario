#include"ComponentCollision.h"



// コンストラクタ
ComponentCollisionShape::ComponentCollisionShape(int objectId) : Component(objectId)
{

	isCollide = true;
}
// デストラクタ
ComponentCollisionShape::~ComponentCollisionShape()
{


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




void ComponentCollisionShape::setIsCollide(bool _isCollide)
{
	isCollide = _isCollide;
}

bool ComponentCollisionShape::getIsCollide()
{
	return isCollide;
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
		if (pContact)return CheckBoxHit(pTarget->rect, this->rect, pContact);
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


ShapeSetParam::Param::Param()
{
	this->paramR.r = 0.0;
}


ShapeSetParam::ShapeSetParam(ShapeSetParam::ParamType type)
{
	paramType = type;
}
