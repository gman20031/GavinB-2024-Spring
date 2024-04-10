// EndTile.h
#ifndef __ENDTILE_H__
#define __ENDTILE_H__

#include "Tile.h"

class EndTile : public Tile
{
public:
    virtual void Draw() override;
    virtual void OnEnter(Player* pPlayer) override;
};

#endif

