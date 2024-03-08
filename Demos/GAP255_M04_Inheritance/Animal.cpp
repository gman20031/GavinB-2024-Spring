#include "Animal.h"
#include <iostream>

Animal::Animal()
    : Animal{100, 50, 0, 100}
{
}

Animal::Animal(float energy, float fun, float hunger, float nutrition)
    : m_energy{ energy }
    , m_fun{ fun }
    , m_hunger{ hunger }
    , m_nutrition{ nutrition }
{
}

void Animal::Sleep(float hours)
{
    static constexpr float kEnergyPerHour = 10;
    static constexpr float kFunPerHour = 10;
    static constexpr float kHungerPerHour = 10;
    static constexpr float kNutritionPerHour = 10;

    m_energy += hours * kEnergyPerHour;
    m_fun -= hours * kFunPerHour;
    m_hunger += hours * kHungerPerHour;
    m_nutrition -= hours * kNutritionPerHour;
    PrintSleepResult();
}

void Animal::Hunt(float hours)
{
    static constexpr float kEnergyPerHour = 15;
    static constexpr float kFunPerHour = 12;
    static constexpr float kHungerPerHour = 10;
    static constexpr float kNutritionPerHour = 10;

    m_energy -= hours * kEnergyPerHour;
    m_fun += hours * kFunPerHour;
    m_hunger += hours * kHungerPerHour;
    m_nutrition -= hours * kNutritionPerHour;
    std::cout << GetSpecies() << " is hunting. Energy decreases to " << m_energy << '\n';
}

void Animal::Eat(float massInKg)
{
    static constexpr float kEnergyPerKg = 1;
    static constexpr float kFunPerKg = 1;
    static constexpr float kHungerPerKg = 10;
    static constexpr float kNutritionPerKg = 10;

    m_energy -= massInKg * kEnergyPerKg;
    m_fun += massInKg * kFunPerKg;
    m_hunger -= massInKg * kHungerPerKg;
    m_nutrition += massInKg * kNutritionPerKg;
    std::cout << GetSpecies() << " is eating. Hunger decreases to " << m_hunger
        << " and nutrition increases to " << m_nutrition << '\n';
}

void Animal::Play(float hours)
{
    static constexpr float kEnergyPerHour = 5;
    static constexpr float kFunPerHour = 20;
    static constexpr float kHungerPerHour = 10;
    static constexpr float kNutritionPerHour = 10;

    m_energy -= hours * kEnergyPerHour;
    m_fun += hours * kFunPerHour;
    m_hunger += hours * kHungerPerHour;
    m_nutrition -= hours * kNutritionPerHour;
    std::cout << GetSpecies() << " is playing. Fun increases to " << m_fun << '\n';
}

void Animal::PrintSleepResult() const
{
    std::cout << GetSpecies() << " is sleeping. Energy increases to " << m_energy << '\n';
}
