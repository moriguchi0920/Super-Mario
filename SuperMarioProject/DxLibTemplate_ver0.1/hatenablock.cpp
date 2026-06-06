#include "hatenablock.h"
#include "objectManager.h"
#include"componentTransform.h"
#include "componentRenderable.h"

hatenablock::hatenablock(float x, float y) : Object(ObjectManager::makeId())
{
    // 四角描画コンポーネント追加
    auto rect = addComponent<ComponentRenderableRect>(getId(), 0.5f, Float2(x, y), Float2(SPRITE_SIZE, SPRITE_SIZE));

    // 黄色設定
    rect.lock()->setColor(250, 220, 0);
}

void hatenablock::update()
{
}