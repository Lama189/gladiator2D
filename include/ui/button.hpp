#pragma once

#include "raylib.h"
#include <string>

namespace UI
{
    // here will be just a simple struct
    struct Button
    {
        Rectangle rect;
        std::string text;
    };

    void drawButton(const Button& b, Vector2& mousePos);
}