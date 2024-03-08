#include "Cat.h"

#include <iostream>

Cat::Cat()
    : Cat{25, 0, 40, 50}
{
}


Cat::Cat(float energy, float fun, float hunger, float nutrition, int lives)
    : Animal{ energy, fun, hunger, nutrition }
    , m_lives{ lives }
    , m_climbSkill{10}
{
}

void Cat::PerformSpecialAbility()
{
    ClimbTree();

    //--m_lives;
    //if (m_lives <= 0)
    //    std::cout << "Cat has no more lives\n";
    //else
    //    std::cout << "Cat has " << m_lives << " lives remaining\n";
}

void Cat::OnEncounterEnemy()
{
    ClimbTree();
}

void Cat::ClimbTree()
{
    std::cout << GetSpecies() << " climbs " << m_climbSkill
        << " feet into a tree\n";
}



// PROBLEM: when cats encounter an enemy, they climb a tree
//          when dogs encounter an enemy, they bark
//          we have a lot of cats and dogs stored in an Animal* array