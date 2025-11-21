#include "player.h"
#include <math.h>
#include "bullets.h"
#include "raymath.h"
#include "sprite.h"
#include <stdlib.h>
#include <stdio.h>
#include "screens.h"

#define FIRE_RATE 0.066f /* 15 tiros por segundo */
#define BULLET_DISTANCE_X 8
#define BULLET_DISTANCE_Y 20
#define PLAYER_CENTER 15
#define FOCUS_SPEED 200.0f
#define RIGHT_LIMIT 700
#define LEFT_LIMIT -60
#define BOTTOM_LIMIT 650
#define TOP_LIMIT -40

HealthNode g_health1, g_health2, g_health3, g_health4;
UltsNode g_ult1, g_ult2, g_ult3;

void InitPlayer(Player *player, Vector2 initial_pos, float speed)
{
    player->healths = NULL;

    player->position = initial_pos;
    player->speed = speed;
    player->shoot_timer = 0.0f;
    player->is_invulnerable = false;
    player->invul_timer = 0.0f;
    
    g_health1.next = &g_health2;
    g_health2.next = &g_health3;
    g_health3.next = &g_health4;
    g_health4.next = NULL;

    player->healths = &g_health1;

    g_ult1.next = &g_ult2;
    g_ult2.next = &g_ult3;
    g_ult3.next = NULL;

    player->ults = &g_ult1;

    LoadPlayerSprites(&player->sprites);
}

void UpdatePlayer(Player *player, float dt, Bullet *bullets, Sound shoot_sound)
{
    if (player->is_invulnerable)
    {
        player->invul_timer -= dt;
        if (player->invul_timer <= 0.0f)
        {
            player->is_invulnerable = false;
            player->invul_timer = 0.0f;
        }
    }

    Vector2 input = {0, 0};

    if (IsKeyDown(KEY_UP))
    {
        input.y = -1;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        input.y = 1;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        input.x = 1;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        input.x = -1;
    }
    
    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
        player->speed = FOCUS_SPEED;
    }
    else
    {
        player->speed = BASE_SPEED;
    }

    if (input.x != 0 && input.y != 0)
    {
        float length = sqrtf(input.x * input.x + input.y * input.y);
        input.x /= length;
        input.y /= length;
    }

    player->shoot_timer -= dt;
    if (IsKeyDown(KEY_Z) && player->shoot_timer <= 0.0f)
    {
        PlayerShoot(player, bullets);
        player->shoot_timer = FIRE_RATE;
        PlaySound(shoot_sound);
    }

    if (IsKeyPressed(KEY_R))
    {
        if (player->ults != NULL)
        {
            LoseUlts(player);
        }
    }

    player->position.x += input.x * player->speed * dt;
    player->position.y += input.y * player->speed * dt;

    if (player->position.x < LEFT_LIMIT)
    {
        player->position.x = LEFT_LIMIT;
    }
    if (player->position.x > RIGHT_LIMIT)
    {
        player->position.x = RIGHT_LIMIT;
    }
    if (player->position.y < TOP_LIMIT)
    {
        player->position.y = TOP_LIMIT;
    }
    if (player->position.y > BOTTOM_LIMIT)
    {
        player->position.y = BOTTOM_LIMIT;
    }

    Animation *anim = &player->sprites.idle;

    if (input.x < 0)
    {
        anim = &player->sprites.fly_left;
    }
    else if (input.x > 0)
    {
        anim = &player->sprites.fly_right;
    }

    UpdateAnimation(anim, dt);
}

void DrawPlayer(Player *player)
{
    Animation *anim = &player->sprites.idle;

    if (IsKeyDown(KEY_LEFT))
    {
        anim = &player->sprites.fly_left;
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        anim = &player->sprites.fly_right;
    }

    if (player->is_invulnerable)
    {
        int blink = (int)(player->invul_timer * 10) % 2;
        if (blink == 0)
        {
            DrawAnimationFrame(anim, player->position, 1.5f, WHITE);
        }
    }
    else
    {
        DrawAnimationFrame(anim, player->position, 1.5f, WHITE);
    }

    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
        Vector2 hitbox_center = 
        {
            player->position.x + (player->sprites.idle.frames[0].width / 1.3f),
            player->position.y + (player->sprites.idle.frames[0].height / 1.3f)
        };
        DrawCircleV(hitbox_center, HITBOX_RADIUS, WHITE);
    }
}

void PlayerShoot(Player *player, Bullet *bullets)
{
    Vector2 center = 
    {
        player->position.x + player->sprites.idle.frames[0].width / 1.7,
        player->position.y + player->sprites.idle.frames[0].height / 1
    };

    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (!bullets[i].active)
        {
            bullets[i].position = (Vector2){center.x - BULLET_DISTANCE_X + PLAYER_CENTER, center.y - BULLET_DISTANCE_Y};
            bullets[i].velocity = (Vector2){0, -BULLET_SPEED};
            bullets[i].active = true;
            break;
        }
    }

    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (!bullets[i].active)
        {
            bullets[i].position = (Vector2){ center.x + BULLET_DISTANCE_X + PLAYER_CENTER, center.y - BULLET_DISTANCE_Y };
            bullets[i].velocity = (Vector2){0, -BULLET_SPEED};
            bullets[i].active = true;
            break;
        }
    }
}

void UnloadPlayer(Player *player)
{
    UnloadPlayerSprites(&player->sprites);
}



void LoseHealth(Player *player, GameScreen *current_screen)
{
    if (player->healths == NULL) 
    {   
        *current_screen = GAMEOVER_SCREEN;
        return;
    }

    player->healths = player->healths->next;
}


void DrawHealths(Player *player)
{
    int startX = 1046;
    int startY = 210;
    int radius = 17;
    int spacing = 44;

    int lives = 0;
    HealthNode *p = player->healths;

    while (p != NULL)
    {
        lives += 1;
        p = p->next;
    }

    for (int i = 0; i < 4; i += 1) 
    {
        Color color = (i < lives) ? RED : DARKGRAY;

        DrawCircle(startX + i * spacing, startY, radius, color);
    }
}



void LoseUlts(Player *player)
{
    if (player->ults == NULL)
    {
        printf("Não possui mais bombas\n");
        return;
    }

    player->ults = player->ults->next;
}

void DrawUlts(Player *player)
{   
    int startX = 1016;
    int startY = 318;
    int radius = 17;
    int spacing = 44;

    int bombs = 0;
    UltsNode *b = player->ults;

    while (b != NULL)
    {
        bombs += 1;
        b = b->next;
    }

    for (int i = 0; i < 3; i += 1) 
    {
        Color color = (i < bombs) ? BLACK : DARKGRAY;

        DrawCircle(startX + i * spacing, startY, radius, color);
    }
    
}


