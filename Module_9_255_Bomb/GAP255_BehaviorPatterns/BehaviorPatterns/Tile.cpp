#include "Tile.h"

#include "TileFactories.h"

Tile::Tile(AppearanceStrategy::Appearance apearanceType, BehaviorStrategy::Behavior behaviorType)
	: m_pAppearance(FlyweightAppearanceFactory::Create(apearanceType))
	, m_pBehavior(BehaviorFactory::Create(behaviorType))
{

}

void Tile::SetAppearance(AppearanceStrategy::Appearance apearanceType)
{
	delete m_pAppearance;
	m_pAppearance = FlyweightAppearanceFactory::Create(apearanceType);
}

void Tile::SetBehavior(BehaviorStrategy::Behavior behaviorType)
{
	delete m_pBehavior;
	m_pBehavior = BehaviorFactory::Create(behaviorType);
}

Tile* Tile::Clone()
{
	return new Tile(*this);
}
