#pragma once

#include "core/scene.hpp"
#include "ui/button.hpp"

class MenuScene : public Scene
{
public:
    void init(SceneManager& sManager, AssetManager& assets) override;
    void cleanup() override { }

    void update(float dt) override;
    void draw() override;

private:
    UI::Button singlePlayerButton;
    UI::Button multiPlayerButton;
};