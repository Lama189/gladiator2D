#include "raylib.h"
#include "core/engine.hpp"
#include "game/player.hpp"
#include "game/dummy.hpp"
#include "core/client/udpclient.hpp"
#include "game/scenes/menuScene.hpp"
#include "game/scenes/gameScene.hpp"

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

    sceneManager.change(std::make_unique<MenuScene>());
}

void Engine::mainLoop()
{
    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();
        sceneManager.update(deltaTime);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            sceneManager.draw();
            
        EndDrawing();
    }
}

void Engine::cleanup()
{
    sceneManager.cleanup();
    CloseWindow();
}