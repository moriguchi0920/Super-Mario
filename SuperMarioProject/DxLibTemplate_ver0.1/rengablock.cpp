#include "rengablock.h"
#include "objectManager.h"
#include "componentTransform.h"
#include "componentRenderable.h"

rengablock::rengablock(float x, float y) : Object(ObjectManager::makeId())
{
    addComponent<ComponentTransform>(id).lock()->setScroll(true);

    auto comT = getComponent<ComponentTransform>();
    comT.lock()->setPosition(Point(x, y));

    addComponent<ComponentRenderableRect>(this->id,0.5f,Float2(x, y),Float2(SPRITE_SIZE, SPRITE_SIZE));

    auto comR = getComponent<ComponentRenderableRect>();
    comR.lock()->setColor(139, 69, 19);
}

void rengablock::update()
{
    auto comR = getComponent<ComponentRenderableRect>();
    comR.lock()->syncFromTransform();
}