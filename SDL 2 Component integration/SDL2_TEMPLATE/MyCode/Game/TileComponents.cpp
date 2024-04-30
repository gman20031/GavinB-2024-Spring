#include "TileComponents.h"

#include "../Engine/Actor.h"

#include "GameTags.h"
#include "HealthTracker.h"
#include "Appearances.h"
#include "PlayerComponents.h"
#include "World.h"

// EndGameOnCollide on collide

void EndGameOnCollide::OnCollide()
{
	auto& collidedActors = m_pOwner->GetComponent<Basic2dCollider>()->CollidedActors();
	for (Actor* actor : collidedActors)
	{
		if (actor->GetComponent<ActorTags>()->HasTag(GameTag::kPlayer))
			actor->GetWorldPtr()->EndGame();
	}
}

// explode on collide

ExplodeOnCollide::ExplodeOnCollide(Actor* pOwner)
	: Component(pOwner, s_id)
	, m_pOwnerRenderer(pOwner->GetComponent<WindowRenderer2D>())
{
	//empty
}

void ExplodeOnCollide::OnCollide()
{
	if (m_exploded)
		return;

	auto& collidedActors = m_pOwner->GetComponent<Basic2dCollider>()->CollidedActors();
	for (Actor* actor : collidedActors)
	{
		auto pHealth = static_cast<HealthTracker*>( actor->GetComponent(HealthTracker::s_id) );
		assert((pHealth && "Cannot find health component"));
		int damage = (rand() % (s_damageRange.second - s_damageRange.first)) + s_damageRange.first;
		pHealth->ModifyHealth(-damage);
	}
	m_pOwnerRenderer->SetSprite("Game/Sprites/Bomb.bmp");
	m_exploded = true;
}

// GiveTreasureCollide on collide

GiveTreasureCollide::GiveTreasureCollide(Actor* pOwner)
	: Component(pOwner, s_id)
	, m_pOwnerRenderer(pOwner->GetComponent<WindowRenderer2D>())
{
	//empty
}

void GiveTreasureCollide::OnCollide()
{
	if (m_used)
		return;
	auto& collidedActors = m_pOwner->GetComponent<Basic2dCollider>()->CollidedActors();
	int goldAmount = (rand() % (s_treasureRange.second - s_treasureRange.first)) + s_treasureRange.first;
	for (Actor* actor : collidedActors)
	{
		auto pTags = actor->GetComponent<ActorTags>();
		if(pTags)
		{
			if (pTags->HasTag(GameTag::kPlayer))
				actor->GetComponent<MoneyCounter>()->ChangeMoney(goldAmount);
		}
	}
	m_pOwnerRenderer->SetSprite("Game/Sprites/EmptyTile.bmp");
	m_used = true;
}

// TeleportCollide on collide

void TeleportCollide::Init(Vector2d<int> linkedPosition)
{
	m_linkedPosition = linkedPosition;
}

void TeleportCollide::OnCollide()
{
	auto& collidedActors = m_pOwner->GetComponent<Basic2dCollider>()->CollidedActors();
	for (Actor* actor : collidedActors)
	{
		actor->SetPosition(m_linkedPosition);
	}
}
