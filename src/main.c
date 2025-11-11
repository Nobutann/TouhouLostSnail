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
            Bullet bullets[MAX_BULLETS];
            BombProjectile active_bombs[MAX_ACTIVE_BOMBS];
            
            Boss flandre;
            EnemyBullet enemy_bullets[MAX_ENEMY_BULLETS];

            for (int i = 0; i < MAX_ACTIVE_BOMBS; i += 1)
            {
                active_bombs[i].active = false;
            }
            Texture2D bullet_sprite = LoadTexture("assets/sprites/bullets/playerbullet.png");
            Vector2 start_pos = {400, 715};
            InitPlayer(&player, start_pos, BASE_SPEED);

            InitBoss(&flandre, (Vector2){400, 100});
            InitBullet(bullets, bullet_sprite);
            InitEnemyBullets(enemy_bullets);
            Texture2D bullet_red = LoadTexture("assets/sprites/bullets/bullet_small_red.png");
            Texture2D bullet_pink = LoadTexture("assets/sprites/bullets/bullet_small_pink.png");
            Texture2D bullet_orange = LoadTexture("assets/sprites/bullets/bullet_small_orange.png");
            Texture2D bullet_yellow_glow = LoadTexture("assets/sprites/bullets/bullet_medium_yellow_glow.png");
            Texture2D bullet_blue_outline = LoadTexture("assets/sprites/bullets/bullet_outline_blue.png");

            BossAssets boss_assets = 
            {
                .bullet_red = bullet_red,
                .bullet_pink = bullet_pink,
                .bullet_orange = bullet_orange,
                .bullet_yellow_glow = bullet_yellow_glow,
                .bullet_blue_outline = bullet_blue_outline
            };

            Animation map;
            LoadMapSprites(&map);

            while (!WindowShouldClose())
            {
                float dt = GetFrameTime();
                
                UpdatePlayer(&player, dt, bullets, shoot_sound, active_bombs);
                UpdateBoss(&flandre, dt, enemy_bullets, player.position, &boss_assets);
                UpdateBullets(bullets, dt);
                UpdateEnemyBullets(enemy_bullets, dt);
                UpdateBombProjectiles(active_bombs, dt);
                BeginDrawing();
                ClearBackground(RAYWHITE);
                Vector2 map_pos = {0, 0};
                DrawAnimationFrame(&map, map_pos, 1.0f, WHITE);
                UpdateAnimation(&map, dt);
                DrawPlayer(&player);
                DrawBoss(&flandre);
                DrawEnemyBullets(enemy_bullets);
                DrawBullets(bullets);
                DrawBombProjectiles(active_bombs);
                DrawHealths(&player);
                DrawBombs(&player);
                EndDrawing();
            }

            UnloadPlayer(&player);
            UnloadBoss(&flandre);
            UnloadTexture(bullet_sprite);
            UnloadMapSprites(&map);
            UnloadTexture(bullet_red);
            UnloadTexture(bullet_pink);
            UnloadTexture(bullet_orange);
            UnloadTexture(bullet_yellow_glow);
            UnloadTexture(bullet_blue_outline);
        }
    }

    UnloadSound(shoot_sound);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}