#include "hatenablock.h"
#include "objectManager.h"
#include"componentTransform.h"
#include "componentRenderable.h"

hatenablock::hatenablock(float x, float y) : Object(ObjectManager::makeId())
{

    addComponent<ComponentTransform>(id).lock()->setScroll(true);

    auto comT = getComponent<ComponentTransform>();
    comT.lock()->setPosition(Point(x, y));

    // 四角描画コンポーネント追加
    auto rect = addComponent<ComponentRenderableRect>(getId(), 0.5f, Float2(x, y), Float2(SPRITE_SIZE, SPRITE_SIZE));

    auto comR = getComponent<ComponentRenderableRect>();
    comR.lock()->setColor(250, 220, 0);
}

void hatenablock::update()
{
    auto comR = getComponent<ComponentRenderableRect>();
    comR.lock()->syncFromTransform();
}