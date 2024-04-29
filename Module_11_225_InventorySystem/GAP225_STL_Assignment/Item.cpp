#include "Item.h"

#include "Tile.h"

#include <iostream>

Item::Item(const char appearance, const std::string& name,
	const std::string& description , const std::function<void(Item*)>  pUseFunction)
	: m_pTile{nullptr}
	, m_appearance{appearance}
	, m_name{name}
	, m_description{description}
	, m_pUseFunction(pUseFunction)
{
}

void Item::Draw() const
{
	std::cout << m_appearance;
}

void Item::PrintDescription() const
{
	std::cout << m_description;
}

/////////////////////////////////////////////////////
// React to being touched by another GameObject.
/////////////////////////////////////////////////////
void Item::OnTouch(GameObject* pToucher)
{
	pToucher->Collect(this);
}

