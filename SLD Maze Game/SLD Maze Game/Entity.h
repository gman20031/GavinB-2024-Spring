#pragma once
#include "SDL.h"
#include "DisplayModel.h"

class Entity
{
	float m_speedMult;
	int m_moveDistance;
	
	SDL_Point m_playerLocation;
	SDL_Color m_playerColor{ 0,0,0,255 };
	SDL_Vertex* m_charModel;

public:
	//void MoveLocation();

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