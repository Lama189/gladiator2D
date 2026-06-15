#pragma once

#include "core/entity.hpp"

class Player;

class SwordAttack : public Entity
{
public:
    SwordAttack(Player& owner);

    void update(float dt) override;
    void draw() override;

    void hurt(int damage) override { }

private:
    Player& owner;
    float lifetime = 0.f;
    int damage;

    bool hit;

    float startAngle = 0.f;
    float endAngle = 0.f;
    float radius = 0.f;
};