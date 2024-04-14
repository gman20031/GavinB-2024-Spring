// Tile.h
#pragma once

class Player;

class Tile
{
public:
	virtual ~Tile() = default;  // if your class is being used as a base class, it's best to have a virtual destructor
	virtual void Draw() = 0;
	virtual void OnEnter([[maybe_unused]] Player* pPlayer) { }
};


