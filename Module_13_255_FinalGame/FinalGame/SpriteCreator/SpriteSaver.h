#pragma once


#include "../MyCode/Engine/Sprite_2D.h"

class SpriteSaver
{
	using Sprite_ptr_unique = std::unique_ptr<Sprite>;

	Sprite* m_pSprite;

public:
	SpriteSaver();


	/*
	* Saves a sprite.
	*/
	void Save(Sprite* savedSprite);

	/*
	* Takes in a filepath where the sprite is expected to be saved to
	* loads the data into a sprite class and returns a unique pointer of that sprite. 
	*/
	Sprite_ptr_unique Load(const char* filePath);
};
