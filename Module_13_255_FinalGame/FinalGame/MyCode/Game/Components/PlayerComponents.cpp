#include "PlayerComponents.h"

#include "../../Engine/SDL_Manager.h"
#include "../../Engine/Actor/Actor.h"
#include "../../Engine/Debug.h"


bool PlayerMover::HandleKeyDown(SDL_Event event)
{
	auto keyScanCode = event.key.keysym.scancode;

	if (m_pressedKeys.contains(keyScanCode))
		return true;
	m_pressedKeys.insert(keyScanCode);

	switch (keyScanCode)
	{
	case SDL_SCANCODE_W: m_direction.y += -1; break;
	case SDL_SCANCODE_S: m_direction.y += 1;break;
	case SDL_SCANCODE_A: m_direction.x += -1;break;
	case SDL_SCANCODE_D: m_direction.x += 1;	break;
	}
	DEBUG_PRINT("KEY DOWN : " << (SDL_Scancode)keyScanCode);
	return true;
}

bool PlayerMover::HandleKeyUp(SDL_Event event)
{
	auto keyScanCode = event.key.keysym.scancode;
	m_pressedKeys.erase(keyScanCode);
	switch (keyScanCode)
	{
	case SDL_SCANCODE_W: m_direction.y -= -1; break;
	case SDL_SCANCODE_S: m_direction.y -= 1; break;
	case SDL_SCANCODE_A: m_direction.x -= -1; break;
	case SDL_SCANCODE_D: m_direction.x -= 1; break;
	}
	DEBUG_PRINT("KEY UP : " << (SDL_Scancode)keyScanCode);

	return true;
}

PlayerMover::PlayerMover(Actor* pOwner)
	: Component(pOwner)
{
	auto keyDown = [this](SDL_Event e) -> bool
		{
			return this->HandleKeyDown(e);
		};
	auto keyUp = [this](SDL_Event e) -> bool
		{
			return this->HandleKeyUp(e);
		};

	SDL_Manager::RegisterEventListener(keyDown, SDL_KEYDOWN);
	SDL_Manager::RegisterEventListener(keyUp, SDL_KEYUP);
	//SDL_Manager::RegisterEventListener( HandleKeyDown, SDL_KEYDOWN);
}

void PlayerMover::Update()
{
#if 1
	if (m_direction != Vector2d<double>{0, 0})
		DEBUG_PRINT("Moving Now, Direciton at : " << m_direction * m_speedMult);
#endif
	auto pos = m_pOwner->GetPosition();
	pos.x += (m_direction.x * m_speedMult);
	pos.y += (m_direction.y * m_speedMult);
	m_pOwner->SetPosition(pos);

}
