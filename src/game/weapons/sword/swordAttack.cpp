#include "game/weapons/sword/swordAttack.hpp"
#include "game/player.hpp"
#include <iostream>
#include <cmath>

SwordAttack::SwordAttack(Player& owner) : owner(owner)
{  
    this->position = owner.getPosition();
    this->isAlive = true;
    this->hitbox = { this->position.x, this->position.y, 10.f, 15.f };

    lifetime = 0.15f;

    startAngle = -60.0f;
    endAngle   = 60.0f;

    radius = 80.0f;
}

void SwordAttack::update(float dt)
{
    lifetime -= dt;

    if (lifetime <= 0.f)
        isAlive = false;    

    Vector2 mousePos = GetMousePosition();
    Vector2 center = owner.getPosition(); // owner.getCenter is bad here

    Vector2 dir = {
        mousePos.x - center.x,
        mousePos.y - center.y
    };


    float baseAngle = atan2(dir.y, dir.x);

    float t = 1.f - (lifetime / 0.15f);

    float swing = 90.f * DEG2RAD;
    float offset = (-swing / 2) + swing * t;

    float angle = baseAngle + offset;

    position.x = center.x + cosf(angle) * radius;
    position.y = center.y + sinf(angle) * radius;
    
    hitbox = {position.x, position.y, 10.f, 15.f};
}

void SwordAttack::draw()
{
    DrawRectangleRec(hitbox, RED);
}