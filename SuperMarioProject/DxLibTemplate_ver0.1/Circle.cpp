#include "Circle.h"

Circle::Circle()
{
	pos.Clear();
	radius = 0.0f;
}

Circle::Circle(Float2 _pos, float _radius)
{
	pos = _pos;
	radius = _radius;

}
