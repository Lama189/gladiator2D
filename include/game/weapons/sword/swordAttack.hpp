#pragma once

#include "core/entity.hpp"

class SwordAttack : public Entity
{
public:
    SwordAttack(Vector2 pos, float width, float height);

    void update(float dt) override;
    void draw() override;

private:
    float lifetime;
};