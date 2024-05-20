#pragma once

#include <concepts>
#include <string>
#include <vector>

#include "../System/StringHash.h"

class Actor;

////////////////////////////////////////////////////////////
// General Component class
//   constexpr void Start() {}
//   void Render() {}
//   void Update() {}
//   void OnCollide() {}
//	To inherit:
//   add ID_FROM_NAME 
//   and Esnure constructor calls component constructor
////////////////////////////////////////////////////////////
class Component
{
public: 
	using IdType = uint32_t;

protected:
	Actor* m_pOwner;
public:
	//const size_t m_id; , m_id(id)
	Component(Actor* pOwner) : m_pOwner(pOwner) { /*EMPTY*/ }
	virtual ~Component() = default;

	constexpr virtual void Start()	{ /*EMPTY*/ }
	virtual void Render()	{ /*EMPTY*/ }
	virtual void Update()	{ /*EMPTY*/ }
	virtual void OnCollide(){ /*EMPTY*/ }
};

/* -- Subclass template -- 
class ActorTags : public Component
{
private:
	ID_FROM_NAME( "identifier" );
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

#define ID_FROM_NAME(name_c_string) public: static inline constexpr Component::IdType s_id = StringHash(name_c_string);

////////////////////////////////////////////////////////////
// compile time counter to ensure each component has a -
// unique Id
////////////////////////////////////////////////////////////
class ComponentStaticIdCounter
{
#define D_NEW_STATIC_ID public: static inline const Component::IdType s_id = ComponentStaticIdCounter::Get()
private:
	static inline Component::IdType m_next = 0;
public:
	static constexpr Component::IdType Get() {
		return m_next++;
	}
};
