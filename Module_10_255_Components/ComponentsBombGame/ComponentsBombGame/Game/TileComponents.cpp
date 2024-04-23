#include "TileComponents.h"

#include "../Engine/Actor.h"

#include "GameTags.h"
#include "HealthTracker.h"
#include "Appearances.h"
#include "PlayerComponents.h"
#include "World.h"

// TeleportCollide on collide

void TeleportCollide::Init(Vector2d<int> linkedPosition)
{
	m_linkedPosition = linkedPosition;
}

void TeleportCollide::OnCollide()
{
	auto& collidedActors = m_pOwner->GetCollidedActors();
	for (Actor* actor : collidedActors)
	{
		actor->SetPosition(m_linkedPosition);
	}
}

// EndGameOnCollide on collide

void EndGameOnCollide::OnCollide()
{
	auto& collidedActors = m_pOwner->GetCollidedActors();
	for (Actor* actor : collidedActors)
	{
		if (actor->HasTag(GameTag::kPlayer))
			actor->GetWorldPtr()->EndGame();
	}
}

// explode on collide

ExplodeOnCollide::ExplodeOnCollide(Actor* pOwner)
	: Component(pOwner, s_id)
	, m_pOwnerRenderer(static_cast<BasicRenderer*>(pOwner->GetComponent(BasicRenderer::s_id)))
{
	//empty
}

void ExplodeOnCollide::OnCollide()
{
	auto& collidedActors = m_pOwner->GetCollidedActors();
	for (Actor* actor : collidedActors)
	{
		auto pHealth = static_cast<HealthTracker*>( actor->GetComponent(HealthTracker::s_id) );
		assert((pHealth and "Cannot find health component"));
		int damage = (rand() % (s_damageRange.second - s_damageRange.first)) + s_damageRange.first;
		pHealth->ModifyHealth(-damage);
	}
	m_pOwnerRenderer->ChangeSprite((char)TileAppearance::kEmpty);
	m_pOwner->RemoveComponent(s_id);
}

// GiveTreasureCollide on collide

GiveTreasureCollide::GiveTreasureCollide(Actor* pOwner)
	: Component(pOwner, s_id)
	, m_pOwnerRenderer(static_cast<BasicRenderer*>(pOwner->GetComponent(BasicRenderer::s_id)))
{
	//empty
}

void GiveTreasureCollide::OnCollide()
{
	auto& collidedActors = m_pOwner->GetCollidedActors();
	int goldAmount = (rand() % (s_treasureRange.second - s_treasureRange.first)) + s_treasureRange.first;
	for (Actor* actor : collidedActors)
	{
		if (actor->HasTag(GameTag::kPlayer))
			actor->GetComponent<MoneyCounter>()->ChangeMoney(goldAmount);
	}
	m_pOwnerRenderer->ChangeSprite((char)TileAppearance::kEmpty);
	m_pOwner->RemoveComponent(s_id);
}
