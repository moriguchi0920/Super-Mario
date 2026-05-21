#include "blockBase.h"
#include"componentCollision.h"
#include"componentRenderable.h"
#include"componentTransform.h"

BlockBase::BlockBase(int id, const Rect& rect) : Object(id)
{
	this->addComponent<ComponentTransform>(this->id);
	this->addComponent<ComponentCollisionRect>(this->id, rect);
	Point lineBegin = rect.begin;
	Point lineEnd(rect.begin.x + rect.size.x, rect.begin.y);
	Line line(lineBegin, lineEnd);
	this->addComponent<ComponentCollisionLine>(this->id, line);
	this->addComponent<ComponentRenderableRect>(this->id, rect);

}

BlockBase::~BlockBase()
{
}

void BlockBase::update()
{
}
