#pragma once

#include "core/entity.hpp"
#include "game/weapons/sword/sword.hpp"
#include <cstdint>

class World;

class Player : public Entity
{
public:
    Player(World& w, const Vector2& pos, float vel, int screenW, int screenH);
    ~Player() override = default;
    
    void update(float dt) override;
    void draw() override;

    void hurt(int damage) override;

    Vector2 getCenter();
    Vector2& getDirection();

    World& getWorldFromPlayer();
    
private:
    World& world; // maybe bad idea
    Sword testSword;

    Camera2D camera;
    
    Vector2 center{0, 0};
    Vector2 dir{0, 0};

    float speed = 0.f;
    uint8_t id = 0; // will need in future 
    
    void input(float dt);
};