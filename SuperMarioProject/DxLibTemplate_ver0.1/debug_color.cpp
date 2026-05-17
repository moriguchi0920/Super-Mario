#include"debug_color.h"


DebugColor::DebugColor()
{
	r = 255;
	g = 255;
	b = 255;
	a = 255;
}
DebugColor::DebugColor(int _r, int _g, int _b)
{
	r = _r;
	g = _g;
	b = _b;
	a = 255;
}
DebugColor::DebugColor(int _r, int _g, int _b, int _a)
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

void DebugColor::set(int _r, int _g, int _b)
{
	r = _r;
	g = _g;
	b = _b;
}


void DebugColor::set(int _r, int _g, int _b, int _a)
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

DebugColor& DebugColor::operator + (const DebugColor& otherColor)
{
	int tmpR = fix(this->r + otherColor.r, 0, 255);
	int tmpG = fix(this->g + otherColor.g, 0, 255);
	int tmpB = fix(this->b + otherColor.b, 0, 255);
	int tmpA = fix(this->a + otherColor.a, 0, 255);
	DebugColor ret(tmpR, tmpG, tmpB, tmpA);
	return ret;
}
DebugColor& DebugColor::operator - (const DebugColor& otherColor)
{
	int tmpR = fix(this->r - otherColor.r, 0, 255);
	int tmpG = fix(this->g - otherColor.g, 0, 255);
	int tmpB = fix(this->b - otherColor.b, 0, 255);
	int tmpA = fix(this->a - otherColor.a, 0, 255);
	DebugColor ret(tmpR, tmpG, tmpB, tmpA);
	return ret;

}

DebugColor& DebugColor::operator * (const double rate)
{
	int tmpR = fix((int)((double)this->r * rate), 0, 255);
	int tmpG = fix((int)((double)this->g * rate), 0, 255);
	int tmpB = fix((int)((double)this->b * rate), 0, 255);
	int tmpA = fix((int)((double)this->a * rate), 0, 255);
	DebugColor ret(tmpR, tmpG, tmpB, tmpA);
	return ret;
}

bool DebugColor::operator==(const DebugColor& otherColor)
{
	if (r == otherColor.r && g == otherColor.g && b == otherColor.b)
	{
		return true;
	}
	return false;
}
