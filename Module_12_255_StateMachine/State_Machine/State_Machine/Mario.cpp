#include "Mario.h"

Mario::Mario()
{
	ChangeState(new MarioSmall(this));
}

void Mario::Damage()
{
	m_dead = true;
}
