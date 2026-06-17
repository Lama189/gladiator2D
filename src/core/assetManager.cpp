#include "core/assetManager.hpp"
#include <iostream>
#include <filesystem>

void AssetManager::init(const std::string& path)
{
    loadAll(path);
}

void AssetManager::cleanup()
{
    for (auto& [name, texture] : assets)
        UnloadTexture(texture);

    assets.clear();
}

void AssetManager::loadAll(const std::string& path)
{
    try
    {
        for (const auto& entry: std::filesystem::recursive_directory_iterator(path))
        {
            if (entry.is_regular_file())
            {
                std::string ext = entry.path().extension().string();

                if (ext == ".png")
                {
                    std::string name = entry.path().stem().string();
                    std::string path = entry.path().string();

                    loadTexture(path, name);
                }
            }
        }

        std::cout << "Total textures loaded: " << assets.size() << std::endl;
    }
    catch(const std::filesystem::filesystem_error& e)
    {
        std::cerr << "File system err: " << e.what() << '\n';
    }
    
}

Texture2D& AssetManager::getTexture(const std::string& name)
{
    if (assets.find(name) == assets.end())
        std::cerr << "Cannot find texture! " << name << "\n";

    return assets[name];
}

Texture2D AssetManager::loadTexture(const std::string& path, const std::string& name)
{
    if (assets.find(name) != assets.end())
        return assets[name];

    auto texture = LoadTexture(path.c_str());

    assets[name] = std::move(texture);
    return texture;
}