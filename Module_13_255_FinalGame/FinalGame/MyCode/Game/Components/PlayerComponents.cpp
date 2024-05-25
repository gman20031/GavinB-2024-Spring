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
	case SDL_SCANCODE_D: m_direction.x += 1; break;
	case SDL_SCANCODE_Q: m_pOwner->GetComponent<SDLRenderComponent>()->SetFrame(0); break;
	case SDL_SCANCODE_E: m_pOwner->GetComponent<SDLRenderComponent>()->SetFrame(2); break;
	}
	return true;
}

bool PlayerMover::HandleKeyUp(SDL_Event event)
{
	auto keyScanCode = event.key.keysym.scancode;
	m_pressedKeys.erase(keyScanCode);
	switch (keyScanCode)
	{
	case SDL_SCANCODE_W: m_direction.y -= -1; break;
	case SDL_SCANCODE_S: m_direction.y -= 1;  break;
	case SDL_SCANCODE_A: m_direction.x -= -1; break;
	case SDL_SCANCODE_D: m_direction.x -= 1;  break;
	}
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
	uint32_t currentTick = SDL_GetTicks();

	auto dir = m_direction;
	if (dir.x > 0)
		m_pOwner->GetComponent<SDLRenderComponent>()->SetFrame(2);
	if (dir.x == 0)
		m_pOwner->GetComponent<SDLRenderComponent>()->SetFrame(1);
	if (dir.x < 0)
		m_pOwner->GetComponent<SDLRenderComponent>()->SetFrame(0);

	if (dir == Vector2d<double>{0, 0})
	{
		m_lastTick = currentTick;
		return;
	}
	
	double ticksPassed = currentTick - m_lastTick;
	double secondsPassed = (ticksPassed / kTicksPerSecond);
	double speedMultiplier = (secondsPassed * m_pixelsPerSecond) * m_speedMult;
	dir.Normalize() *= speedMultiplier;
	auto pos = m_pOwner->GetPosition();
	pos += dir;
	//DEBUG_PRINT(ticksPassed  << " , " << secondsPassed << " , " << speedMultiplier);
	m_pOwner->SetPosition(pos);
	m_lastTick = currentTick;
}
