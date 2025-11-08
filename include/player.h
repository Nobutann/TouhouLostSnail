#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "sprite.h"
#include "bullets.h"
#define BASE_SPEED 1000.0f

typedef struct HealthNode {
    struct HealthNode *next;
} HealthNode;

typedef struct Bombs {
    struct Bombs *next;
} Bombs;

typedef struct
{
    HealthNode *healths;
    Vector2 position;
    float speed;
    PlayerSprites sprites;
    float shoot_timer;
    Bombs *bombs;
} Player;

void InitPlayer(Player *player, Vector2 initial_pos, float speed);
void UpdatePlayer(Player *player, float dt, Bullet *bullets, Sound shoot_sound);
void DrawPlayer(Player *player);
void UnloadPlayer(Player *player);
void PlayerShoot(Player *player, Bullet *bullets);
void LoseHealth(Player *player);
void DrawHealths(Player *player);
void LoseBombs(Player *player);
void DrawBombs(Player *player);

#endif