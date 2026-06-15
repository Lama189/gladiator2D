#include "game/scenes/gameScene.hpp"

#include "game/dummy.hpp"

static constexpr int WINDOW_W = 800;
static constexpr int WINDOW_H = 600;

GameScene::GameScene(GameMode mode) : mode(mode) { }

void GameScene::init(SceneManager& sManager)
{
    manager = &sManager;

    Vector2 playerPos = {400.f, 300.f};
    auto player = std::make_unique<Player>(world, playerPos, 60.f, WINDOW_W, WINDOW_H);

    localPlayer = player.get();
    localPlayer->setNetworked(false);

    world.addEntity(std::move(player));
    world.addEntity(std::make_unique<Dummy>(Vector2{500.f, 300.f}));

    if (mode == GameMode::MULTIPLAYER)
    {
        network.init();
        localPlayer->setNetworked(true);
    }
}

void GameScene::update(float dt)
{
    if (mode == GameMode::MULTIPLAYER)
        network.update(dt, *localPlayer);
        
    localPlayer->update(dt);
        
    if (mode == GameMode::SINGLE_PLAYER)
        localPlayer->input(dt);
        
    world.update(dt);
}

void GameScene::draw()
{
    const char* fpsText = 0;
    fpsText = TextFormat("FPS: (%i)", GetFPS());
    DrawText(fpsText, 0, 0, 20, GREEN);

    localPlayer->draw();

    if (mode == GameMode::MULTIPLAYER)
    {
        const auto& state = network.getLastState();
        const auto selfIt = state.players.find(network.getPlayerId());
        if (selfIt != state.players.end())
        {
            DrawText(TextFormat("MY POS: %.1f %.1f",
                                selfIt->second.x,
                                selfIt->second.y), 0, 20, 20, BLUE);
        }

        for (auto& [id, ps] : state.players)
        {
            if (id == network.getPlayerId()) continue;
            DrawRectangle(
                static_cast<int>(ps.x) - 10,
                static_cast<int>(ps.y) - 20,
                20, 40,
                RED
            );
            DrawText(TextFormat("OTHER POS: %.1f %.1f", ps.x, ps.y), 0, 40, 20, RED);
        }   
    }

    world.render();
}

void GameScene::cleanup()
{
    localPlayer = nullptr;
    
    if (mode == GameMode::MULTIPLAYER)
        network.cleanup();

    world.cleanup();
}