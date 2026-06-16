#pragma once

#include "core/entity.hpp"
#include "game/weapons/sword/sword.hpp"
#include <cstdint>
#include <string>

class World;

class Player : public Entity
{
public:
    Player(World& w, const Vector2& pos, float vel, int screenW, int screenH);
    ~Player() override { UnloadTexture(playerTexture); };
    
    void update(float dt) override;
    void draw() override;

    static void drawServerPlayer(const Texture2D& playerTexture, float sX, float sY, Color color);

    void input(float dt);
    
    void hurt(int damage) override { }

    Camera2D getCamera() { return camera; }

    Vector2 getCenter();
    Vector2& getDirection();
    Texture2D& getPlayerTexture();

    World& getWorldFromPlayer();

    void setServerPosition(const Vector2& pos);
    void setPlayerId(const std::string& pId) { id = pId; }
    void setNetworked(bool value) { networked = value; }
    const std::string& getPlayerId() const { return id; }
    
private:
    Texture playerTexture;

    World& world; // maybe bad idea
    Sword testSword;

    Camera2D camera;
    
    Vector2 center{0, 0};
    Vector2 dir{0, 0};

    float speed = 0.f;

    float timeSinceUpdate = 0.f;
    static constexpr float TICK_INTERVAL = 1.f / 20.f;

    std::string id; // will need in future 
    bool networked;
};