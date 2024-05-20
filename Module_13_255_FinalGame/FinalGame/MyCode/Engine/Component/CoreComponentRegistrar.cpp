#include "../../Engine/Component/ComponentFactory.h"
#include <tuple>

#include "ActorTags.h"
#include "SDLRenderComponent.h"
#include "Basic2dCollider.h"

static std::tuple<
	ComponentFactory::Registrar<ActorTags>,
	ComponentFactory::Registrar<SDLRenderComponent>,
	ComponentFactory::Registrar<Basic2dCollider>> regristrar;


