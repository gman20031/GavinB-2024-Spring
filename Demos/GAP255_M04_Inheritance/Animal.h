#pragma once

#include <string>

class Animal
{
protected:
    float m_energy;
    float m_fun;
    float m_hunger;
    float m_nutrition;

public:
    Animal();   // default constructor
    Animal(float energy, float fun, float hunger, float nutrition);
    virtual ~Animal() = default;

    void Sleep(float hours);
    void Hunt(float hours);
    void Eat(float massInKg);
    virtual void Play(float hours);
    virtual void PerformSpecialAbility() {}
    virtual void OnEncounterEnemy() {}

protected:
    virtual std::string GetSpecies() const = 0;

private:
    void PrintSleepResult() const;
    
};