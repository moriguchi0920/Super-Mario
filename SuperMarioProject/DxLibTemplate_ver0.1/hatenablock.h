#pragma once

#include "entityObject.h"
#include "blockBase.h"


enum class BLOCK_ITEM_TYPE {
    COIN,      // コイン
    MUSHROOM,  // キノコ
    FLOWER     // フラワー
};


class hatenablock : public BlockBase
{
public:
   
    hatenablock(Rect rect, BLOCK_ITEM_TYPE type = BLOCK_ITEM_TYPE::COIN);

    void update() override;
    void activateProc() override;
    void deactivateProc() override;
    void deathProc() override;

    void hitFromBottom();

private:
    bool m_used = false; // 叩かれているかどうか

   
    BLOCK_ITEM_TYPE myItemType;
};