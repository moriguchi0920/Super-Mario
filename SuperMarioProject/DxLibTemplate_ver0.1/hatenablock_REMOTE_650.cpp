#include "hatenablock.h"
#include "objectManager.h"
#include "componentTransform.h"
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

    auto renderRect = addComponent<ComponentRenderableRect>(id, 0.5, rect);

    if (!renderRect.expired())
    {
        
        renderRect.lock()->setColor(250, 220, 0);
    }
}

void hatenablock::update()
{
    BlockBase::update();

    auto comR = getComponent<ComponentRenderableRect>();
    if (!comR.expired()) 
    {
        comR.lock()->syncFromTransform();
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