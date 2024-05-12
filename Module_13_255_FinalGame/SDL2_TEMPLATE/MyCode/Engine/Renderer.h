#pragma once
#include "System/ConsoleManip.h"

#include <SDL.h>

#include "Component.h"
#include "StateMachine.h"
#include "System/Vector2d.h"

// state machine that takes in a sprite - which acts as a state.
// each sprite has a 
// Render() function, among any other shit it wants.
class Renderer;

class Sprite
{
public:
	virtual ~Sprite() = default;
	virtual void Render( Vector2d<int> actorPosition ) = 0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
};

class Renderer : public Component
{
	using Sprite_ptr = std::unique_ptr<Sprite>;
public:
	ID_FROM_NAME("Renderer");

private:
	Sprite_ptr m_pSprite;
	
public:
	Renderer(Actor* pOwner) : Component(pOwner) {}

	template<std::derived_from<Sprite> Sprite_t, typename... ArgTypes>
	void CreateSprite(ArgTypes ... args);
	void ChangeSprite(std::unique_ptr<Sprite> pSprite);
	Sprite_ptr& GetSprite() { return m_pSprite; }

	virtual void Render() override;
};

template<std::derived_from<Sprite> Sprite_t, typename ...ArgTypes>
inline void Renderer::CreateSprite(ArgTypes ...args)
{
	ChangeSprite(std::make_unique(args...));
}

