#include "core/sceneManager.hpp"

void SceneManager::change(std::unique_ptr<Scene> scene, AssetManager& assets)
{
    currentScene = std::move(scene);
    currentScene->init(*this, assets);
}

void SceneManager::update(float dt)
{
    currentScene->update(dt);
}

void SceneManager::draw()
{
    currentScene->draw();
}

void SceneManager::cleanup()
{
    currentScene->cleanup();
}