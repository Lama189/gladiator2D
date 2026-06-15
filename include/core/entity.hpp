#pragma once

#include "raylib.h"

class Entity
{
public:
    virtual ~Entity() {};

    virtual void update(float dt) = 0;
    virtual void draw() = 0;
    virtual void hurt(int damage) = 0;

    Rectangle getHitbox() const
    {
        return hitbox;
    }

    Vector2 getPosition() const
    {
        return position;
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