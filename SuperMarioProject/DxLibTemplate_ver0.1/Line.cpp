#include<math.h>
#include"Line.h"



Line::Line()
{
	begin.Clear();
	end.Clear();
}

Line::Line(Float2 _begin, Float2 _end)
{
	begin = _begin;
	end = _end;
}

float Line::GetLength()
{
	float x = end.x - begin.x;
	float y = end.y - begin.y;

	return sqrtf(x * x + y * y);
}
