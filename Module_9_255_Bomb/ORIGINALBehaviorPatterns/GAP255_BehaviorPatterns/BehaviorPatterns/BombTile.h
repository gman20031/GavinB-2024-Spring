// BombTile.h
#ifndef __BOMBTILE_H__
#define __BOMBTILE_H__

#include "Tile.h"
#include <utility>

class BombTile : public Tile
{
    typedef std::pair<int, int> DamageRange;

    enum class State
    {
        k_active,
        k_dead,
    };

    static const DamageRange s_damageRange;

    State m_state;

public:
    BombTile();
    virtual void Draw() override;
    virtual void OnEnter(Player* pPlayer) override;
};

#endif

