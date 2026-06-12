#include"hardBlock.h"


HardBlock::HardBlock(Rect rect) : BlockBase(rect)
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

    auto renderRect = addComponent<ComponentRenderableRect>(id, ComponentRenderable::PRIORITY_DEFAULT, rect);

    if (!renderRect.expired())
    {
        // ’ƒFÝ’è
        renderRect.lock()->setColor(128, 54, 16);
    }
}

void HardBlock::update()
{
    BlockBase::update();

    auto comR = getComponent<ComponentRenderableRect>();
    comR.lock()->syncFromTransform();
}

void HardBlock::eventProc(int from, std::string name, std::vector<Event::DataMap> datas)
{
}
