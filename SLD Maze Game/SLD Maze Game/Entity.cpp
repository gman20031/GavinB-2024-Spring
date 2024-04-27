#include "Entity.h"

Entity::Entity()
{
#if TEST_MODEL_ONE
	/*
		   *
		  ***
		 *****
	*/
	m_vertexCount = 3;
	m_drawOrderCount = 0;
	m_pDrawOrder = nullptr;

	SDL_Vertex vertex_1 = { {50, 0}, {0, 0, 0, 255}, {1, 1} }; // tip
	SDL_Vertex vertex_2 = { {0, 50}, {0, 0, 0, 255}, {1, 1} }; // bottom left
	SDL_Vertex vertex_3 = { {100, 50}, {0, 0, 0, 255}, {1, 1} }; // bottom right
	m_entityVertecies = new SDL_Vertex[3];
	m_verteciesStart = new SDL_Vertex[3];
	m_entityVertecies[0] = vertex_1;
	m_entityVertecies[1] = vertex_2;
	m_entityVertecies[2] = vertex_3;

	m_verteciesStart[0] = vertex_1;
	m_verteciesStart[1] = vertex_2;
	m_verteciesStart[2] = vertex_3;

	m_location = { 50,50 };
	updateModelLocation();


#endif // TEST_MODEL_ONE

}

////////////////////////////////////////////////////////////////////////////////////
// Construct Entity by passing full piece of geometry
////////////////////////////////////////////////////////////////////////////////////
Entity::Entity(SDL_Vertex* model, size_t vertexCount, int* drawOrder, int orderCount, SDL_Point startLocation)
{
#if TEST_MODEL_ONE
	Entity::Entity();
#endif
}

////////////////////////////////////////////////////////////////////////////////////
// Set the location of entity
////////////////////////////////////////////////////////////////////////////////////
void Entity::TeleportLocationTo(SDL_Point newLocation)
{
	m_location = newLocation;
	updateModelLocation();
	//todo
	// bring all of the model along with it
}

void Entity::updateModelLocation()
{
	// perhaps not needed, if I run the Model += current location instead of making the model constantly
	// update while moving

	for (size_t i = 0; i < m_vertexCount; ++i)
	{
		m_entityVertecies[i].position.x = m_location.x + m_verteciesStart[i].position.x ;
		m_entityVertecies[i].position.y = m_location.y + m_verteciesStart[i].position.y ;
	}
}



////////////////////////////////////////////////////////////////////////////////////
// Draws the entity to the specified SDL renderer
////////////////////////////////////////////////////////////////////////////////////
void Entity::DrawToRenderer(SDL_Renderer* SDLRenderer)
{


}

////////////////////////////////////////////////////////////////////////////////////
// Draws the entity to saved SDL renderer
////////////////////////////////////////////////////////////////////////////////////
void Entity::Draw()
{
	SDL_RenderGeometry(m_renderer, m_pTexture, m_entityVertecies, m_vertexCount, m_pDrawOrder, m_drawOrderCount);

}

void Entity::SetRenderer(SDL_Renderer* SDLRenderer)
{
	m_renderer = SDLRenderer;
}


//SDL_Vertex* Entity::GetCharModel()
//{
//	return m_charModel;
//}

//void PlayerCharacter::DrawPlayer()
//{
//
//
//}
