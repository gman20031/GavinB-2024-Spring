#include "Actor.h"

#include <assert.h>

constexpr Component* Actor::AddComponent(Component* pNewComponent)
{
	assert(pNewComponent != nullptr);
}

constexpr Component* Actor::GetComponent(size_t)
{
	return nullptr;
}
