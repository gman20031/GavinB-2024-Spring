#include "Tile.h"

#include "TileFactories.h"

//////////////////////// Tile ////////////////////////////////
Tile::~Tile()
{
	delete m_pBehavior;
}

Tile::Tile(AppearanceType appearanceType, BehaviorType behaviorType
	, const std::initializer_list<int>& behaviorInputs )
{
	SetAppearance(appearanceType);
	SetBehavior(behaviorType, behaviorInputs);
}

Tile::Tile(const Tile& original, const std::initializer_list<int>& behaviorInputs)
{
	SetAppearance( (AppearanceType)original.m_pAppearance->GetAppearanceType());
	SetBehavior( (BehaviorType)original.m_pBehavior->GetBehaviorType() , behaviorInputs);
}

void Tile::SetBehavior(BehaviorType behaviorType,
	const std::initializer_list<int>& behaviorInputs)
{
	if (m_pBehavior)
		delete m_pBehavior;
	m_pBehavior = BehaviorFactory::Create(behaviorType, behaviorInputs);
	m_pBehavior->GiveOwner(this);
}

void Tile::SetAppearance(AppearanceType appearanceType)
{						  
	m_pAppearance = FlyweightAppearanceFactory::Create(appearanceType);
}

Tile* Tile::Clone(const std::initializer_list<int>& behaviorInputs)
{
	return new Tile(*this, behaviorInputs);
}

void Tile::OnEnter(Entity* pEntity)
{
	BehaviorType newType = (BehaviorType)m_pBehavior->OnEnter(pEntity);
	if (newType != (BehaviorType)m_pBehavior->GetBehaviorType())
		SetBehavior(newType);
}