#include "dokan.h"

#include "objectManager.h"
#include "componentRenderable.h"

Dokan::Dokan(float x, float y): Object(ObjectManager::makeId())
{
    // 緑の四角（土管ハリボテ）
    auto rect = addComponent<ComponentRenderableRect>(
        getId(),
        0.5f,
        Float2(x,y),
        Float2(30.0f, 50.0f)   // 土管サイズ
    );

    // 緑色に設定
    rect.lock()->setColor(0, 200, 0);
}

void Dokan::update()
{
    // 今は何もしない（ハリボテ）
}