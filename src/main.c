#include "raylib.h"
#include "player.h"

int main(void)
{
    InitWindow(800, 600, "Touhou: Lost Snail");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 20, BLACK);

        Player player;
        initPlayer(&player);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}