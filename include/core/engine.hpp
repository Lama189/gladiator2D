#pragma once

#include <memory>
#include <vector>
#include "core/world.hpp"
#include "core/networkManager.hpp"

class Player;
class Entity;

class Engine
{
public:
    Engine();
    ~Engine();

    void run();

private:
    World world;
    NetworkManager network;
    std::unique_ptr<Player> player;


    float deltaTime;

    void init();
    void mainLoop();
    void cleanup();
};