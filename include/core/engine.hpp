#pragma once

#include <memory>
#include <vector>
#include "core/world.hpp"
#include "core/client/protocol.hpp"

class Player;
class Entity;
class UDPClient;

class Engine
{
public:
    Engine();
    ~Engine();

    void run();

private:
    World world;
    std::unique_ptr<UDPClient> client;
    std::unique_ptr<Player> player;

    std::string playerId;
    bool connected = false;

    float deltaTime;

    Protocol::ServerState lastState;

    void init();
    void mainLoop();
    void cleanup();
};