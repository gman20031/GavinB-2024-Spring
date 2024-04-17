// MimicTile.h
#ifndef __MIMICTILE_H__
#define __MIMICTILE_H__

#include "Tile.h"
#include <utility>

class MimicTile : public Tile
{
    typedef std::pair<int, int> DamageRange;

    enum State
    {
        k_hidden,
        k_revealed,
        k_exploded,
    };

    static const DamageRange s_damageRange;

    State m_state;

public:
    MimicTile();
    virtual void Draw() override;
    virtual void OnEnter(Player* pPlayer) override;
};

#endif

