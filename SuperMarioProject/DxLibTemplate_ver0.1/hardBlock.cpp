#include"hardBlock.h"
#include"imageManager.h"

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

    auto renderRect = addComponent<ComponentRenderableImage>(id, ComponentRenderable::PRIORITY_DEFAULT, ImageManager::getInstance()->getImageHandle(ImageManager::IMAGENAME::IMAGE_BLOCK_HARD));

    if (!renderRect.expired())
    {
        renderRect.lock()->setPos(rect.begin + rect.size * 0.5f);
    }
}

void HardBlock::update()
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

void HardBlock::eventProc(int from, std::string name, std::vector<Event::DataMap> datas)
{
}
