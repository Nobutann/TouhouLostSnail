#include "screens.h"
#include "raylib.h"

GameScreen menu()
{
    const char options[4][10] = 
    {
        "Start",
        "Credits",
        "Exit"
    };
    
    Texture2D background = LoadTexture("assets/sprites/menu/menu.png");
    int selected = 0;
    while (!WindowShouldClose)
    {
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
            selected = 3;
        }
        if (selected > 3)
        {
            selected = 0;
        }

        if (IsKeyPressed(KEY_Z) || IsKeyPressed(KEY_ENTER))
        {
            if (selected == 0)
            {}
        }
    }

    int selected;


}