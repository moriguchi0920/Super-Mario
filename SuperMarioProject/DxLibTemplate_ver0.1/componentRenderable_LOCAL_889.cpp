#include"componentRenderable.h"
#include"DxLib.h"
#include"componentTransform.h"



ComponentRenderable::ComponentRenderable(int objectId, float _priority) : Component(objectId)
{
	setPriority(_priority);
	position.center = { 0.0f, 0.0f };
	transformRef = std::weak_ptr<ComponentTransform>();
}

ComponentRenderable::~ComponentRenderable()
{
}


void ComponentRenderable::setPriority(float newPriority)
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

float ComponentRenderable::getPriority()
{
	return priority;
}

void ComponentRenderable::bindToTransform(std::weak_ptr<ComponentTransform> wpTransform)
{
	transformRef = wpTransform;
	if (!transformRef.expired())
	{
		syncFromTransform();
	}
}

void ComponentRenderable::syncFromTransform()
{
}


ComponentRenderableImage::ComponentRenderableImage(int objectId, float _priority, int _imageHandle) : ComponentRenderable(objectId, _priority)
{
	imageHandle = _imageHandle;
	rotation = 0.0f;
}

void ComponentRenderableImage::setPos(Float2 _pos)
{
	pos = _pos;
}

void ComponentRenderableImage::setRot(float _rot)
{
	rotation = _rot;
}

void ComponentRenderableImage::render()
{
	DrawGraph(pos.x, pos.y, imageHandle, true);
}

void ComponentRenderableImage::syncFromTransform()
{
	if (!transformRef.expired())
	{
		pos = transformRef.lock()->getPosition();
	}
}


ComponentRenderableAnimation::ComponentRenderableAnimation(int objectId, float _priority, AnimationDataSet* pAdc) : ComponentRenderable(objectId, _priority), AP(pAdc)
{

}

void ComponentRenderableAnimation::setBase(Float2 _base)
{
	base = _base;
}

void ComponentRenderableAnimation::setPos(Float2 _pos)
{
	pos = _pos;
	AP.x = (int)pos.x;	
	AP.y = (int)pos.y;
}

AnimationPlayer& ComponentRenderableAnimation::getAP()
{
	return AP;
}


void ComponentRenderableAnimation::render()
{
	AP.render(base.x, base.y);
}

void ComponentRenderableAnimation::syncFromTransform()
{
	if (!transformRef.expired())
	{
		pos = transformRef.lock()->getPosition();
	}

}

ComponentRenderableRect::ComponentRenderableRect(int objectId) : ComponentRenderable(objectId)
{
	priority = PRIORITY_DEFAULT;
}

ComponentRenderableRect::ComponentRenderableRect(int objectId, float _priority, Float2 _leftTop, Float2 _size) : ComponentRenderable(objectId, _priority), rect(_leftTop, _size)
{
}

ComponentRenderableRect::ComponentRenderableRect(int objectId, float _priority, Rect _rect) : ComponentRenderable(objectId, _priority), rect(_rect)
{
}

void ComponentRenderableRect::set(Float2 _leftTop, Float2 _size)
{
	rect.begin = _leftTop;
	rect.size = _size;
}

void ComponentRenderableRect::setColor(int r, int g, int b, int a)
{
	color.set(r, g, b, a);
}

DebugColor& ComponentRenderableRect::getColor()
{
	return color;
}

void ComponentRenderableRect::render()
{
	DrawBox(rect.begin.x, rect.begin.y, rect.begin.x + rect.size.x, rect.begin.y + rect.size.y, GetColor(color.r, color.g, color.b), true);
}

void ComponentRenderableRect::syncFromTransform()
{
	if (!transformRef.expired())
	{
		rect.begin = transformRef.lock()->getPosition();
	}
}

ComponentRenderableCircle::ComponentRenderableCircle(int objectId) : ComponentRenderable(objectId)
{
	priority = PRIORITY_DEFAULT;
}

ComponentRenderableCircle::ComponentRenderableCircle(int objectId, float _priority, Float2 _pos, float _radius) : ComponentRenderable(objectId, _priority), circle(_pos, _radius)
{
}

ComponentRenderableCircle::ComponentRenderableCircle(int objectId, float _priority, Circle _cir) : ComponentRenderable(objectId, _priority), circle(_cir)
{
}

void ComponentRenderableCircle::set(Float2 _pos, float _radius)
{
	circle.pos = _pos;
	circle.radius = _radius;

}

void ComponentRenderableCircle::setColor(int r, int g, int b, int a)
{
	color.set(r, g, b, a);
}


DebugColor& ComponentRenderableCircle::getColor()
{
	return color;
}

void ComponentRenderableCircle::render()
{
	DrawCircle(circle.pos.x, circle.pos.y, circle.radius, GetColor(color.r, color.g, color.b), true);

}

void ComponentRenderableCircle::syncFromTransform()
{
	if (!transformRef.expired())
	{
		circle.pos = transformRef.lock()->getPosition();
	}

}

ComponentRenderableLine::ComponentRenderableLine(int objectId) : ComponentRenderable(objectId)
{
	priority = PRIORITY_DEFAULT;
}

ComponentRenderableLine::ComponentRenderableLine(int objectId, float _priority, Float2 _begin, Float2 _end): ComponentRenderable(objectId, _priority), line(_begin, _end)
{
}




void ComponentRenderableLine::set(Float2 _begin, Float2 _end)
{
	line.begin = _begin;
	line.end = _end;
}

void ComponentRenderableLine::setColor(int r, int g, int b, int a)
{
	color.set(r, g, b, a);
}


DebugColor& ComponentRenderableLine::getColor()
{
	return color;
}

void ComponentRenderableLine::render()
{
	DrawLine(line.begin.x, line.begin.y, line.end.x, line.end.y, GetColor(color.r, color.g, color.b), 1);
}

void ComponentRenderableImage::setImage(int handle)
{
	imageHandle = handle;
}

void ComponentRenderableLine::syncFromTransform()
{
	if (!transformRef.expired())
	{
		Point beginPos = transformRef.lock()->getPosition();
		Point endPos = beginPos + (line.end - line.begin);

		line.begin = beginPos;
		line.end = endPos;
	}





}
