// BombTile.cpp
#include "BombTile.h"
#include "Player.h"
#include <iostream>

const BombTile::DamageRange BombTile::s_damageRange(3, 6);

BombTile::BombTile()
    : m_state(State::k_active)
{
    //
}

void BombTile::Draw()
{
    if (m_state == State::k_active)
        std::cout << "*";
    else
        std::cout << "#";
}

void BombTile::OnEnter(Player* pPlayer)
{
    if (m_state == State::k_active)
    {
        int damage = (rand() % (s_damageRange.second - s_damageRange.first)) + s_damageRange.first;
        pPlayer->Damage(damage);
        m_state = State::k_dead;
    }
}

