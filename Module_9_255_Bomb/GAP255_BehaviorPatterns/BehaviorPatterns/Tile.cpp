#include "Tile.h"

#include "TileFactories.h"

//////////////////////// Tile ////////////////////////////////
Tile::Tile(AppearanceStrategy::Appearance apearanceType, BehaviorStrategy::Behavior behaviorType)
{
	SetAppearance(apearanceType);
	SetBehavior(behaviorType);
}

Tile::Tile(const Tile& original)
{
	SetAppearance(original.m_pAppearance->GetAppearance());
	SetBehavior(original.m_pBehavior->GetBehavior());
}

Tile::~Tile()
{
	delete m_pBehavior;
}

void Tile::SetAppearance(AppearanceStrategy::Appearance appearanceType)
{						  
	m_pAppearance = FlyweightAppearanceFactory::Create(appearanceType);
}

void Tile::SetBehavior(BehaviorStrategy::Behavior behaviorType)
{
	if (m_pBehavior)
		delete m_pBehavior;
	m_pBehavior = BehaviorFactory::Create(behaviorType);
	m_pBehavior->GiveOwner(this);
}

Tile* Tile::Clone()
{
	return new Tile(*this);
}

void Tile::OnEnter(Entity* pEntity)
{
	auto newType = m_pBehavior->OnEnter(pEntity);
	if (newType != m_pBehavior->GetBehavior())
		SetBehavior(newType);
}