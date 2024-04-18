#pragma once
#pragma once
#include <vector>

class Component;

class Actor {
	int x, y;
	//std::vector<Component*> allComponents;
public:
	//void AddComponent(Component* pNewComponent) {
	//	allComponents.emplace_back(pNewComponent);
	//	allComponents.back()->GiveOwner(this);
	//}

	void Print() const { std::cout << "actor printed\n"; }
};

class Component
{
	Actor* m_pOwner;
public:
	using IdType = size_t;

	virtual ~Component() = default;

	constexpr void GiveOwner(Actor* pOwner) { m_pOwner = pOwner; }

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