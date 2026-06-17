#pragma once

#include <string>
#include <unordered_map>

#include "raylib.h"

class AssetManager
{
public:
    void init(const std::string& path);
    void cleanup();

    void loadAll(const std::string& path);

    Texture2D& getTexture(const std::string& name);

private:
    std::unordered_map<std::string, Texture2D> assets;

    Texture2D loadTexture(const std::string& path, const std::string& name);
};