#include "rengablock.h"
#include "objectManager.h"
#include "componentTransform.h"
#include "componentRenderable.h"
#include"scrollManager.h"
#include"imageManager.h"

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
        //printfDx("Renga Tag = %d\n", colRect.lock()->getTag()->tag);
    }

    auto renderImage = addComponent<ComponentRenderableImage>(id,ComponentRenderable::PRIORITY_DEFAULT,ImageManager::getInstance()->getImageHandle(ImageManager::IMAGENAME::IMAGE_BLOCK_BRICK)
    );


    if (!transform.expired() && !renderImage.expired())
    {
        renderImage.lock()->bindToTransform(transform);
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

    auto comR = getComponent<ComponentRenderableImage>();

    if (!comR.expired())
    {
        comR.lock()->syncFromTransform();

        float offset = SPRITE_SIZE / 2.0f; 

        auto transform = getComponent<ComponentTransform>();
        if (!transform.expired())
        {
         
            Float2 basePos = transform.lock()->getPosition(); 
            comR.lock()->setPos(basePos);
        }
    }
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

void rengablock::hitFromBottom()
{
    die();
}
