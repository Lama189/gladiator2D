#include "game/scenes/gameScene.hpp"
#include "core/assetManager.hpp"
#include "game/dummy.hpp"

static constexpr int WINDOW_W = 800;
static constexpr int WINDOW_H = 600;

GameScene::GameScene(GameMode mode) : mode(mode) { }

void GameScene::init(SceneManager& sManager, AssetManager& assets)
{
    assetManager = &assets;
    manager = &sManager;

    Vector2 playerPos = {400.f, 300.f};
    auto player = std::make_unique<Player>(assetManager->getTexture("TestPlayerAnim"), world, playerPos, 60.f, WINDOW_W, WINDOW_H);

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
    {
        const auto& state = network.getLastState();
        network.update(dt, *localPlayer);
        
        for (auto& [id, ps] : state.players)
        {
            if (id == network.getPlayerId())
                continue;

            Player* p = world.getPlayerByID(id);

            if (!p)
            {
                auto newPlayer = std::make_unique<Player>(assetManager->getTexture("TestPlayerAnim"), world, Vector2{ps.x, ps.y}, 60.f, WINDOW_W, WINDOW_H);

                newPlayer->setNetworked(true);

                Player* raw = newPlayer.get();

                world.registerPlayer(id, raw);
                world.addEntity(std::move(newPlayer));
                    
                p = raw;
            }

            p->setServerPosition({ps.x, ps.y});
        }
    }
        
    world.update(dt);

    if (mode == GameMode::SINGLE_PLAYER)
        localPlayer->input(dt);
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
            if (id == network.getPlayerId()) 
                continue;

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