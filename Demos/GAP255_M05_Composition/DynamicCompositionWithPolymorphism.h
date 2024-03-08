#pragma once

#include <iostream>

// base class for things like RTS resources
// or money
// or hp/mp
class IResource
{
public:
    virtual void Set(int amount) {}
    virtual bool CanAfford(int amount) const { return false; }
    virtual int Get() const { return 0; }
    virtual void Add(int amount) {}
    virtual bool Spend(int amount) { return false; }
    virtual std::string GetName() const = 0;
};

//TODO: insert base class

class Minerals : public IResource
{
    int m_amount;
public:
    virtual std::string GetName() const override { return "Minerals"; }
    virtual int Get() const override { return m_amount; }
};

class Vespene : public IResource
{
    int m_amount;
public:
    virtual std::string GetName() const override { return "Vespene gas"; }
    virtual int Get() const override { return m_amount; }
};



class Character
{
protected:
    IResource* m_pResource;

public:
    Character(IResource* pPosition) : m_pResource{ pPosition } {}
    ~Character() { delete m_pResource; }
    void Init(IResource* pPosition) { m_pResource = pPosition; }
    virtual void Print() const = 0;
};

// non-virtual interface function + virtual implementation function

class Player : public Character
{
public:
    Player() : Player{ nullptr } {}
    Player(IResource* pPosition) : Character{ pPosition } {}
    virtual void Print() const override
    {
        std::cout << "Player has " << m_pResource->Get() << " " << m_pResource->GetName() << '\n';
    }
};

class Enemy : public Character
{
public:
    Enemy() : Enemy{ nullptr } {}
    Enemy(IResource* pPosition) : Character{ pPosition } {}
    virtual void Print() const override
    {
        std::cout << "Enemy has " << m_pResource->Get() << " " << m_pResource->GetName() << '\n';
    }
};


void Example()
{
    //IResource* pPlayerResource = new Minerals;
    //Player player{ pPlayerResource };
    //// or
    //Player player{ new Minerals };
    // or
    IResource* pPlayerResource = new Minerals;
    Player player;
    player.Init(pPlayerResource);

    player.Print();


    //IResource* pEnemyPosition = new Vespene;
    //Enemy enemy{ pEnemyPosition };
    //// or
    //Enemy enemy{ new Vespene };
    // or
    IResource* pEnemyPosition = new Vespene;
    Enemy enemy;
    enemy.Init(pEnemyPosition);

    enemy.Print();
}