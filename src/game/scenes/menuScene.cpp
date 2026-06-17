#include "game/scenes/menuScene.hpp"
#include "core/sceneManager.hpp"
#include "game/scenes/gameScene.hpp"
#include "raylib.h"

void MenuScene::init(SceneManager& sManager, AssetManager& assets) 
{ 
    assetManager = &assets;
    manager = &sManager; 

    singlePlayerButton = { {300, 200, 200, 50}, "Single player" };
    multiPlayerButton  = { {300, 300, 200, 50}, "Multiplayer" };
}

void MenuScene::update(float dt)
{
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionPointRec(mouse, singlePlayerButton.rect))
        {
            manager->change(std::make_unique<GameScene>(GameMode::SINGLE_PLAYER), *assetManager);
        }

        if (CheckCollisionPointRec(mouse, multiPlayerButton.rect))
        {
            manager->change(std::make_unique<GameScene>(GameMode::MULTIPLAYER), *assetManager);
        }
    }
}

void MenuScene::draw()
{
    Vector2 mouse = GetMousePosition();

    UI::drawButton(singlePlayerButton, mouse);
    UI::drawButton(multiPlayerButton, mouse);
}