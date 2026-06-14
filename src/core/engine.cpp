#include "raylib.h"
#include "core/engine.hpp"
#include "game/player.hpp"

static constexpr int WINDOW_W = 800;
static constexpr int WINDOW_H = 600;

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
    world.addEntity(std::make_unique<Player>(world, playerPos, 60.f, WINDOW_W, WINDOW_H));
}

void Engine::mainLoop()
{
    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();

        world.update(deltaTime);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            const char* fpsText = 0;
            fpsText = TextFormat("FPS: (%i)", GetFPS());

            for (auto& entity : world.getEntities())
                entity->draw();

            DrawText(fpsText, 0, 0, 20, GREEN);
        EndDrawing();
    }
}

void Engine::cleanup()
{
    CloseWindow();
}