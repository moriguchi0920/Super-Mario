#include"common_func.h"
#include"collisionType.h"


CPoint::CPoint() : point()
{
	
}
CPoint::CPoint(float _x, float _y) : point(_x, _y)
{

}
CPoint::CPoint(const Point& pos) : point(pos)
{

}



void CPoint::paramUpdate(ShapeSetParam* param)
{
	if (param->paramType == ShapeSetParam::PT_XY)
	{
		this->point.x = param->param.paramPoint.point.x;
		this->point.y = param->param.paramPoint.point.y;
	}
	else
	{
		return;
	}
}





ShapeSetParam::Param::Param()
{
	this->paramR.r = 0.0;
}


ShapeSetParam::ShapeSetParam(ShapeSetParam::ParamType type)
{
	paramType = type;
}


