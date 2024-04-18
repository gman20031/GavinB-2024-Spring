#pragma once

#include "Actor.h"

class Component
{
protected:
	Actor* m_pOwner;

public:
	using IdType = size_t;

	virtual ~Component() = default;

	virtual void Render() {}
	virtual void Start() {}
	virtual void Update() {}
	virtual void OnCollide() {}

};

/*

actor Teleporter : public Actor
	+ basic Renderer
	+ basic Collider
	+ other Components
		+ teleportOnCollide
		
		class teleportOnCollide : public Component
			+ int x,y
			+ teleportOnCollide(int x, int y, owner)
			+ OnCollide() { for all enemies collided with, set positions to x,y }

*/