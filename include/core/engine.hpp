#pragma once
#include <memory>
#include <string>
#include "core/protocol.hpp"

class Player;
class UDPClient;

class Engine
{
public:
    Engine();
    ~Engine();
    void run();

private:
    std::unique_ptr<Player> player;
    std::unique_ptr<UDPClient> client;
    std::string playerId;
    bool connected = false;
    float deltaTime = 0.f;
    Protocol::ServerState lastState;

    void init();
    void mainLoop();
    void cleanup();
};