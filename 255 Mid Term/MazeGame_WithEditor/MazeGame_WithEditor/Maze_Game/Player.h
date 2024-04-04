#pragma once

#include "Entity.h"

class Player : public Entity
{
	CREATE_CHAR(GameObjectType::kPlayer)
private:
	bool m_invulnerable = false;
	bool m_playerInitiated = true;
	bool m_hasSword = false;
	static constexpr int kDefaultLives = 1;
	inline static const char* kDefaultDisplay = TEXT_RGB(29, 153, 219);
	virtual void Collide( Entity* collidedEntity) override;
	virtual void Kill() override;

	bool m_collided = false;
	bool m_hasKey = false;
	Vector2 m_collideLocation = { 0,0 };
	Entity* m_collidedEntity = nullptr;

	int m_lives = kDefaultLives;
	bool m_alive = true;

	void FightEntity(Entity* otherEntity);
public:

	Player()
		: Entity(s_displayCharacter, movementType::kPlayer, Direction::kDown)
	{ 
		m_displayFormat = kDefaultDisplay;
	}

	bool HasKey() const { return m_hasKey; }
	void DropKey() { m_hasKey = false; }
	void CollectKey() { m_hasKey = true; }
	void CollectSword() { m_hasSword = true;}
	void HitEnemy(Vector2 hitLocation, Entity* collidedEntity);
	void CheckCollisions();
	virtual bool IsPlayer() override{ return true; }
};