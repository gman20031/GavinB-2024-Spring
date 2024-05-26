#pragma once
#include <SDL.h>
#include <unordered_set>

#include "../../Engine/Component/Component.h"
#include "../../Engine/System/Vector2d.h"
#include "../../Engine/Actor/Actor.h"

class PlayerMover : public Component
{
public:
	ID_FROM_NAME("PlayerMover");
private:
	Vector2d<double> m_direction = { 0,0 };
	std::unordered_set<SDL_Scancode> m_pressedKeys;
	uint32_t m_lastTick = 0;
	double m_speedMult = 1;
	int m_pixelsPerSecond = 1;

private: // method
	bool HandleKeyDown(SDL_Event event);
	bool HandleKeyUp(SDL_Event event);
	bool InBounds(const Actor::Position_t& actorPosition) const;

public:
	PlayerMover(Actor* pOwner);


	void SetSpeedMult(double mult) { m_speedMult = mult; }
	void SetSpeed(int speed) { m_pixelsPerSecond = speed; }

	virtual void Update() override;
};



