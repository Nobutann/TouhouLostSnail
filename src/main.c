#include "raylib.h"
#include "player.h"
#include "screens.h"
#include "bullets.h"

#define BASE_SPEED 550.0f

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
            Bullet bullets[MAX_BULLETS];
            Vector2 start_pos = {400, 300};
            Texture2D bullet_sprite = LoadTexture("assets/sprites/bullets/playerbullet.png");
            InitPlayer(&player, start_pos, BASE_SPEED);
            InitBullet(bullets, bullet_sprite);

            while (!WindowShouldClose())
            {
                float dt = GetFrameTime();
                
                UpdatePlayer(&player, dt, bullets);
                UpdateBullets(bullets, dt);

                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawPlayer(&player);
                DrawBullets(bullets);
                EndDrawing();
            }

            UnloadPlayer(&player);
            UnloadTexture(bullet_sprite);
        }
    }

    CloseWindow();

    return 0;
}