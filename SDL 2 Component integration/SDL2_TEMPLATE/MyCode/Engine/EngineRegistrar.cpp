#include <tuple>
#include "ComponentFactory.h"
#include "Basic2dCollider.h"
#include "SDL_Integration\WindowRenderer2D.h"


static std::tuple<
	ComponentFactory::Registrar<Basic2dCollider>,

	ComponentFactory::Registrar<WindowRenderer2D>, 
	ComponentFactory::Registrar<ConsoleRenderer>> Registrar;