#pragma once

#include <concepts>
#include <SDL.h>

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

	//static bool RegisterEventListener(Callable call)

	template<std::predicate Callable>
	static void Start(Callable gameLoop);
};

template<std::predicate Callable>
inline void SDL_Manager::Start(Callable gameLoop)
{
	// hack to stay open
	bool keepRunning = true;
	while (keepRunning)
	{
		SDL_RenderClear(SDL_Manager::GetSDLRenderer());		 //resets the window, setting to default color
		keepRunning = gameLoop();
		SDL_RenderPresent(SDL_Manager::GetSDLRenderer());	 //displays all the stuff stored int renderer to linked windows
		SDL_UpdateWindowSurface(SDL_Manager::GetSDLWindow());//honestly no idea
	}
}
