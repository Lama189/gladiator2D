#pragma once

#include "core/entity.hpp"

class Dummy : public Entity
{
public:
    Dummy(Vector2 pos);
    ~Dummy();

    void update(float dt) override;
    void draw() override;

    void hurt(int damage) override;

private:
    Texture2D texture;
    int health;
};