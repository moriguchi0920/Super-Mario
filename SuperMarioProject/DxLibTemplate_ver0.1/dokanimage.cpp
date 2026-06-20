#include "dokanimage.h"

#include "objectManager.h"
#include "componentRenderable.h"

Dokanimage::Dokanimage(float x, float y) : Object(ObjectManager::makeId())
{
    int dokanImage = LoadGraph("Stage/Dokan.png");
    addComponent<ComponentTransform>(id).lock()->setScroll(true);
    auto comT = getComponent<ComponentTransform>();
    comT.lock()->setPosition(Point(x, 190.0f));

    Rect rect(Point(x, 160.0f), Point(y, 40.0f));
    //addComponent<ComponentCollisionRect>(this->id, rect).lock()->addTag(ICollisionTag::BLOCK);
    // “yŠÇ‚Ì‰æ‘œ
    auto comR = addComponent<ComponentRenderableImage>(id, ComponentRenderable::PRIORITY_DEFAULT, dokanImage);

    // —ÎF‚Éİ’è
    //auto comR = getComponent<ComponentRenderableRect>();
    //comR.lock()->setColor(0, 200, 0);
}

void Dokanimage::update()
{
    auto comR = getComponent<ComponentRenderableImage>();
    comR.lock()->syncFromTransform();
}