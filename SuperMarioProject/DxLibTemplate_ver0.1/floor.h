#pragma once
#include"entityObject.h"


class Floor : public Object
{
public:
    Floor(float x, float width);
    virtual ~Floor();

    void update() override;
};
