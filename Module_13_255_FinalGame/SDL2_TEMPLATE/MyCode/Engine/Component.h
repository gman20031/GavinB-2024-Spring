#pragma once

#include <concepts>
#include <string>

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
public: 
	using IdType = uint32_t;

protected:
	Actor* m_pOwner;
public:
	//const size_t m_id; , m_id(id)
	Component(Actor* pOwner) : m_pOwner(pOwner) { /*EMPTY*/ }
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

// Using '!=' disables compiler warnings.
//constexpr auto cString = string.c_str();
// from eastl string.h - string hash template overload
constexpr uint32_t StringHash(const char* cString)
{
	// kPrime = 16777619;
	// kOffset = 2166136261U
	unsigned int character , result = 2166136261U; // They implement an FNV-like string hash.
	while ((character = *(cString++)) != '\0')
		result = (result * 16777619) ^ character;
	return (uint32_t)result;
}

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
