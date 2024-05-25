#pragma once

/*
TASK 3: (10)
- Create a file called Trigger.h and implement this class.
NAME: Trigger
PURPOSE: This class implements a game trigger that can have any effect injected into it.
DETAILS:
- Implement this as a class.
- Store a position, e.g. a Vector2<size_t>.
- Is dependent on the Player class from Game.h (you will need to #include Game.h)
- We will use the word 'effect' to describe a function with this signature: void(Player*)
- Functions:
	- ctor(x, y, appearance, effect)
		- effect: a function that will execute when the trigger is stepped on by a Player
	- void SetEffect(newEffect)
		- newEffect: a new function that will replace the existing effect function.
	- void OnStep(Player* pPlayer)
		- SIDE EFFECT: This calls ExecuteEffect, passing in pPlayer.
	- void Draw()
		- SIDE EFFECT: Draws the trigger's appearance (as a char).
*/
#include <iostream>

#include "Vector2.h"

class Player;

class Trigger
{
	using Effect = void(*)(Player*);
private:
	Vector2<size_t> m_position;
	char m_appearance;
	Effect m_effect;

public:
	Trigger(size_t x, size_t y, char appearance, Effect effect);

	void SetEffect(Effect newEffect);
	void OnStep(Player* pPlayer) const;

	void Draw() const{ std::cout << m_appearance; }
	Vector2<size_t> GetPosition() const { return m_position; }
};


