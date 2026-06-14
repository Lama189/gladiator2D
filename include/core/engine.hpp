#pragma once

#include <memory>
#include <vector>
#include "core/world.hpp"

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

    float deltaTime;

    void init();
    void mainLoop();
    void cleanup();
};