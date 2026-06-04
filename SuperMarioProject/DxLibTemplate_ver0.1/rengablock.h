#pragma once

#include "entityObject.h"

class rengablock : public Object
{
private:
    float x;
    float y;

public:
    rengablock(float x, float y);

    void update() override;

    void render();
};