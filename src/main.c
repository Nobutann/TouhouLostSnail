#include "raylib.h"
#include "player.h"
#include "screens.h"

int main(void)
{
    InitWindow(1280, 800, "Touhou: Lost Snail");
    SetTargetFPS(60);

    GameScreen current_screen = MENU_SCREEN;

    while (current_screen != EXIT_SCREEN && !WindowShouldClose())
    {
        if (current_screen == MENU_SCREEN)
        {
            current_screen = menu();
        }
        if (current_screen == GAME_SCREEN)
        {
            Player player;
            Vector2 start_pos = {400, 300};
            InitPlayer(&player, start_pos, 350.0f);

            while (!WindowShouldClose())
            {
                float dt = GetFrameTime();
                
                UpdatePlayer(&player, dt);

                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawPlayer(&player);
                EndDrawing();
            }

            UnloadPlayer(&player);
        }
    }

    CloseWindow();

    return 0;
}