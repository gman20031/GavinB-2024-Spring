#pragma once

#include "Animal.h"

class Dog : public Animal
{
public:
    Dog();
    Dog(float energy, float fun, float hunger, float nutrition);

    virtual void Play(float hours) override;
    virtual void PerformSpecialAbility() override;

    virtual void OnEncounterEnemy();    // SOLUTION to the enemy problem

private:
    virtual std::string GetSpecies() const override { return "Dog"; }

    // can change the access level of the virtual function
};

// "Is a dog a kind of animal?"

/*
#include "Cat.h"

class Dog : public Cat
{
   
};

"Is a dog a kind of cat?"

*/

