#include "game/player.hpp"

Player::Player(const Vector2& pos, float vel, int screenW, int screenH)
    : speed(vel)
{
    this->position = pos;

    const float HITBOX_WIDTH = 40.f;
    const float HITBOX_HEIGHT = 80.f;
    hitbox = {position.x, position.y, HITBOX_WIDTH / 2.f, HITBOX_HEIGHT / 2.f};

    center = {hitbox.width / 2.f, hitbox.height / 2.f};

    camera.target = {position.x + center.x, position.y + center.y};
    camera.offset = {static_cast<float>(screenW / 2), static_cast<float>(screenH / 2)};
    camera.rotation = 0.f;
    camera.zoom = 1.f;

    id = 0;
}

void Player::update(float dt)
{
    input(dt);
}

void Player::draw()
{
    DrawRectanglePro(hitbox, center, 0.f, BLACK);
}

void Player::input(float dt)
{
    float currentSpeed = speed;
    if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
        currentSpeed *= 2.f;

    if (IsKeyDown(KEY_W)) position.y -= currentSpeed * dt;
    if (IsKeyDown(KEY_S)) position.y += currentSpeed * dt;
    if (IsKeyDown(KEY_A)) position.x -= currentSpeed * dt;
    if (IsKeyDown(KEY_D)) position.x += currentSpeed * dt;

    hitbox.x = position.x;
    hitbox.y = position.y;
}