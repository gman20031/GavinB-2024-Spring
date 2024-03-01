#pragma once
#include "SDL.h"

#define TEST_MODEL_ONE 1

class Entity
{
	SDL_Vertex* m_verteciesStart = nullptr;
	SDL_Vertex* m_entityVertecies = nullptr;
	size_t m_vertexCount = 0;
	int* m_pDrawOrder = nullptr;
	int m_drawOrderCount = 0;

	SDL_Point m_location{ 0,0 };
	SDL_Color m_Color{ 0,0,0,255 };
	SDL_Texture* m_pTexture = 0;
	SDL_Renderer* m_renderer = nullptr; // redundant?
				// the current game window should know tf renderer we are using
				// this also brings up if gamewindow should handle everything.

	void updateModelLocation(); // perhaps reduntant

public:
	Entity();
	Entity(SDL_Vertex* model, size_t vertexCount, int* drawOrder, int orderCount, SDL_Point startLocation);
	~Entity() = default;

	// Add model

	void TeleportLocationTo(SDL_Point newLocation);
	
	void SetRenderer(SDL_Renderer* SDLRenderer);
	void DrawToRenderer(SDL_Renderer* SDLRenderer);
	void Draw();
	

	//void moveTowards
	//Move(direction)
		//*helper functions
		// Move(towards Point)
		// UpdateCharModel()

	/*
	Get and move their position
	when position is moved, move the model along with it.
	Move in specified direction distance * multiplier pixels.
	the location is the Bottom-most center point of the model.

	Change and Get color of the model.
	all models are unicoloured right now. 

	This class does not draw, but stores all the info for entities
	that is required for the GameWindow to not need to worry about any entity
	*/
};