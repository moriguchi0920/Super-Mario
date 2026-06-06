#pragma once

#include "entityObject.h"

class hatenablock : public Object
{
private:
    float x;
    float y;

public:
    hatenablock(float x, float y);

    void update() override;

    void render();
};
