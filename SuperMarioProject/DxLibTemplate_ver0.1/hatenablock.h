#pragma once

#include "entityObject.h"
#include"blockBase.h"

class hatenablock : public BlockBase
{
private:

public:
    hatenablock(Rect rect);

    void update() override;

    void activateProc() override;

    void deactivateProc() override;

    void deathProc() override;

};
