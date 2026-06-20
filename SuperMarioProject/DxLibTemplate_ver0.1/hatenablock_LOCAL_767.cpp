#include "hatenablock.h"
#include "objectManager.h"
#include "componentTransform.h"
#include "imageManager.h"
#include "componentRenderable.h"
#include "superMushroom.h" 
#include "const.h"
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

        auto renderImage = addComponent<ComponentRenderableImage>(id, 0.5, ImageManager::getInstance()->getImageHandle(ImageManager::IMAGENAME::IMAGE_BLOCK_QUESTION));

        if (!renderImage.expired())
        {
            // ‰©FÝ’è
            renderImage.lock()->setPos(rect.begin);
        }
    }

void hatenablock::update()
{

    BlockBase::update();

    auto comR = getComponent<ComponentRenderableImage>();
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

void hatenablock::hitFromBottom()
{
    if (m_used)
    {
        return;
    }

    m_used = true;

    auto transform = getComponent<ComponentTransform>();

    if (transform.expired())
    {
        return;
    }

    Float2 pos = transform.lock()->getPosition();

    ObjectManager::createObject<SuperMushroom>(
        Rect(
            Float2(pos.x, pos.y - SPRITE_SIZE),
            Float2(SPRITE_SIZE, SPRITE_SIZE)
        )
    );
}

