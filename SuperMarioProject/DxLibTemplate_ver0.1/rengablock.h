#pragma once

#include "entityObject.h"
#include"blockBase.h"

class rengablock : public BlockBase
{
private:

public:
    rengablock(Rect rect);

    void update() override;

    void render();
};