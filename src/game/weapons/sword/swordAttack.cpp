#include "game/weapons/sword/swordAttack.hpp"
#include <iostream>

SwordAttack::SwordAttack(Vector2 pos, float width, float height)
{  
    this->position = pos;
    this->isAlive = true;
    this->hitbox = { pos.x, pos.y, width, height };

    lifetime = 4.f;
}

void SwordAttack::update(float dt)
{
    lifetime -= dt;
    std::cout << "Life time: " << lifetime << "\n";

    if (lifetime <= 0.f)
    {
        isAlive = false;
    }
}

void SwordAttack::draw()
{
    DrawRectangleRec(hitbox, RED);
}