#pragma once

#include "entityObject.h"
#include"blockBase.h"

class rengablock : public BlockBase
{
private:

public:
    rengablock(Rect rect);

    void update() override;

    void eventProc(int from, std::string name, std::vector<Event::DataMap> datas) override;

    void activateProc() override;

    void deactivateProc() override;

    void deathProc() override;
};