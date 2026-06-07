#pragma once
#include"entityObject.h"
#include"blockBase.h"

class Floor : public BlockBase
{
public:
    Floor(float x, float width);
    virtual ~Floor();

    void update() override;
};
