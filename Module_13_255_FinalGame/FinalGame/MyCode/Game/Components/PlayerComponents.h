#pragma once
#include <SDL.h>
#include <unordered_set>

#include "../../Engine/Component/Component.h"
#include "../../Engine/System/Vector2d.h"


class PlayerMover : public Component
{
public:
	ID_FROM_NAME("PlayerMover");
private:
	Vector2d<double> m_direction = { 0,0 };
	std::unordered_set<SDL_Scancode> m_pressedKeys;

private: // method
	bool HandleKeyDown(SDL_Event event);
	bool HandleKeyUp(SDL_Event event);

public:
	PlayerMover(Actor* pOwner);

	double m_speedMult = 1;

	virtual void Update() override;
};



