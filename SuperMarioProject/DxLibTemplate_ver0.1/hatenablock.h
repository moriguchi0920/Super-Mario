#pragma once

#include "entityObject.h"
#include"blockBase.h"

class hatenablock : public BlockBase
{
public:
    hatenablock(Rect rect);

    void update() override;

    void activateProc() override;

    void deactivateProc() override;

    void deathProc() override;

    void hitFromBottom();

private:
    bool m_used = false;

};
