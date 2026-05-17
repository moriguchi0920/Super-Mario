#include"renderable.h"
#include"DxLib.h"

const float Renderable::PRIORITY_DEFAULT = 0.5f;
const float Renderable::PRIORITY_MIN = 0.0f;
const float Renderable::PRIORITY_MAX = 1.0f;


Renderable::Renderable(float _priority)
{
	setPriority(_priority);
	position.center = { 0.0f, 0.0f };
}


void Renderable::setPriority(float newPriority)
{
	if (newPriority < PRIORITY_MIN)
	{
		newPriority = PRIORITY_MIN;
	}
	if (PRIORITY_MAX < newPriority)
	{
		newPriority = PRIORITY_MAX;
	}
	priority = newPriority;
}

float Renderable::getPriority()
{
	return priority;
}


RenderableImage::RenderableImage(float _priority, int _imageHandle) : Renderable(_priority)
{
	imageHandle = _imageHandle;
	rotation = 0.0f;
}

void RenderableImage::setPos(Float2 _pos)
{
	pos = _pos;
}

void RenderableImage::setRot(float _rot)
{
	rotation = _rot;
}

void RenderableImage::render()
{
	DrawRotaGraph(pos.x, pos.y, RATE, rotation , imageHandle, true);
}


RenderableAnimation::RenderableAnimation(float _priority, AnimationDataSet* pAdc) : Renderable(_priority), AP(pAdc)
{

}

void RenderableAnimation::setBase(Float2 _base)
{
	base = _base;
}

void RenderableAnimation::setPos(Float2 _pos)
{
	pos = _pos;
	AP.x = (int)pos.x;	
	AP.y = (int)pos.y;
}

AnimationPlayer& RenderableAnimation::getAP()
{
	return AP;
}


void RenderableAnimation::render()
{
	AP.render(base.x, base.y);
}

RenderableRect::RenderableRect()
{
	priority = PRIORITY_DEFAULT;
}

RenderableRect::RenderableRect(float _priority, Float2 _leftTop, Float2 _size) : Renderable(_priority), rect(_leftTop, _size)
{
}

void RenderableRect::set(Float2 _leftTop, Float2 _size)
{
	rect.begin = _leftTop;
	rect.size = _size;
}

void RenderableRect::setColor(int r, int g, int b, int a)
{
	color.set(r, g, b, a);
}

DebugColor& RenderableRect::getColor()
{
	return color;
}

void RenderableRect::render()
{
	DrawBox(rect.begin.x, rect.begin.y, rect.begin.x + rect.size.x, rect.begin.y + rect.size.y, GetColor(color.r, color.g, color.b), true);
}

RenderableCircle::RenderableCircle()
{
	priority = PRIORITY_DEFAULT;
}

RenderableCircle::RenderableCircle(float _priority, Float2 _pos, float _radius) : Renderable(_priority), circle(_pos, _radius)
{
}

void RenderableCircle::set(Float2 _pos, float _radius)
{
	circle.pos = _pos;
	circle.radius = _radius;

}

void RenderableCircle::setColor(int r, int g, int b, int a)
{
	color.set(r, g, b, a);
}


DebugColor& RenderableCircle::getColor()
{
	return color;
}

void RenderableCircle::render()
{
	DrawCircle(circle.pos.x, circle.pos.y, circle.radius, GetColor(color.r, color.g, color.b), true);

}

RenderableLine::RenderableLine()
{
	priority = PRIORITY_DEFAULT;
}

RenderableLine::RenderableLine(float _priority, Float2 _begin, Float2 _end): Renderable(_priority), line(_begin, _end)
{
}




void RenderableLine::set(Float2 _begin, Float2 _end)
{
	line.begin = _begin;
	line.end = _end;
}

void RenderableLine::setColor(int r, int g, int b, int a)
{
	color.set(r, g, b, a);
}


DebugColor& RenderableLine::getColor()
{
	return color;
}

void RenderableLine::render()
{
	DrawLine(line.begin.x, line.begin.y, line.end.x, line.end.y, GetColor(color.r, color.g, color.b), 1);
}
