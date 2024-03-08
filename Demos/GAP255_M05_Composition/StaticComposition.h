#pragma once

#include <iostream>

struct Vector2
{
    float x;
    float y;
};

class Player
{
    Vector2 m_position;
public:
    void Print() const
    {
        std::cout << "Player at " << m_position.x << ',' << m_position.y << '\n';
    }
};

class Enemy
{
    Vector2 m_position;
public:
    void Print() const
    {
        std::cout << "Enemy at " << m_position.x << ',' << m_position.y << '\n';
    }
};

void Example()
{
    Player player;
    player.Print();

    Enemy enemy;
    enemy.Print();
}
