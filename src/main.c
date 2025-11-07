#include "raylib.h"
#include "player.h"
#include "screens.h"
#include "bullets.h"

#define BASE_SPEED 550.0f

int main(void)
{
    InitWindow(1280, 800, "Touhou: Lost Snail");
    InitAudioDevice();
    SetTargetFPS(60);

    GameScreen current_screen = MENU_SCREEN;

    Sound shoot_sound = LoadSound("assets/sounds/player_sounds/playerattack.wav");
    SetSoundVolume(shoot_sound, 0.02f);
    Music menu_music = LoadMusicStream("assets/sounds/musics/menumusic/menumusic.wav");

    while (current_screen != EXIT_SCREEN && !WindowShouldClose())
    {
        if (current_screen == MENU_SCREEN)
        {
            PlayMusicStream(menu_music);
            current_screen = menu(menu_music);
        }
        if (current_screen == GAME_SCREEN)
        {
            StopMusicStream(menu_music);
            UnloadMusicStream(menu_music);
            Player player;
            Bullet bullets[MAX_BULLETS];
            Vector2 start_pos = {400, 300};
            Texture2D bullet_sprite = LoadTexture("assets/sprites/bullets/playerbullet.png");
            InitPlayer(&player, start_pos, BASE_SPEED);
            InitBullet(bullets, bullet_sprite);

            while (!WindowShouldClose())
            {
                float dt = GetFrameTime();
                
                UpdatePlayer(&player, dt, bullets, shoot_sound);
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

    UnloadSound(shoot_sound);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}