#include "rengablock.h"
#include "objectManager.h"
#include"componentTransform.h"
#include "componentRenderable.h"

rengablock::rengablock(float x, float y): Object(ObjectManager::makeId())
{
    // 四角描画コンポーネント追加
    auto rect = addComponent<ComponentRenderableRect>(getId(),0.5f,Float2(x, y),Float2(SPRITE_SIZE, SPRITE_SIZE));

    // 茶色設定
    rect.lock()->setColor(139, 69, 19);
}

void rengablock::update()
{
}