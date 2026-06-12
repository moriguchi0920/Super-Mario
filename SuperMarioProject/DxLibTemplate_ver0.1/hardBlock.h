#pragma once

#include "entityObject.h"
#include"blockBase.h"

class HardBlock : public BlockBase
{
private:

public:
    HardBlock(Rect rect);


    void update() override;

    void eventProc(int from, std::string name, std::vector<Event::DataMap> datas) override;
};
