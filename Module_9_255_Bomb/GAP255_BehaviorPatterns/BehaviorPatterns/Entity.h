#pragma once

class World;
class EnemyUpdating;
class EntityDrawing;

class Entity
{
protected:
	int m_x;
	int m_y;
	World* m_pWorld;
	int m_hitPoints = 1;

public:
	Entity(int x, int y, World* pWorld);
	virtual ~Entity() = default;

	World* GetWorld() const { return m_pWorld; }
	int GetX() const { return m_x; }
	int GetY() const { return m_y; }

	bool IsDead() const { return (m_hitPoints <= 0); }
	void Damage (int amount);
	void Kill() { m_hitPoints = 0; }

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual bool IsPlayer() { return false; }
};



