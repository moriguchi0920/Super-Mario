#include "dokan.h"

#include "objectManager.h"
#include "componentRenderable.h"

Dokan::Dokan(float x, float y): Object(ObjectManager::makeId())
{
    addComponent<ComponentTransform>(id).lock()->setScroll(true);
    auto comT = getComponent<ComponentTransform>();
    comT.lock()->setPosition(Point(x, 160.0f));

    Rect rect(Point(x, 160.0f), Point(y, 50.0f));
    addComponent<ComponentCollisionRect>(this->id, rect).lock()->addTag(ICollisionTag::FLOOR);
    // 緑の四角（土管ハリボテ）
    addComponent<ComponentRenderableRect>(this->id, 0.5, rect);

    // 緑色に設定
    auto comR = getComponent<ComponentRenderableRect>();
    comR.lock()->setColor(0, 200, 0);
}

void Dokan::update()
{
    auto comR = getComponent<ComponentRenderableRect>();
    auto comC = getComponent<ComponentCollisionRect>();
    comR.lock()->syncFromTransform();
    comC.lock()->update();
}