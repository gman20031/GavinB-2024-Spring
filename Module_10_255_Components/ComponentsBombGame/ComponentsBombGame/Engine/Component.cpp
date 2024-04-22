#include "Component.h"
#include "ComponentFactory.h"

Component* Component::Clone(Actor* pOwner)
{
	 return ComponentFactory::Create(m_id, pOwner);
}
