#include "Dog.h"

#include <iostream>

Dog::Dog()
    : Dog{100, 50, 200, 25}
{
}

Dog::Dog(float energy, float fun, float hunger, float nutrition)
    : Animal{energy, fun, hunger, nutrition}
{
}

void Dog::Play(float hours)
{
    std::cout << GetSpecies() << " wants to play fetch!\n";
    Animal::Play(hours);    // base.Play(hours);
}

void Dog::PerformSpecialAbility()
{
    std::cout << GetSpecies() << " digs a hole for no reason.\n";
}

void Dog::OnEncounterEnemy()
{
    std::cout << "BARK BARK BARK BARK BARK\n";
}
