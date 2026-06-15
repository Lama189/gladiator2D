#pragma once

#include "core/scene.hpp"
#include <memory>

class SceneManager
{
public:
    void change(std::unique_ptr<Scene> scene);
    
    void update(float dt);
    void draw();

    void cleanup();

private:
    std::unique_ptr<Scene> currentScene;
};