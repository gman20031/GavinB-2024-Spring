// TreasureTile.cpp
#include "TreasureTile.h"
#include "Player.h"
#include <iostream>

const TreasureTile::TreasureRange TreasureTile::s_treasureRange(50, 150);

TreasureTile::TreasureTile()
    : m_collected(false)
{
    m_amount = (rand() % (s_treasureRange.second - s_treasureRange.first)) + s_treasureRange.first;
}

void TreasureTile::Draw()
{
    if (!m_collected)
        std::cout << "$";
    else
        std::cout << ".";  // floor
}

void TreasureTile::OnEnter(Player* pPlayer)
{
    if (!m_collected)
    {
        pPlayer->AddGold(m_amount);
        m_collected = true;
    }
}

