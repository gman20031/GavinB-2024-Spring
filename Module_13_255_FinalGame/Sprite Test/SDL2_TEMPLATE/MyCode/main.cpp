#include <SDL.h>
#include <iostream>
#include <assert.h>

#include "Texture.h"
#include "TextureFileIO.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	const char* title = "Sprite Animation Test";
	constexpr int xPosition = 200;
	constexpr int yPosition = 200;
	constexpr int width		= 500;
	constexpr int height	= 500;

	assert(SDL_Init(SDL_INIT_VIDEO) == 0);

	SDL_Window*   pWindow	= SDL_CreateWindow(title, xPosition, yPosition, width, height, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, NULL, NULL);

	double rotationAngle = 0;
	SDL_Point rotationPoint{ 0,0 };
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	constexpr int ticksPerSecond = 1'000;
	constexpr int framesPerSecond = 15;


	const char* snowBroImagePath = "Textures/TornadoSnowBro.bmp";
	constexpr int maxFrames = 8;
	constexpr Vector2d spriteDimensions( 32,32 );

	Texture snowBroTexture(snowBroImagePath, maxFrames, spriteDimensions, pRenderer);

	TextureFileIO::Save(snowBroTexture, "SnowBro");
	auto pSnowBro = TextureFileIO::Create("SnowBro" , pRenderer);
	SDL_SetTextureScaleMode( pSnowBro->GetSDLTexture(), SDL_ScaleModeNearest);

	uint32_t timingStart = SDL_GetTicks();

	bool keepRunning = true;
	while(keepRunning)
	{
		SDL_RenderClear(pRenderer);		 //resets the window, setting to default color

		pSnowBro->RenderCurrentFrame( { 0,0,pRenderer, rotationAngle, rotationPoint, flip } );

		uint32_t currentTime = SDL_GetTicks();
		std::cout << currentTime << '\n';
		if (currentTime - timingStart > (ticksPerSecond / framesPerSecond))
		{
			pSnowBro->ChangeFrame(1);
			timingStart = currentTime;
		}

		SDL_RenderPresent(pRenderer);	 //displays all the stuff stored int renderer to linked windows
		SDL_UpdateWindowSurface(pWindow);//honestly no idea
		SDL_Event SdlEvent;
		while (SDL_PollEvent(&SdlEvent) > 0)
		{
			if (SdlEvent.type == SDL_QUIT)
				keepRunning = false;
		}
	}
	return 0;
}