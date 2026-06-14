#pragma once

#include "raylib.h"

class Player
{
public:
    Player(const Vector2& pos, float vel, int screenW, int screenH);
    ~Player();

    void update(float dt);
    void draw();
    
private:
    Camera2D camera;

    Rectangle hitbox;
    
    Vector2 position;
    Vector2 center;

    float speed = 0.f;
    
    void input(float dt);
};