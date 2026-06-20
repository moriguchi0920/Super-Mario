#include "hatenablock.h"
#include "objectManager.h"
#include "componentTransform.h"
#include "imageManager.h"
#include "componentRenderable.h"
#include "superMushroom.h" 
#include "const.h"
#include "scrollManager.h"


hatenablock::hatenablock(Rect rect, BLOCK_ITEM_TYPE type) : BlockBase(rect)
{
    myItemType = type;

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
            renderImage.lock()->setPos(rect.begin + rect.size * 0.5f);
        }

}

void hatenablock::update()
{
    BlockBase::update();


    auto comR = getComponent<ComponentRenderableImage>();

    if (!comR.expired())
    {
        comR.lock()->syncFromTransform();

        float offset = SPRITE_SIZE / 2.0f;

        auto transform = getComponent<ComponentTransform>();
        if (!transform.expired())
        {

            Float2 basePos = transform.lock()->getPosition();
            comR.lock()->setPos(basePos + Float2(offset, offset));
        }
    }

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

  
    auto comR = getComponent<ComponentRenderableRect>();
    if (!comR.expired())
    {
        comR.lock()->setColor(150, 100, 50); 
    }

    auto transform = getComponent<ComponentTransform>();
    if (transform.expired())
    {
        return;
    }

    Float2 pos = transform.lock()->getPosition();

    
    switch (myItemType)
    {
    case BLOCK_ITEM_TYPE::MUSHROOM:
        // ÉLÉmÉRÇê∂ê¨Ç∑ÇÈ
        ObjectManager::createObject<SuperMushroom>(
            Rect(
                Float2(pos.x, pos.y - SPRITE_SIZE),
                Float2(SPRITE_SIZE, SPRITE_SIZE)
            )
        );
        break;

    case BLOCK_ITEM_TYPE::COIN:
       
        break;

    case BLOCK_ITEM_TYPE::FLOWER:
       
        break;
    }
}