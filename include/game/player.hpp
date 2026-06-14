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

    Vector2& getCenter();
    World& getWorldFromPlayer();
    
private:
    World& world; // maybe bad idea

    Camera2D camera;
    
    Vector2 center;

    float speed = 0.f;
    uint8_t id; // will need in future 
    
    void input(float dt);
};