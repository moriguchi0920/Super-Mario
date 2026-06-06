#include "rengablock.h"
#include "objectManager.h"
#include"componentTransform.h"
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

void rengablock::update()
{
    BlockBase::update();
}