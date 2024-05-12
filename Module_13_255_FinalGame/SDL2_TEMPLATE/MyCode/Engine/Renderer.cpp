#include "Renderer.h"

#include "Actor.h"

void Renderer::ChangeSprite(std::unique_ptr<Sprite> pSprite)
{
	m_pSprite->OnExit();
	m_pSprite.swap(pSprite);
	m_pSprite->OnEnter();
}

void Renderer::Render()
{
	m_pSprite->Render( m_pOwner->GetPosition() );
}