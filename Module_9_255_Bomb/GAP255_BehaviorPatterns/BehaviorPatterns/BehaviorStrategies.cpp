#include "BehaviorStrategies.h"

#include "Entity.h"
#include "Player.h"
#include "World.h"
#include "Tile.h"

void BehaviorStrategy::GiveOwner(Tile* pOwner)
{
	m_pOwner = pOwner;
}

BehaviorStrategy::Behavior EndGame::OnEnter(Entity* pEntity)
{
	if(pEntity->IsPlayer())
		pEntity->GetWorld()->GetPlayerPointer()->EndGame();
	return Behavior::kEndGame;
}

BehaviorStrategy::Behavior Explosion::OnEnter(Entity* pEntity)
{
	int damage = (rand() % (s_damageRange.second - s_damageRange.first)) + s_damageRange.first;
	pEntity->Damage(damage);
	m_pOwner->SetAppearance(AppearanceStrategy::Appearance::kUsedBomb);
	return Behavior::kNothing;
}

BehaviorStrategy::Behavior GiveTreasure::OnEnter(Entity* pEntity)
{
	int amount = (rand() % (s_treasureRange.second - s_treasureRange.first)) + s_treasureRange.first;
	if (pEntity->IsPlayer())
		pEntity->GetWorld()->GetPlayerPointer()->AddGold(amount);
	m_pOwner->SetAppearance(AppearanceStrategy::Appearance::kEmpty);
	return Behavior::kNothing;
}

BehaviorStrategy::Behavior  Teleport::OnEnter(Entity* pEntity)
{
	pEntity->SetPosition(m_linkedTileX, m_linkedTileY);
	return m_behaviorType;
}
