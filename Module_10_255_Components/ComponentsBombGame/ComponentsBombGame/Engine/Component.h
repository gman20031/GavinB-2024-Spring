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
public: using IdType = size_t;
//public: using IdClass = CounterId;
protected:
	Actor* m_pOwner;
public:
	const size_t m_id;
	Component(Actor* pOwner, const size_t id) : m_pOwner(pOwner), m_id(id) { /*EMPTY*/ }
	virtual ~Component() = default;
	virtual Component* Clone(Actor* pOwner);

	constexpr virtual void Start()	{ /*EMPTY*/ }
	virtual void Render()	{ /*EMPTY*/ }
	virtual void Update()	{ /*EMPTY*/ }
	virtual void OnCollide(){ /*EMPTY*/ }
};

/*	Example subclass Requirements
	
class EnemyMover : Component
{
	NEW_STATIC_ID;
public:
	EnemyMover(Actor* pOwner) : Component(pOwner, s_id) {}
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
#define NEW_STATIC_ID public: const static inline Component::IdType s_id = ComponentStaticIdCounter::Get()
#define SHARED_STATIC_ID(Baseclass) public: const static inline Component::IdType s_id = Baseclass::s_id
private:
	static inline size_t m_next = 0;
public:
	static constexpr size_t Get() {
		return m_next++;
	}
};

//class CounterId
//{
//	using id_t = Component::IdType;
//public:
//	inline static const id_t internal_ID = ComponentStaticIdCounter::Get();
//	constexpr CounterId() = default;
//	static id_t Get() { return internal_ID; }
//
//	constexpr bool operator==(const CounterId& other) const { return (internal_ID == other.internal_ID); }
//	constexpr bool operator==(const id_t& other) const { return (internal_ID == other); }
//	constexpr auto operator<=>(const CounterId& other) const = default;
//	constexpr id_t operator*() { return internal_ID; }
//
//};
