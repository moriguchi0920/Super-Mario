#include "hatenablock.h"
#include "objectManager.h"
#include "componentTransform.h"
#include "componentRenderable.h"
#include"scrollManager.h"

hatenablock::hatenablock(Rect rect) : BlockBase(rect)
{
    auto transform = getComponent<ComponentTransform>();

        if (!transform.expired())
        {
            transform.lock()->setScroll(true);
        }

        auto colRect = getComponent<ComponentCollisionRect>();
        if (!colRect.expired())
        {
            colRect.lock()->addTag(ICollisionTag::BLOCK);
        }

        auto renderRect = addComponent<ComponentRenderableRect>(id, 0.5, rect);

        if (!renderRect.expired())
        {
            // ‰©FÝ’è
            renderRect.lock()->setColor(250, 220, 0);
        }
    }

void hatenablock::update()
{

    BlockBase::update();

    auto comR = getComponent<ComponentRenderableRect>();
    comR.lock()->syncFromTransform();

}

void hatenablock::activateProc()
{
}

void hatenablock::deactivateProc()
{
}

void hatenablock::deathProc()
{
}
