#pragma once
#include "GameObject.h"

#include <string>
#include <iostream>
#include <functional>

class Tile;

class Item : public GameObject
{
private:
	Tile* m_pTile;
	char m_appearance;
	std::string m_name;
	std::string m_description;
	const std::function<void(Item*)> m_pUseFunction;


public:
	Item(char appearance, const std::string& name,
		const std::string& description, const std::function<void(Item*)>  pUseFunction);
	
	virtual void SetTile(Tile* pTile) final { m_pTile = pTile; }
	virtual Tile* GetTile() const final { return m_pTile; }

	virtual void Draw() const final;
	void PrintDescription() const;
	virtual void OnTouch(GameObject* pToucher) final;
	void Use() { m_pUseFunction(this); };
};
