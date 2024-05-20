#include "../../Engine/Component/ComponentFactory.h"
#include <tuple>

#include "PlayerComponents.h"

static std::tuple<
	ComponentFactory::Registrar<PlayerMover>> regristrar;


