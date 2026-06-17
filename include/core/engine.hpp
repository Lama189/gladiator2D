#pragma once

#include <memory>
#include <vector>
#include "core/sceneManager.hpp"
#include "core/assetManager.hpp"


class Engine
{
public:
    Engine();
    ~Engine();

    void run();

private:
    SceneManager sceneManager;
    AssetManager assetManager;
    float deltaTime;

    void init();
    void mainLoop();
    void cleanup();
};