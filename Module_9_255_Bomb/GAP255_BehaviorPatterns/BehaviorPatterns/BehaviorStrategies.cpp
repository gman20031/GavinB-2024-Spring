#include "BehaviorStrategies.h"

#include "Player.h"
#include "World.h"

void EndGame::OnEnter(Player* pPlayer)
{
	pPlayer->EndGame();
}

void Explosion::OnEnter(Player* pPlayer)
{
	int damage = (rand() % (s_damageRange.second - s_damageRange.first)) + s_damageRange.first;
	pPlayer->Damage(damage);
}

void GiveTreasure::OnEnter(Player* pPlayer)
{
	int amount = (rand() % (s_treasureRange.second - s_treasureRange.first)) + s_treasureRange.first;
	pPlayer->AddGold(amount);
}
