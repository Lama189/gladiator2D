#include "ui/button.hpp"

namespace UI
{
    void drawButton(const Button& b, Vector2& mousePos)
    {
        bool hover = CheckCollisionPointRec(mousePos, b.rect);

        DrawRectangleRec(b.rect, hover ? GRAY : DARKGRAY);
        DrawRectangleLinesEx(b.rect, 2, BLACK);

        int textWidth = MeasureText(b.text.c_str(), 20);
        DrawText(b.text.c_str(),
            b.rect.x + (b.rect.width - textWidth) / 2,
            b.rect.y + 15,
            20,
            WHITE);
    }
}