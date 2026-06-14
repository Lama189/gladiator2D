#include "game/dummy.hpp"

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
}

Dummy::~Dummy()
{
    UnloadTexture(texture);
}

void Dummy::update(float dt) 
{
    // nothing
}

void Dummy::draw()
{
    DrawTexture(texture, position.x, position.y, WHITE);
}