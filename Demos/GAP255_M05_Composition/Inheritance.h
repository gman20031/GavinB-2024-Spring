#pragma once

#include <iostream>

class Character
{
protected:
    float x;
    float y;
};

class Player : public Character
{
public:
    void Print() const
    {
        std::cout << "Player at " << x << ',' << y << '\n';
    }
};

class Enemy : public Character
{
public:
    void Print() const
    {
        std::cout << "Enemy at " << x << ',' << y << '\n';
    }
};


void Example()
{
    Player player;
    player.Print();
    
    Enemy enemy;
    enemy.Print();
}