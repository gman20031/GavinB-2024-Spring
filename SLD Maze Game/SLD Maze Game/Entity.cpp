#include "Entity.h"


Entity::Entity()
{
}

void Entity::TeleportLocationTo(SDL_Point& newLocation)
{
	m_playerLocation = newLocation;
	//todo
	// bring all of the model along with it
}

void Entity::updateModelLocation()
{
	// perhaps not needed, if I run the Model += current location instead of making the model constantly
	// moving

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
