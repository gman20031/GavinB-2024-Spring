#include <SDL.h>
#include <SDL_image.h>
#include <assert.h>

#define NO_DEBUG 1
#define DEBUG_MODE 2

#define RUN_MODE DEBUG_MODE
#include "Engine/Debug.h"

#include "Engine/SDL_Manager.h"

#include "Engine/Actor/ActorManager.h"
#include "Engine/Actor/ActorFileIO.h"
#include "Engine/Component/SDLRenderComponent.h"
#include "Game/Components/PlayerComponents.h"


static void MakePlayer(const std::unique_ptr<Actor>& pActor)
{
	SDLRenderComponent* pActorRenderer = pActor->GetComponent<SDLRenderComponent>();
	pActorRenderer->NewTexture("FighterPlane");
	pActorRenderer->ScaleTexture(2);
	pActorRenderer->SetFrame(1);
	pActor->GetComponent<PlayerMover>()->SetSpeedMult(1);
	pActor->GetComponent<PlayerMover>()->SetSpeed(500);

}


int main( [[maybe_unused]]int argc, [[maybe_unused]]char** argv)
{
	const char* title = "Hello, world";
	constexpr int xPosition = 200;
	constexpr int yPosition = 200;
	constexpr int width = 1'000;
	constexpr int height = 1'000;

	SDL_Manager::Init(title, xPosition, yPosition, width, height);

	auto& pPlayer = ActorManager::Get().Create("Player");
	MakePlayer( pPlayer );
	pPlayer->SetPosition( 50, 50 );


	auto startTick = SDL_GetTicks();

	auto gameLoop = [&startTick]() -> bool {
		ActorManager::Get().RenderAll();
		auto Tick = SDL_GetTicks();
		if (Tick - startTick >= (kTicksPerSecond / kUpdatesPerSecond))
		{
			startTick = Tick;
			ActorManager::Get().UpdateAll();
		}
		return true;
	};
	SDL_Manager::Start(gameLoop);

	return 0;
}

