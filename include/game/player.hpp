#pragma once

#include "raylib.h"
#include <string>

class Player
{
public:
    Player(const Vector2& pos, int screenW, int screenH);
    ~Player();

    void update(float dt);
    void draw();
    
    Camera2D getCamera() const { return camera; }

    void setServerPosition(const Vector2& pos);
    void setPlayerId(const std::string& id) { playerId = id; }
    const std::string& getPlayerId() const { return playerId; }

private:
    Camera2D camera;

    Rectangle hitbox;

    Vector2 position;
    Vector2 center;

    Vector2 previousPosition;
    Vector2 serverPosition;
    float timeSinceUpdate = 0.f;
    static constexpr float TICK_INTERVAL = 1.f / 20.f;

    std::string playerId;
};
