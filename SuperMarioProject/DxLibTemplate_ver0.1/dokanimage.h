#pragma once

#include "objectManager.h"

class Dokanimage : public Object
{
public:
    Dokanimage(float x, float y);

    void update() override;
};