#include "game/player.hpp"

Player::Player(World& w, const Vector2& pos, float vel, int screenW, int screenH)
    :  world(w), speed(vel)
{
    playerTexture = LoadTexture("assets/TestPlayer.png");
    playerTexture.width *= 2;
    playerTexture.height *= 2;

    this->position = pos;
    this->isAlive = true;

    const float HITBOX_WIDTH = 20.f;
    const float HITBOX_HEIGHT = 40.f;
    hitbox = {position.x, position.y, HITBOX_WIDTH, HITBOX_HEIGHT};

    center = {hitbox.width / 2.f, hitbox.height / 2.f};

    camera.target = {position.x + center.x, position.y + center.y};
    camera.offset = {static_cast<float>(screenW / 2), static_cast<float>(screenH / 2)};
    camera.rotation = 0.f;
    camera.zoom = 1.f;
}

void Player::update(float dt)
{
    if (networked)
    {
        timeSinceUpdate += dt;
        float alpha = timeSinceUpdate / TICK_INTERVAL;
        if (alpha > 1.f) alpha = 1.f;

        position.x = oldPosition.x + (serverPos.x - oldPosition.x) * alpha;
        position.y = oldPosition.y + (serverPos.y - oldPosition.y) * alpha;
    }

    hitbox.x = position.x;
    hitbox.y = position.y;
}

void Player::draw()
{
    DrawTexture(playerTexture, position.x - playerTexture.width / 2.f, position.y - playerTexture.height / 2.f, BLUE);
}

void Player::drawServerPlayer(const Texture2D& playerTexture, float sX, float sY, Color color)
{
    DrawTexture(playerTexture, sX - playerTexture.width / 2.f, sY - playerTexture.height / 2.f, color);
}

Vector2 Player::getCenter()
{
    return { position.x + hitbox.width / 2.f, position.y + hitbox.height / 2.f };
}

Vector2& Player::getDirection()
{
    return dir;
}

World& Player::getWorldFromPlayer()
{
    return world;
}

Texture2D& Player::getPlayerTexture()
{
    return playerTexture;
}

void Player::input(float dt)
{
    float currentSpeed = speed;
    if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
        currentSpeed *= 2.f;

    if (IsKeyDown(KEY_W)) position.y -= currentSpeed * dt;
    if (IsKeyDown(KEY_S)) position.y += currentSpeed * dt;
    if (IsKeyDown(KEY_A)) 
    {
        position.x -= currentSpeed * dt;
        dir = {1, 0};
    }
    if (IsKeyDown(KEY_D)) 
    {
        position.x += currentSpeed * dt;
        dir = {0, 1};
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    {
        testSword.attack(*this);
    }

    hitbox.x = position.x;
    hitbox.y = position.y;
}

void Player::setServerPosition(const Vector2& pos)
{
    oldPosition = position;
    serverPos = pos;
    timeSinceUpdate = 0.f;
}