#include "MarioStates.h"
#include "Mario.h"

#include <iostream>

void MarioSmall::EatMushroom()
{
	m_pOwner->ChangeState(new MarioBig(m_pOwner) );
}

void MarioSmall::EatFireFlower()
{
	m_pOwner->ChangeState(new MarioFire(m_pOwner) );
}

void MarioSmall::GetHit()
{
	std::cout << "Mario has been defeated\n";
	m_pOwner->Damage();
}

void MarioSmall::DoAction()
{
}

void MarioSmall::PrintDescription()
{
	std::cout << "Short, red overalls, brown shirt\n";
}

void MarioSmall::OnEnter()
{
	std::cout << "Mario is now small and weak\n";
}

void MarioSmall::OnExit()
{
	std::cout << "Mario is no longer small\n";
}

////////////////////////////////////////////////
// Big Mario
////////////////////////////////////////////////

void MarioBig::EatMushroom()
{
	std::cout << "mario is alredy large enough\n";
}

void MarioBig::EatFireFlower()
{
	m_pOwner->ChangeState(new MarioFire(m_pOwner) );
}

void MarioBig::GetHit()
{
	m_pOwner->ChangeState(new MarioSmall(m_pOwner) );
}

void MarioBig::DoAction()
{
	//
}

void MarioBig::PrintDescription()
{
	std::cout << "Tall, red overalls, brown shirt\n";
}

void MarioBig::OnEnter()
{
	std::cout << "Mario has doubled in size with the strength of the mushroom\n";
}

void MarioBig::OnExit()
{
	std::cout << "Mario no longer has the power of the mushroom\n";
}


////////////////////////////////////////////////
// Fire Mario
////////////////////////////////////////////////


void MarioFire::EatMushroom()
{
	std::cout << "The mushroom is consumed by the fire flower\n";
}

void MarioFire::EatFireFlower()
{
	std::cout << "Mario is already fire mario\n";
}

void MarioFire::GetHit()
{
	m_pOwner->ChangeState(new MarioBig(m_pOwner) );
}

void MarioFire::DoAction()
{
	std::cout << "Mario throws a fireball withe the power of the fire flower\n";
}

void MarioFire::PrintDescription()
{
	std::cout << "Tall, White overalls, red shirt\n";
}

void MarioFire::OnEnter()
{
	std::cout << "Mario gains the power of the fire flower\n";
}

void MarioFire::OnExit()
{
	std::cout << "Mario loses the power of the fire flower\n";
}
