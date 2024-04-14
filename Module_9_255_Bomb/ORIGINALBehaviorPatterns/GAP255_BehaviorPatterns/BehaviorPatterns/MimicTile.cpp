// MimicTile.cpp
#include "MimicTile.h"
#include "Player.h"
#include <iostream>

using std::cout;

const MimicTile::DamageRange MimicTile::s_damageRange(3, 6);

MimicTile::MimicTile()
    : m_state(State::k_hidden)
{
    //
}

void MimicTile::Draw()
{
    switch (m_state)
    {
        case State::k_hidden:
            cout << "$";
            break;

        case State::k_revealed:
            cout << "*";
            break;

        case State::k_exploded:
            cout << "#";
            break;

        default:
            cout << "ERROR: Invalid state in MimiTile";
            break;
    }
}

void MimicTile::OnEnter(Player* pPlayer)
{
    if (m_state == State::k_hidden || m_state == State::k_revealed)
    {
        int damage = (rand() % (s_damageRange.second - s_damageRange.first)) + s_damageRange.first;
        pPlayer->Damage(damage);
        m_state = State::k_exploded;
    }
}
