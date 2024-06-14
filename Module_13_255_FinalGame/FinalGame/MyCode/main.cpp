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
#include "Engine/Component/TextureFileIO.h"
#include "Game/Components/PlayerComponents.h"

/*
TODOODLY DOO's		- Error | Solution first thought.

	- reduce the number of super long inclusion paths needed in game code  |  Add a single include for engine containing all other header files | move all engine headers into .lib folder and path with visual studio

	- Delink texture wrapper from SDL_Texture instance to reduce needless copies | Remove all linking to the underlying texture outside of Render() functions
		 - Then.. Make TextureIO save SDL_texture pointers in cache instead of save info

	- Actor loading should not require a function to set specific features,	| Bit dump actor files then read the data into a ?? container
			it should all be initable from the file input				   .. and let each component just pop the data it needs off the top, in order that they're added.

	- Allow window to be fully resizeable while mainting all logic	| Add event listener to notice a window resize, learn the new size, and have a variable that tracks the scale diff from start.
																   .. The run all logic and pixel info through the base size of the window scaling as late as possible.
														
	- Collison system to start working | ???

non issue / reminders
	- Ensure main game loop does not require any modification to let any logic happen
	- Does render need to happen as fast as it does?

*/



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
	const char* title = "Not a shooter anymore";
	constexpr int xPosition = 200;
	constexpr int yPosition = 200;
	constexpr int width = 1'000;
	constexpr int height = 700;

	SDL_Manager::Init(title, xPosition, yPosition, width, height);

	auto& pBackGround = ActorManager::Get().Create("Background");
	pBackGround->GetComponent< SDLRenderComponent>()->NewTexture("Background");

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

	DEBUG_PRINT("Game starting!");
	ActorManager::Get().StartAll();
	SDL_Manager::Start(gameLoop);

	return 0;
}

