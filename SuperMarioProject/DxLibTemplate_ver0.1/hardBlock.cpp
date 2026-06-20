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

    }
}

void HardBlock::update()
{
    BlockBase::update();

    auto comR = getComponent<ComponentRenderableImage>();
    comR.lock()->syncFromTransform();
}

void HardBlock::eventProc(int from, std::string name, std::vector<Event::DataMap> datas)
{
}
