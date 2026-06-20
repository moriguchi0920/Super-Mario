#pragma once

#include "entityObject.h"
#include"blockBase.h"
#include "hatenablock.h"

class rengablock : public BlockBase
{
private:

public:
    rengablock(Rect rect, BLOCK_ITEM_TYPE type = BLOCK_ITEM_TYPE::COIN);

    void update() override;

    void eventProc(int from, std::string name, std::vector<Event::DataMap> datas) override;

    void activateProc() override;

    void deactivateProc() override;

    void deathProc() override;

    void hitFromBottom();
};