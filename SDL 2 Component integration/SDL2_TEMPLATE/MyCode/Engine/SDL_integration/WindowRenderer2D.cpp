#include "WindowRenderer2D.h"
#include "../Actor.h"

WindowRenderer2D::WindowRenderer2D(Actor* pOwner)
	: BasicRenderer(pOwner , s_id)
	, m_pSprite(nullptr)
{
	// EMPTY
}

WindowRenderer2D& WindowRenderer2D::Init(SDL_Renderer* pRenderer, const char* filePath)
{
	m_pSprite = std::make_shared<Sprite_t>(filePath, pRenderer);
	return *this;
}

void WindowRenderer2D::SetSprite(const char* filePath)
{
	SDL_Renderer* pRenderer = m_pSprite->GetRenderer();
	m_pSprite = std::make_shared<Sprite_t>(filePath, pRenderer);
}

void WindowRenderer2D::Render()
{
	Vector2d<int> drawnPosition = m_pOwner->GetPosition();
	auto dimensions = m_pSprite->GetDimensions();

	drawnPosition.x += (dimensions.x / 2);
	drawnPosition.y += (dimensions.y / 2);

	m_pSprite->Render(
		drawnPosition.x,
		drawnPosition.y,
		nullptr,
		m_rotation,
		nullptr,
		m_flip
	);
}
