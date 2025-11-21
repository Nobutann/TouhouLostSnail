#include "raylib.h"
#include "player.h"
#include "screens.h"
#include "bullets.h"
#include "boss.h"
#include <stdio.h> 

#define HIGHSCORE_FILE "highscore.txt"

int LoadHighScore()
{
    int highScore = 0;
    FILE *file = fopen(HIGHSCORE_FILE, "r");
    if (file == NULL) return 0;
    fscanf(file, "%d", &highScore);
    fclose(file);
    return highScore;
}

void SaveHighScore(int score)
{
    FILE *file = fopen(HIGHSCORE_FILE, "w");
    if (file == NULL) { printf("ERRO: Salvar High Score\n"); return; }
    fprintf(file, "%d", score);
    fclose(file);
}

int main(void)
{
    InitWindow(1280, 800, "Touhou: Lost Snail");
    SetExitKey(0);
    InitAudioDevice();
    SetTargetFPS(60);

    GameScreen current_screen = MENU_SCREEN;

    Sound shoot_sound = LoadSound("assets/sounds/player_sounds/playerattack.wav");
    SetSoundVolume(shoot_sound, 0.02f);
    Music menu_music = LoadMusicStream("assets/sounds/musics/menumusic/menumusic.mp3");

    Texture2D menu_background = LoadTexture("assets/sprites/menu/menu.png");

    while (current_screen != EXIT_SCREEN && !WindowShouldClose())
    {
        if (current_screen == MENU_SCREEN)
        {
            PlayMusicStream(menu_music);
            current_screen = menu(menu_music, menu_background);
        }
        else if (current_screen == GAME_SCREEN)
        {
            bool is_paused = false;
            bool game_running = true;
            int selected = 0;

            StopMusicStream(menu_music);

            int currentScore = 0;
            int highScore = LoadHighScore();
            float scoreTimer = 0.0f;
            float scoreInterval = 0.1f; 
            int pointsPerInterval = 10; 

            ScorePopup popups[MAX_POPUPS];
            InitPopups(popups);

            Player player;
            Bullet bullets[MAX_BULLETS];
            BombProjectile active_bombs[MAX_ACTIVE_BOMBS];

            for (int i = 0; i < MAX_ACTIVE_BOMBS; i += 1) active_bombs[i].active = false;
            
            Boss flandre;
            EnemyBullet enemy_bullets[MAX_ENEMY_BULLETS];

            Texture2D bullet_sprite = LoadTexture("assets/sprites/bullets/playerbullet.png");
            Vector2 start_pos = {400, 715};

            InitPlayer(&player, start_pos, BASE_SPEED);
            InitBullet(bullets, bullet_sprite);

            InitBoss(&flandre, (Vector2){400, 100});
            InitEnemyBullets(enemy_bullets);
            
            Texture2D bullet_red = LoadTexture("assets/sprites/bullets/bullet_small_red.png");
            Texture2D bullet_pink = LoadTexture("assets/sprites/bullets/bullet_small_pink.png");
            Texture2D bullet_orange = LoadTexture("assets/sprites/bullets/bullet_small_orange.png");
            Texture2D bullet_yellow_glow = LoadTexture("assets/sprites/bullets/bullet_medium_yellow_glow.png");
            Texture2D bullet_blue_outline = LoadTexture("assets/sprites/bullets/bullet_outline_blue.png");
            Texture2D bullet_blue_solid = LoadTexture("assets/sprites/bullets/bullet_small_blue.png");
            Texture2D bullet_orange_oval = LoadTexture("assets/sprites/bullets/bullet_oval_orange.png");
            Texture2D bullet_orange_outline = LoadTexture("assets/sprites/bullets/bullet_orange_outline.png");

            BossAssets boss_assets = 
            {
                .bullet_red = bullet_red,
                .bullet_pink = bullet_pink,
                .bullet_orange = bullet_orange,
                .bullet_yellow_glow = bullet_yellow_glow,
                .bullet_blue_outline = bullet_blue_outline,
                .bullet_blue_solid = bullet_blue_solid,
                .bullet_orange_oval = bullet_orange_oval,
                .bullet_orange_outline = bullet_orange_outline
            };

            Texture2D pause_menu1 = LoadTexture("assets/sprites/menu/pause_menu3.png");
            Texture2D pause_menu2 = LoadTexture("assets/sprites/menu/pause_menu2.png");

            Animation map;
            LoadMapSprites(&map);

            while (game_running && !WindowShouldClose())
            {
                float dt = GetFrameTime();

                if (IsKeyPressed(KEY_ESCAPE)) is_paused = !is_paused;
                
                if (is_paused)
                {
                    if (IsKeyPressed(KEY_UP)) selected--;
                    if (IsKeyPressed(KEY_DOWN)) selected++;
                    if (selected < 0) selected = 1;
                    if (selected > 1) selected = 0;

                    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_Z))
                    {
                        if (selected == 0) { is_paused = false; selected = 0; }
                        else if (selected == 1) { game_running = false; current_screen = MENU_SCREEN; }
                    }
                }

                if (!is_paused)
                {
                    scoreTimer += dt;
                    if (scoreTimer >= scoreInterval)
                    {
                        currentScore += pointsPerInterval;
                        scoreTimer -= scoreInterval; 
                    }
                    if (currentScore > highScore) highScore = currentScore;

                    UpdatePlayer(&player, dt, bullets, shoot_sound, active_bombs);
                    UpdateBoss(&flandre, dt, enemy_bullets, player.position, &boss_assets);

                    if (flandre.justChangedPhase)
                    {
                        currentScore += 50000; 
                        flandre.justChangedPhase = false; 
                        SpawnPopup(popups, (Vector2){400, 300}, "PHASE CLEAR! +50000", GOLD, 30);
                    }

                    UpdateBullets(bullets, dt);
                    UpdateEnemyBullets(enemy_bullets, dt);
                    UpdateBombProjectiles(active_bombs, dt);
                    
                    UpdatePopups(popups, dt);

                    CheckPlayerVsBoss(&flandre, bullets);
                    
                    CheckBossVsPlayer(&player, enemy_bullets, &currentScore, popups, &current_screen);
                }
                
                BeginDrawing();
                    ClearBackground(RAYWHITE);
                    Vector2 map_pos = {0, 0};
                    DrawAnimationFrame(&map, map_pos, 1.0f, WHITE);
                    if (!is_paused) UpdateAnimation(&map, dt);
                    
                    DrawPlayer(&player);
                    DrawBoss(&flandre);
                    DrawEnemyBullets(enemy_bullets);
                    DrawBullets(bullets);
                    DrawBombProjectiles(active_bombs);
                    
                    DrawPopups(popups); 

                    DrawHealths(&player);
                    DrawBombs(&player);

                    DrawText(TextFormat("SCORE: %010d", currentScore), 850, 20, 30, WHITE);
                    DrawText(TextFormat("HIGH:  %010d", highScore), 850, 60, 30, LIGHTGRAY);

                    if (is_paused)
                    {
                        Vector2 menu_pos;
                        Texture2D menu_text;
                        if (selected == 0) menu_text = pause_menu1;
                        else menu_text = pause_menu2;
                        menu_pos.x = (float)(GetScreenWidth() - menu_text.width) / 2;
                        menu_pos.y = (float)(GetScreenHeight() - menu_text.height) / 2;
                        DrawTexture(menu_text, menu_pos.x, menu_pos.y, RAYWHITE);
                    }
                EndDrawing();
            }

            SaveHighScore(highScore);

            UnloadPlayer(&player);
            UnloadBoss(&flandre);
            UnloadTexture(bullet_sprite);
            UnloadMapSprites(&map);
            UnloadTexture(bullet_red);
            UnloadTexture(bullet_pink);
            UnloadTexture(bullet_orange);
            UnloadTexture(bullet_yellow_glow);
            UnloadTexture(bullet_blue_outline);
            UnloadTexture(bullet_blue_solid);
            UnloadTexture(bullet_orange_oval);
            UnloadTexture(bullet_orange_outline);
            UnloadTexture(pause_menu1);
            UnloadTexture(pause_menu2);
        }
    }

    UnloadSound(shoot_sound);
    UnloadMusicStream(menu_music);
    UnloadTexture(menu_background);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}