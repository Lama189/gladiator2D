#include "game/player.hpp"

Player::Player(const Vector2& pos, int screenW, int screenH): position(pos)
{
    const float HITBOX_WIDTH = 40.f;
    const float HITBOX_HEIGHT = 80.f;
    hitbox = {position.x, position.y, HITBOX_WIDTH / 2.f, HITBOX_HEIGHT / 2.f};
    center = {hitbox.width / 2.f, hitbox.height / 2.f};
    camera.target = {position.x + center.x, position.y + center.y};
    camera.offset = {static_cast<float>(screenW / 2), static_cast<float>(screenH / 2)};
    camera.rotation = 0.f;
    camera.zoom = 1.f;
    previousPosition = pos;
    serverPosition = pos;
}

Player::~Player()
{

}

void Player::update(float dt)
{
    timeSinceUpdate += dt;
    float alpha = timeSinceUpdate / TICK_INTERVAL;
    if (alpha > 1.f) alpha = 1.f;

    position.x = previousPosition.x + (serverPosition.x - previousPosition.x) * alpha;
    position.y = previousPosition.y + (serverPosition.y - previousPosition.y) * alpha;

    hitbox.x = position.x;
    hitbox.y = position.y;
    // camera.target = {position.x + center.x, position.y + center.y};
}

void Player::draw()
{
    DrawRectanglePro(hitbox, center, 0.f, BLACK);
}

void Player::setServerPosition(const Vector2& pos)
{
    previousPosition = position;
    serverPosition = pos;
    timeSinceUpdate = 0.f;
}