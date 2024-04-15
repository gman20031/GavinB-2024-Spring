#include "Tile.h"

#include "TileFactories.h"

//////////////////////// Tile ////////////////////////////////
Tile::~Tile()
{
	delete m_pBehavior;
}

Tile::Tile(AppearanceStrategy::Appearance appearanceType, BehaviorStrategy::Behavior behaviorType
	, const std::initializer_list<int>& behaviorInputs)
{
	SetAppearance(appearanceType);
	SetBehavior(behaviorType, behaviorInputs);
}

Tile::Tile(const Tile& original, const std::initializer_list<int>& behaviorInputs)
{
	SetAppearance(original.m_pAppearance->GetAppearance());
	SetBehavior(original.m_pBehavior->GetBehavior() , behaviorInputs);
}

void Tile::SetBehavior(BehaviorStrategy::Behavior behaviorType,
	const std::initializer_list<int>& behaviorInputs)
{
	if (m_pBehavior)
		delete m_pBehavior;
	m_pBehavior = BehaviorFactory::Create(behaviorType, behaviorInputs);
	m_pBehavior->GiveOwner(this);
}

void Tile::SetAppearance(AppearanceStrategy::Appearance appearanceType)
{						  
	m_pAppearance = FlyweightAppearanceFactory::Create(appearanceType);
}

Tile* Tile::Clone(const std::initializer_list<int>& behaviorInputs)
{
	return new Tile(*this, behaviorInputs);
}

void Tile::OnEnter(Entity* pEntity)
{
	auto newType = m_pBehavior->OnEnter(pEntity);
	if (newType != m_pBehavior->GetBehavior())
		SetBehavior(newType);
}