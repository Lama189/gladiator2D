#include "game/dummy.hpp"
#include <iostream>

Dummy::Dummy(Vector2 pos)
{
    this->position = pos;

    texture = LoadTexture("assets/SuperDummy.png");

    hitbox = {
        position.x,
        position.y,
        (float)texture.width,
        (float)texture.height
    };

    isAlive = true;

    health = 100;
}

Dummy::~Dummy()
{
    UnloadTexture(texture);
}

void Dummy::update(float dt) 
{
    if (!isAlive)
        return;
}

void Dummy::draw()
{
    DrawTexture(texture, position.x, position.y, WHITE);
}

void Dummy::hurt(int damage)
{
    health -= damage;

    std::cout << "Get Hurt!" << "\n";

    if (health <= 0)
        isAlive = false;
}