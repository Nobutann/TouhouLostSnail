#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "sprite.h"
#include "bullets.h"

typedef struct
{
    int health;
    Vector2 position;
    float speed;
    PlayerSprites sprites;
    float shoot_timer;
} Player;

void InitPlayer(Player *player, Vector2 initial_pos, float speed);
void UpdatePlayer(Player *player, float dt, Bullet *bullets, Sound shoot_sound);
void DrawPlayer(Player *player);
void UnloadPlayer(Player *player);
void PlayerShoot(Player *player, Bullet *bullets);

#endif