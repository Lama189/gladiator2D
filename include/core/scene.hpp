#pragma once

class SceneManager;
class AssetManager;

class Scene
{
public:
    virtual ~Scene() = default;

    virtual void init(SceneManager& sManager, AssetManager& assets) = 0;
    virtual void cleanup() = 0;

    virtual void update(float dt) = 0;
    virtual void draw() = 0;

protected:
    SceneManager* manager = nullptr;
    AssetManager* assetManager = nullptr;
};