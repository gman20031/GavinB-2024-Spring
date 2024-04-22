#pragma once

#include <concepts>
#include <iostream>

class Actor;

////////////////////////////////////////////////////////////
// General Component class
//   constexpr void Start() {}
//   void Render() {}
//   void Update() {}
//   void OnCollide() {}
// Subclasses Require Unique static Id
////////////////////////////////////////////////////////////
class Component
{
public: using IdType = size_t;
//public: using IdClass = CounterId;
protected:
	Actor* m_pOwner;
	const size_t m_Id;
public:
	Component(Actor* pOwner, const IdType id) : m_pOwner(pOwner), m_Id(id) { /*EMPTY*/ }
	virtual ~Component() = default;

	constexpr virtual void Start()	{ /*EMPTY*/ }
	virtual void Render()	{ /*EMPTY*/ }
	virtual void Update()	{ /*EMPTY*/ }
	virtual void OnCollide(){ /*EMPTY*/ }
};

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

class CounterId
{
	using id_t = Component::IdType;
	static inline id_t m_next = 0;
	static constexpr id_t next() {return m_next++;}
	const id_t m_id = 0;
public:
	constexpr CounterId() : m_id(next()) {}
	constexpr const id_t Get() const { return m_id; }

	constexpr bool operator==(const CounterId& other) const { return (m_id == other.m_id); }
	constexpr bool operator==(const id_t& other) const { return (m_id == other); }
	constexpr auto operator<=>(const CounterId& other) const = default;
	friend std::ostream& operator<<(std::ostream& os, const CounterId& Counter){ os << Counter.m_id; return os; }
	constexpr const id_t operator*() { return m_id; }

};