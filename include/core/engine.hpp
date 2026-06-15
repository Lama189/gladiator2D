#pragma once

#include <memory>
#include <vector>
#include "core/sceneManager.hpp"

class Engine
{
public:
    Engine();
    ~Engine();

    void run();

private:
    SceneManager sceneManager;
    float deltaTime;

    void init();
    void mainLoop();
    void cleanup();
};