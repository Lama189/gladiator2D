#pragma once

#include "core/entity.hpp"
#include <cstdint>

class Player : public Entity
{
public:
    Player(const Vector2& pos, float vel, int screenW, int screenH);
    ~Player() override = default;
    
    void update(float dt) override;
    void draw() override;

    Vector2& getCenter();
    
private:
    Camera2D camera;
    
    Vector2 center;

    float speed = 0.f;
    uint8_t id; // will need in future 
    
    void input(float dt);
};