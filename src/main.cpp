#include <iostream>
#include "raylib.h"

int main()
{
    const int WINDOW_W = 800;
    const int WINDOW_H = 600;

    InitWindow(WINDOW_W, WINDOW_H, "Gladiator");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawText("Hi!", 400, 300, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}