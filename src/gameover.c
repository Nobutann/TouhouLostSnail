#include "screens.h"

GameScreen gameover(Texture2D background, Music menu_music)
{
    Vector2 background_pos;

    background_pos.x = (float)(GetScreenWidth() - background.width) / 2;
    background_pos.y = (float)(GetScreenHeight() - background.height) / 2;

    while (!WindowShouldClose())
    {
        UpdateMusicStream(menu_music);

        if (IsKeyPressed(KEY_Z) || IsKeyPressed(KEY_ENTER))
        {
            return MENU_SCREEN;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexture(background, background_pos.x, background_pos.y, WHITE);
        EndDrawing();
    }

    return EXIT_SCREEN;
}