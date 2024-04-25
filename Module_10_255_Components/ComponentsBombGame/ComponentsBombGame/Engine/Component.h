#pragma once

#include <concepts>

class Actor;

////////////////////////////////////////////////////////////
// General Component class
//   constexpr void Start() {}
//   void Render() {}
//   void Update() {}
//   void OnCollide() {}
//	To inherit:
//   add NEW_STATIC_ID 
//   and Esnure constructor calls component constructor
////////////////////////////////////////////////////////////
class Component
{
public: using IdType = uint32_t;
protected:
	Actor* m_pOwner;
public:
	const size_t m_id;
	Component(Actor* pOwner, const size_t id) : m_pOwner(pOwner), m_id(id) { /*EMPTY*/ }
	virtual ~Component() = default;
	//virtual Component* Clone(Actor* pOwner);

	constexpr virtual void Start()	{ /*EMPTY*/ }
	virtual void Render()	{ /*EMPTY*/ }
	virtual void Update()	{ /*EMPTY*/ }
	virtual void OnCollide(){ /*EMPTY*/ }
};

/* -- Subclass template -- 
class ActorTags : public Component
{
private:
	NEW_STATIC_ID;
public:
	ActorTags(Actor* pOwner) : Component(pOwner, s_id) { /*EMPTY }
	virtual ~ActorTags() = default;

	constexpr virtual void Start() { /*EMPTY }
	virtual void Render()	{ /*EMPTY }
	virtual void Update()	{ /*EMPTY }
	virtual void OnCollide(){ /*EMPTY }
};
*/

////////////////////////////////////////////////////////////
// Concept equivilant to - std::derived_from<T, Component>
////////////////////////////////////////////////////////////
template<class T>
concept SubComponent = std::derived_from<T, Component>;

////////////////////////////////////////////////////////////
// compile time counter to ensure each component has a -
// unique Id
////////////////////////////////////////////////////////////
class ComponentStaticIdCounter
{
#define NEW_STATIC_ID public: static inline const Component::IdType s_id = ComponentStaticIdCounter::Get()
//#define SHARED_STATIC_ID(Baseclass) public: const static inline Component::IdType s_id = Baseclass::s_id
private:
	static inline Component::IdType m_next = 0;
public:
	static constexpr Component::IdType Get() {
		return m_next++;
	}
};
