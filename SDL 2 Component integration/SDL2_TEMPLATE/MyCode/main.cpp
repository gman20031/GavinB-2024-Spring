#include "SDL.h"

#include <iostream>
#include <utility>
#include <memory>
#include <concepts>
#include <vector>
#include <numeric>
#include <math.h>

template<class T, size_t N>
size_t ArraySize([[maybe_unused]]T(&a)[N])
{
	return N;
}


struct Sprite
{
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;
	SDL_Vertex* m_pVertecies;
	int m_vertexCount;
	int* m_pDrawOrder = nullptr;
	int m_drawCount = 0;
};

Sprite spriteCpy(const Sprite& other)
{
	Sprite output;
	output.m_pRenderer = other.m_pRenderer;
	output.m_pTexture = other.m_pTexture;
	output.m_vertexCount = other.m_vertexCount;
	output.m_drawCount = other.m_drawCount;

	if (other.m_pVertecies)
	{
		output.m_pVertecies = new SDL_Vertex[output.m_vertexCount];
		std::memcpy(output.m_pVertecies, other.m_pVertecies, output.m_vertexCount);
	}
	if (other.m_pDrawOrder)
	{
		output.m_pDrawOrder = new int[output.m_drawCount];
		std::memcpy(output.m_pDrawOrder, other.m_pDrawOrder, output.m_vertexCount);
	}
	return output;
}

static void DrawSprite(Sprite& sprite, SDL_Point pos = {0,0} )
{
	for (size_t i = 0; i < sprite.m_vertexCount; ++i)
	{
		auto& vertex = sprite.m_pVertecies[i];
		vertex.position.x += pos.x;
		vertex.position.y += pos.y;
	}

	SDL_RenderGeometry(
		sprite.m_pRenderer,
		sprite.m_pTexture,
		sprite.m_pVertecies,
		sprite.m_vertexCount,
		sprite.m_pDrawOrder,
		sprite.m_drawCount
	);

	for (size_t i = 0; i < sprite.m_vertexCount; ++i)
	{
		auto& vertex = sprite.m_pVertecies[i];
		vertex.position.x -= pos.x;
		vertex.position.y -= pos.y;
	}
}

static void RotateTriangle(Sprite* pSprite )
{
	SDL_FPoint center{ 0,0 };

	std::vector<float> xValues;
	std::vector<float> yValues;

	for (size_t i = 0; i < pSprite->m_vertexCount; ++i)
	{
		auto& pos = pSprite->m_pVertecies[i].position;
		
		bool xKnown = false;
		bool yKnown = false;
		
		for (auto& knownX : xValues)
		{
			if (knownX == pos.x)
				xKnown = true;
		}
		for (auto& knownY : yValues)
		{
			if (knownY == pos.y)
				yKnown = true;
		}
		if (!xKnown || xValues.empty() )
			xValues.emplace_back(pos.x);
		if (!yKnown || yValues.empty() )
			yValues.emplace_back(pos.y);
	}

	int xCount = xValues.size();
	int yCount = yValues.size();
	int xTotal = std::accumulate(xValues.begin(), xValues.end() , 0);
	int yTotal = std::accumulate(yValues.begin(), yValues.end(), 0);

	std::cout << xTotal / xCount << " , " << yTotal / yCount << '\n';



	// x = (cos( 0 ) * -sin( 0 )) * pointOfRotationX
	// y = (sin( 0 ) * cos ( 0 )) * y
	constexpr double theta = 0;
	double rot_mat[]{ cos(theta) , -sin(theta), sin(theta) , cos(theta) };

	for (size_t i = 0; i < pSprite->m_vertexCount; ++i)
	{
		auto& [ _x , _y ] = pSprite->m_pVertecies[i].position;
		{
			for (auto& rot : X_rot_mat)
				_x *= rot;
			for (auto& rot : Y_rot_mat)
				_y *= rot;
		}
	}

}


int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	const char* title = "Hello, world";
	constexpr int xPosition = 200;
	constexpr int yPosition = 200;
	constexpr int width = 500;
	constexpr int height = 500;

	SDL_Window* pWindow = SDL_CreateWindow(title, xPosition, yPosition, width, height, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, NULL , NULL);

	SDL_Color red{ 255,0,0,255 };
	SDL_Color blue{ 0,0,255,255 };
	SDL_Color green{ 0,255,0,255 };


	SDL_Vertex triangleVertecies[] { {50,0, red}, { 0, 50 , blue}, { 100, 50, green} };
	SDL_Point position{ 50,50 };
	Sprite triangle(pRenderer, nullptr, triangleVertecies, ArraySize(triangleVertecies) ); 
	DrawSprite(triangle , position );

	RotateTriangle(&triangle);

	// hack to stay open
	bool keepRunning = true;
	while (keepRunning)
	{
		SDL_RenderClear(pRenderer);		 //resets the window, setting to default color
		DrawSprite(triangle , position);
		SDL_RenderPresent(pRenderer);	 //displays all the stuff stored int renderer to linked windows
		SDL_UpdateWindowSurface(pWindow);//honestly no idea
		SDL_Event SdlEvent;
		while (SDL_PollEvent(&SdlEvent) > 0)
		{
			if( SdlEvent.type == SDL_QUIT )
				keepRunning = false;
			
		}
	}
	return 0;
}

