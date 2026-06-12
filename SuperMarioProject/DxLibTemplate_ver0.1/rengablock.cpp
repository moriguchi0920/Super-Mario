#include "rengablock.h"
#include "objectManager.h"
#include "componentTransform.h"
#include "componentRenderable.h"
#include"scrollManager.h"

rengablock::rengablock(Rect rect) : BlockBase(rect)
{
    auto transform = getComponent<ComponentTransform>();

    if (!transform.expired())
    {
        transform.lock()->setScroll(true);
    }

    auto colRect = getComponent<ComponentCollisionRect>();
    if (!colRect.expired())
    {
        colRect.lock()->addTag(ICollisionTag::RENGA);
        printfDx("Renga Tag = %d\n", colRect.lock()->getTag()->tag);
    }

    auto renderRect = addComponent<ComponentRenderableRect>(id, ComponentRenderable::PRIORITY_DEFAULT, rect);

    if (!renderRect.expired())
    {
        // ’ƒFÝ’è
        renderRect.lock()->setColor(139, 69, 19);
    }
}
//rengablock::rengablock(float x, float y) : Object(ObjectManager::makeId())
//{
//    addComponent<ComponentTransform>(id).lock()->setScroll(true);
//
//    auto comT = getComponent<ComponentTransform>();
//    comT.lock()->setPosition(Point(x, y));
//
//    addComponent<ComponentRenderableRect>(this->id,0.5f,Float2(x, y),Float2(SPRITE_SIZE, SPRITE_SIZE));
//
//    auto comR = getComponent<ComponentRenderableRect>();
//    comR.lock()->setColor(139, 69, 19);
//}

void rengablock::update()
{

    BlockBase::update();

    auto comR = getComponent<ComponentRenderableRect>();
    comR.lock()->syncFromTransform();

}

void rengablock::eventProc(int from, std::string name, std::vector<Event::DataMap> datas)
{
}

void rengablock::activateProc()
{
}

void rengablock::deactivateProc()
{
}

void rengablock::deathProc()
{
}
