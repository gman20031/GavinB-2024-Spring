#include <iostream>
#include "SDL.h"

#include "GameWindow.h"

int main(int argc, char* argv[])
{
#ifdef SDLTESTCODE
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("COuld not init SDL vido\n");
		return 1;
	}

	const int WIDTH = 640; // Width for window
	const int HEIGHT = 480; // height for window
	SDL_Window* StartWindow = NULL; // the current window I am showing
	StartWindow = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);

	SDL_Renderer* renderer = SDL_CreateRenderer(StartWindow, -1, SDL_RENDERER_SOFTWARE);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // what renderer target:R,G,B, alpha  values, 255 alpha = fully visible
	SDL_RenderClear(renderer); // fills render target with current color (red)
	SDL_RenderPresent(renderer); // Tell the renderer to go!

	constexpr int vertexCount = 4;
	// Position of vertex , Color of vertex, Normalized texture coordinates??
	SDL_Vertex vertex_1 = { {0, 0}, {0, 0, 0, 255}, {1, 1} };
	SDL_Vertex vertex_2 = { {0, 100}, {0, 0, 0, 255}, {1, 1} };
	SDL_Vertex vertex_3 = { {100, 0}, {0, 0, 0, 255}, {1, 1} };
	SDL_Vertex vertex_4 = { {100, 100}, {0, 0, 0, 255}, {1, 1} };

	// Put them into array
	SDL_Vertex square[] = {
		vertex_1,
		vertex_2,
		vertex_4
	};

	if ((SDL_RenderGeometry(renderer, 0/*texture val*/, square, vertexCount, NULL, NULL)) == -1) std::cout << "shit\n"; // fails
	// not able to render squares, must always be multiples of 3.
	SDL_RenderPresent(renderer);


	bool keepWindowOpen = true;
	while (keepWindowOpen)
	{
		SDL_Event SdlEvent;
		while (SDL_PollEvent(&SdlEvent) > 0)
		{
			switch (SdlEvent.type)
			{
			case SDL_QUIT:
				keepWindowOpen = false;
				break;
			}

			SDL_UpdateWindowSurface(StartWindow);
		}
	}

	SDL_DestroyWindow(StartWindow);
	SDL_Quit(); // should remove renderer
	return 0;
#endif

	GameWindow TestWindow;
	TestWindow.StartWindow();
	
	return (0);
}
