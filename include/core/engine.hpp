#pragma once

#include <memory>

class Player;

class Engine
{
public:
    Engine();
    ~Engine();

    void run();

private:
    std::unique_ptr<Player> player;

    float deltaTime;

    void init();
    void mainLoop();
    void cleanup();
};