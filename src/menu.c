#include "screens.h"
#include "raylib.h"

GameScreen menu(Music menu_music)
{
    const char options[3][8] = 
    {
        "Start",
        "Credits",
        "Exit"
    };
    
    Texture2D background = LoadTexture("assets/sprites/menu/menu.png");
    Vector2 background_pos;

    background_pos.x = (float)(GetScreenWidth() - background.width) / 2;
    background_pos.y = (float)(GetScreenHeight() - background.height) / 2;

    int selected = 0;

    int baseY = GetScreenHeight() / 2 + 100;
    int baseX = GetScreenWidth() / 2 - 60;
    int spacing = 80;
    
    while (!WindowShouldClose())
    {
        UpdateMusicStream(menu_music);
        
        if (IsKeyPressed(KEY_UP))
        {
            selected = selected - 1;
        }
        if (IsKeyPressed(KEY_DOWN))
        {
            selected = selected + 1;
        }
        if (selected < 0)
        {
            selected = 2;
        }
        if (selected > 2)
        {
            selected = 0;
        }

        if (IsKeyPressed(KEY_Z) || IsKeyPressed(KEY_ENTER))
        {
            if (selected == 0)
            {
                return GAME_SCREEN;
            }
            if (selected == 1)
            {
                return CREDITS_SCREEN;
            }
            if (selected == 2)
            {
                return EXIT_SCREEN;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexture(background, background_pos.x, background_pos.y, WHITE);

        for (int i = 0; i < 3; i++)
        {
            const char *text = options[i];
            int fontSize = 50;
            int posY = baseY + i * spacing;
            
            if (i == selected)
            {
                DrawText(text, baseX + 2, posY + 2, fontSize + 2, BLACK);
                DrawText(text, baseX, posY, fontSize, RED);
            }
            else
            {
                DrawText(text, baseX, posY, fontSize, WHITE);
            }
        }

        EndDrawing();
    }

    UnloadTexture(background);
    
    return EXIT_SCREEN;
}