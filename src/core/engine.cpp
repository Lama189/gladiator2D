#include "raylib.h"
#include "core/engine.hpp"
#include "core/client.hpp"
#include "core/protocol.hpp"
#include "game/player.hpp"

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
    player = std::make_unique<Player>(playerPos, WINDOW_W, WINDOW_H);
    client = std::make_unique<UDPClient>();
    if (client->connect(SERVER_HOST, SERVER_PORT))
    {
        auto connectPacket = Protocol::encodeConnect();
        client->send(connectPacket);
    }
}

void Engine::mainLoop()
{
    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();

        auto inputPacket = Protocol::encodeInput(
            IsKeyDown(KEY_W),
            IsKeyDown(KEY_S),
            IsKeyDown(KEY_A),
            IsKeyDown(KEY_D),
            IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)
        );
        client->send(inputPacket);

        std::vector<uint8_t> recvBuf;
        std::string lastPlayerId;

        while (client->receive(recvBuf))
        {
            if (Protocol::decodePacket(recvBuf.data(), recvBuf.size(), lastState, lastPlayerId))
            {
                if (!connected && !lastPlayerId.empty())
                {
                    playerId = lastPlayerId;
                    player->setPlayerId(playerId);
                    connected = true;
                }
            }
        }

        if (connected)
        {
            auto it = lastState.players.find(playerId);
            if (it != lastState.players.end())
            {
                player->setServerPosition({it->second.x, it->second.y});
            }
        }

        player->update(deltaTime);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(player->getCamera());

        player->draw();

        for (auto& [id, ps] : lastState.players)
        {
            if (id == playerId) continue;
            DrawRectangle(
                static_cast<int>(ps.x),
                static_cast<int>(ps.y),
                20, 40,
                RED
            );
        }

        EndMode2D();

        const char* fpsText = TextFormat("FPS: (%i)", GetFPS());
        DrawText(fpsText, 0, 0, 20, GREEN);

        EndDrawing();
    }
}

void Engine::cleanup()
{
    client->disconnect();
    CloseWindow();
}