#pragma once

#include "raylib.h"

class Entity
{
public:
    virtual ~Entity() = default;

    virtual void update(float dt) = 0;
    virtual void draw() = 0;

    Rectangle getHitbox() const
    {
        return hitbox;
    }
    
    bool alive() const
    {
        return isAlive;
    }

protected:
    Vector2 position{0, 0};

    Rectangle hitbox{};

    bool isAlive = false;
};