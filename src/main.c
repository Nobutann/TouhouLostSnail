#include "raylib.h"
#include "player.h"
#include "screens.h"
#include "bullets.h"
#include "boss.h"
int main(void)
{
    InitWindow(1280, 800, "Touhou: Lost Snail");
    InitAudioDevice();
    SetTargetFPS(60);

    GameScreen current_screen = MENU_SCREEN;

    Sound shoot_sound = LoadSound("assets/sounds/player_sounds/playerattack.wav");
    SetSoundVolume(shoot_sound, 0.02f);
    Music menu_music = LoadMusicStream("assets/sounds/musics/menumusic/menumusic.mp3");

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
            BOSS boss;
            Bullet bullets[MAX_BULLETS];
            Vector2 start_pos = {400, 500};
            Vector2 start_boss_pos = {300, 200};
            Texture2D bullet_sprite = LoadTexture("assets/sprites/bullets/playerbullet.png");
            InitPlayer(&player, start_pos, BASE_SPEED);
            InitBoss(&boss, start_boss_pos, BASE_SPEED);
            InitBullet(bullets, bullet_sprite);
            Animation map;
            LoadMapSprites(&map);

            while (!WindowShouldClose())
            {
                float dt = GetFrameTime();
                UpdateBoss(&boss, dt, bullets, shoot_sound);
                UpdatePlayer(&player, dt, bullets, shoot_sound);
                UpdateBullets(bullets, dt);

                BeginDrawing();
                ClearBackground(RAYWHITE);
                Vector2 map_pos = {0, 0};
                DrawAnimationFrame(&map, map_pos, 1.0f, WHITE);
                UpdateAnimation(&map, dt);
                DrawPlayer(&player);
                DrawBoss(&boss);
                DrawBullets(bullets);
                EndDrawing();
            }

            UnloadPlayer(&player);
            UnloadBoss(&boss);
            UnloadTexture(bullet_sprite);
            UnloadMapSprites(&map);
        }
    }

    UnloadSound(shoot_sound);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}