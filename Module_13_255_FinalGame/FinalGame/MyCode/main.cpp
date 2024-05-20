#include <SDL.h>
#include <SDL_image.h>
#include <assert.h>

#define NO_DEBUG 1
#define DEBUG_MODE 2

#define RUN_MODE DEBUG_MODE
#include "Engine/Debug.h"

#include "Engine/SDL_Manager.h"

#include "Engine/Actor/ActorManager.h"
#include "Engine/Component/SDLRenderComponent.h"


int main( [[maybe_unused]]int argc, [[maybe_unused]]char** argv)
{
	const char* title = "Hello, world";
	constexpr int xPosition = 200;
	constexpr int yPosition = 200;
	constexpr int width = 500;
	constexpr int height = 500;

	SDL_Manager::Init(title, xPosition, yPosition, width, height);

	Actor snowBro;
	snowBro.Init({50, 50});
	auto pRenderer = snowBro.AddComponent<SDLRenderComponent>();
	pRenderer->NewTexture("SnowBro");
	pRenderer->StartAnimation(6, true);
	pRenderer->ScaleTexture(2);
	//ActorManager::Get().GetActors().emplace_back(snowBro);

	//auto& actorManager = ActorManager::Get();

	auto loop = [pRenderer]() -> bool {

		//ActorManager::Get().RenderAll();
		pRenderer->Render();

		SDL_Event SdlEvent;
		while (SDL_PollEvent(&SdlEvent) > 0)
		{
			if (SdlEvent.type == SDL_QUIT)
				return false;
		}
		return true;
	};
	SDL_Manager::Start(loop);

	return 0;
}

