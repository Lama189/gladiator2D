#include "game/player.hpp"

Player::Player(Texture2D& texture, World& w, const Vector2& pos, float vel, int screenW, int screenH)
    :  world(w), speed(vel)
{
    playerTexture = &texture;

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

        velocity.x = position.x - oldPosition.x;
        velocity.y = position.y - oldPosition.y;

        if ((serverPos.x - oldPosition.x) > 0)
            isFacingLeft = false;
        else if ((serverPos.x - oldPosition.x) < 0)
            isFacingLeft = true;
    }

    if (velocity.x != 0 || velocity.y != 0)
        currentState = AnimationState::Run;
    else
        currentState = AnimationState::Idle;

    animTimer += dt;

    const float FRAME_TIME = 0.1f;

    if (animTimer >= FRAME_TIME)
    {
        animTimer = 0.f;

        currentFrame++;

        if (currentState == AnimationState::Run)
        {
            if (currentFrame > 3)
                currentFrame = 0;
        }
        else
        {
            if (currentFrame < 4)
                currentFrame = 4;

            if (currentFrame > 7)
                currentFrame = 4;
        }
    }

    hitbox.x = position.x;
    hitbox.y = position.y;
}

void Player::draw()
{
    const int TEXTURE_WIDTH = 36;
    const int TEXTURE_HEIGHT = 46;

    Rectangle src = { static_cast<float>(currentFrame * TEXTURE_WIDTH), 0, static_cast<float>(TEXTURE_WIDTH), static_cast<float>(TEXTURE_HEIGHT) };

    if (isFacingLeft)
    {
        src.x += TEXTURE_WIDTH;
        src.width = -TEXTURE_WIDTH;
    }

    Rectangle dst = { position.x, position.y, static_cast<float>(TEXTURE_WIDTH), static_cast<float>(TEXTURE_HEIGHT) };

    Vector2 origin = { static_cast<float>(TEXTURE_WIDTH) / 2.0f, static_cast<float>(TEXTURE_HEIGHT) / 2.0f };

    DrawTexturePro(*playerTexture, src, dst, origin, 0.0f, BLUE);
}

void Player::drawServerPlayer(Texture2D& playerTexture, float sX, float sY, Color color)
{
    DrawTexture(playerTexture, sX - playerTexture.width / 2.f, sY - playerTexture.height / 2.f, color);
}

Vector2 Player::getCenter()
{
    return { position.x + hitbox.width / 2.f, position.y + hitbox.height / 2.f };
}

World& Player::getWorldFromPlayer()
{
    return world;
}

void Player::input(float dt)
{
    velocity = {0, 0};

    float currentSpeed = speed;
    if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
        currentSpeed *= 2.f;

    if (IsKeyDown(KEY_W)) velocity.y = -currentSpeed;
    if (IsKeyDown(KEY_S)) velocity.y = currentSpeed;
    if (IsKeyDown(KEY_A)) 
    {
        velocity.x = -currentSpeed;
        isFacingLeft = true;
    }
    if (IsKeyDown(KEY_D)) 
    {
        velocity.x = currentSpeed;
        isFacingLeft = false;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
    {
        testSword.attack(*this);
    }

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    hitbox.x = position.x;
    hitbox.y = position.y;
}

void Player::setServerPosition(const Vector2& pos)
{
    oldPosition = position;
    serverPos = pos;
    timeSinceUpdate = 0.f;
}