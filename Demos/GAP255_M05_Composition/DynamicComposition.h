#pragma once

#include <iostream>

struct Vector2
{
    float x;
    float y;
};

class Player
{
    Vector2* m_pPosition;

public:
    Player(Vector2* pPosition) : m_pPosition{ pPosition } {}
    // and/or
    Player() = default;
    void Init(Vector2* pPosition) { m_pPosition = pPosition; }

    //TODO: if you statically allocate the Vector2,
    // this will cause an exception!
    ~Player() { delete m_pPosition; }   // dynamic
    ~Player() = default;                // static

    void Print() const
    {
        std::cout << "Player at " << m_pPosition->x << ',' << m_pPosition->y << '\n';
    }
};

class Enemy
{
    Vector2* m_pPosition;

public:
    Enemy(Vector2* pPosition) : m_pPosition{ pPosition } {}
    // and/or
    Enemy() = default;
    void Init(Vector2* pPosition) { m_pPosition = pPosition; }

    //TODO: if you statically allocate the Vector2,
    // this will cause an exception!
    //~Enemy() { delete m_pPosition; }  // dynamic
    ~Enemy() = default;                 // static

    void Print() const
    {
        std::cout << "Player at " << m_pPosition->x << ',' << m_pPosition->y << '\n';
    }
};

void Example()
{
    //Vector2* pPlayerPosition = new Vector2{ 5,5 };
    //Player player{ pPlayerPosition };
    //// or
    //Player player{ new Vector2{5,5} };
    // or
    //Vector2* pPlayerPosition = new Vector2{ 5,5 };
    //Player player;
    //player.Init(pPlayerPosition);

    Vector2 playerPosition{ 5,5 };
    Player player{ &playerPosition };



    //Vector2* pEnemyPosition = new Vector2{ 5,5 };
    //Enemy enemy{ pEnemyPosition };
    //// or
    //Enemy enemy{ new Vector2{5,5} };
    // or
    Vector2* pEnemyPosition = new Vector2{ 5,5 };
    Enemy enemy;
    enemy.Init(pEnemyPosition);
}