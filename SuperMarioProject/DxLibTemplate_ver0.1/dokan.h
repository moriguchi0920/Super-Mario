#pragma once

#include "objectManager.h"

class Dokan : public Object
{
public:
    Dokan(float x, float y);

    void update() override;
};