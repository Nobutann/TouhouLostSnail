#include "raylib.h"
#include "player.h"

int main(void)
{
    InitWindow(800, 600, "Touhou: Lost Snail");
    SetTargetFPS(60);

    Player player;
    Vector2 start_pos = {400, 300};
    InitPlayer(&player, start_pos, 200.0f);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        
        UpdatePlayer(&player, dt);

        BeginDrawing();
        DrawPlayer(&player);
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    UnloadPlayer(&player);
    CloseWindow();

    return 0;
}