#pragma once

#include "core/scene.hpp"
#include "core/world.hpp"
#include "game/player.hpp"
#include "core/networkManager.hpp"

enum class GameMode
{
    SINGLE_PLAYER,
    MULTIPLAYER
};

class GameScene : public Scene
{
public:
    GameScene(GameMode mode);

    void init(SceneManager& sManager) override;
    void cleanup() override;
    
    void update(float dt) override;
    void draw() override;


private:
    GameMode mode;

    World world;
    Player* localPlayer = nullptr;
    NetworkManager network;
};