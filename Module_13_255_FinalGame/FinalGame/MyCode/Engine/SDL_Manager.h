#pragma once

#include <concepts>
#include <SDL.h>
#include <memory>

#include "SDL_EventListener.h"

static constexpr uint32_t kMilisecondsPerSecond = 1'000;
static constexpr uint32_t kTicksPerSecond = kMilisecondsPerSecond;

struct WindowInfo
{
	int xPos, yPos;
	int width, height;
};

class SDL_Manager
{
public:

private:
	inline static SDL_Renderer* m_pRenderer = nullptr ;
	inline static SDL_Window* m_pWindow = nullptr;
	inline static int m_xPos, m_yPos, m_width, m_height;
	inline static bool m_keepRunning = true;
	
	inline static std::unique_ptr<SDLEventObserver> pEventObserver;

private:
	SDL_Manager() = default;
public:
	static SDL_Renderer* GetSDLRenderer() { return m_pRenderer; }
	static SDL_Window* GetSDLWindow() { return m_pWindow; }
	static void Init(
		  const char* title
		, int xPos, int yPos
		, int width, int height
		, SDL_WindowFlags windowFlags = SDL_WINDOW_RESIZABLE
	);

	static WindowInfo GetWindowInfo();

	template<std::predicate<SDL_Event> SdlCallable>
	static void RegisterEventListener(SdlCallable callback, SDL_EventType eventType );

	template<std::predicate Callable> static void Start(Callable&& gameLoop);
	static void Stop() { m_keepRunning = false; }
};

template<std::predicate<SDL_Event> SdlCallable>
void SDL_Manager::RegisterEventListener(SdlCallable callback, SDL_EventType eventType)
{
	if (!pEventObserver)
		pEventObserver = std::make_unique<SDLEventObserver>();

	pEventObserver->RegisterListener(callback, eventType);
}

template<std::predicate Callable>
inline void SDL_Manager::Start(Callable&& gameLoop)
{
	auto stopGameOnQuit = []([[maybe_unused]]SDL_Event event) -> bool
		{
			SDL_Manager::Stop();
			return false;
		};
	RegisterEventListener(stopGameOnQuit, SDL_QUIT);

	while (m_keepRunning)
	{
		SDL_RenderClear(SDL_Manager::GetSDLRenderer());		 //resets the window, setting to default color

		if(pEventObserver)
		{
			SDL_Event SdlEvent;
			while (SDL_PollEvent(&SdlEvent) > 0)
				pEventObserver->PushEvent(SdlEvent);
		}
		if (m_keepRunning)
			m_keepRunning = gameLoop();

		SDL_RenderPresent(SDL_Manager::GetSDLRenderer());	 //displays all the stuff stored int renderer to linked windows
		SDL_UpdateWindowSurface(SDL_Manager::GetSDLWindow());//honestly no idea
	}
}
