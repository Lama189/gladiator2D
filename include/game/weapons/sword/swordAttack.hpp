#pragma once

#include "core/entity.hpp"

class Player;

class SwordAttack : public Entity
{
public:
    SwordAttack(Player& owner);

    void update(float dt) override;
    void draw() override;

private:
    Player& owner;
    float lifetime = 0.f;

    float startAngle = 0.f;
    float endAngle = 0.f;
    float radius = 0.f;
};