#include "rengablock.h"
#include "objectManager.h"
#include "componentTransform.h"
#include "componentRenderable.h"


rengablock::rengablock(Rect rect) : BlockBase(rect)
{
    auto colRect = getComponent<ComponentCollisionRect>();
    if (!colRect.expired())
    {
        colRect.lock()->addTag(ICollisionTag::BLOCK);
    }

    auto renderRect = addComponent<ComponentRenderableRect>(id, 0.5, rect);

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