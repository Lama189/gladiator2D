#include "raylib.h"
#include "core/engine.hpp"
#include "game/player.hpp"
#include "game/dummy.hpp"
#include "core/client/udpclient.hpp"

static constexpr int WINDOW_W = 800;
static constexpr int WINDOW_H = 600;
static constexpr const char* SERVER_HOST = "127.0.0.1";
static constexpr int SERVER_PORT = 7777;

Engine::Engine() = default; 

Engine::~Engine() = default;

void Engine::run()
{
    init();
    mainLoop();
    cleanup();
}

void Engine::init()
{
    InitWindow(WINDOW_W, WINDOW_H, "Gladiator");

    Vector2 playerPos = {400.f, 300.f};
    player = std::make_unique<Player>(world, playerPos, 60.f, WINDOW_W, WINDOW_H);
    world.addEntity(std::make_unique<Dummy>(Vector2{500.f, 300.f}));

    network.init();
}

void Engine::mainLoop()
{
    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();

        network.update(deltaTime, *player);

        player->update(deltaTime);
        world.update(deltaTime);    

        BeginDrawing();
            ClearBackground(RAYWHITE);
        
            BeginMode2D(player->getCamera());
            
            const char* fpsText = 0;
            fpsText = TextFormat("FPS: (%i)", GetFPS());

            player->draw();

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

            world.render();

            DrawText(fpsText, 0, 0, 20, GREEN);

            EndMode2D();
        EndDrawing();
    }
}

void Engine::cleanup()
{
    network.cleanup();

    world.cleanup();
    CloseWindow();
}