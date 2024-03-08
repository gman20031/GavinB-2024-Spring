#pragma once

#include "Animal.h"

class Cat : public Animal
{
private:
    static constexpr int kStartingLives = 9;

    //float m_energy;
    //float m_fun;
    //float m_hunger;
    //float m_nutrition;
    int m_lives;// = 9;
    float m_climbSkill;

public:
    Cat();
    Cat(float energy, float fun, float hunger, float nutrition, int lives = 9);

    //void Sleep(float hours);
    //void Hunt(float hours);
    //void Eat(float massInKg);
    //void Play(float hours);

    virtual void PerformSpecialAbility() override;
    virtual void OnEncounterEnemy() override;
    void ClimbTree();   // SOLUTION to the enemy problem

private:
    virtual std::string GetSpecies() const { return "Cat"; }
};