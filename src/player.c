#include "player.h"
#include <math.h>
#include "bullets.h"
#include "raymath.h"
#include "sprite.h"
#include <stdlib.h>
#include <stdio.h>

#define FIRE_RATE 0.066f /* 15 tiros por segundo */
#define BULLET_DISTANCE_X 8
#define BULLET_DISTANCE_Y 20
#define PLAYER_CENTER 15
#define FOCUS_SPEED 500.0f
#define RIGHT_LIMIT 760
#define LEFT_LIMIT 15
#define BOTTOM_LIMIT 715
#define TOP_LIMIT 5

HealthNode g_health1, g_health2, g_health3, g_health4;
Bombs g_bomb1, g_bomb2, g_bomb3;

void InitPlayer(Player *player, Vector2 initial_pos, float speed)
{
    player->healths = NULL;

    player->position = initial_pos;
    player->speed = speed;
    player->shoot_timer = 0.0f;
    
    g_health1.next = &g_health2;
    g_health2.next = &g_health3;
    g_health3.next = &g_health4;
    g_health4.next = NULL;

    player->healths = &g_health1;

    g_bomb1.next = &g_bomb2;
    g_bomb2.next = &g_bomb3;
    g_bomb3.next = NULL;

    player->bombs = &g_bomb1;

    LoadPlayerSprites(&player->sprites);
}

void UpdatePlayer(Player *player, float dt, Bullet *bullets, Sound shoot_sound)
{
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

    DrawAnimationFrame(anim, player->position, 1.5f, WHITE);
}

void PlayerShoot(Player *player, Bullet *bullets)
{
    Vector2 center = 
    {
        player->position.x + player->sprites.idle.frames[0].width / 2,
        player->position.y + player->sprites.idle.frames[0].height / 2
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



void LoseHealth(Player *player)
{
    if (player->healths == NULL) 
    {   
        printf("Game Over\n");
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



void LoseBombs(Player *player)
{
    if (player->bombs == NULL)
    {
        printf("Não possui mais bombas\n");
        return;
    }

    player->bombs = player->bombs->next;
}

void DrawBombs(Player *player)
{   
    int startX = 1016;
    int startY = 318;
    int radius = 17;
    int spacing = 44;

    int bombs = 0;
    Bombs *b = player->bombs;

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