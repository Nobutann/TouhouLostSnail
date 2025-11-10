#ifndef BULLETS_H
#define BULLETS_H

#include "raylib.h"

#define MAX_BULLETS 100
#define BULLET_SPEED 2000
#define MAX_ACTIVE_BOMBS 3
#define BOMB_SPEED 1200


typedef struct
{
    Vector2 position;
    Vector2 velocity;
    Texture2D sprite;
    bool active;
} Bullet;

typedef struct
{
    Vector2 position;
    Vector2 velocity;
    bool active;
} BombProjectile;


void InitBullet(Bullet *bullets, Texture2D sprite);
void UpdateBullets(Bullet *bullets, float dt);
void DrawBullets(Bullet *bullets);
void UpdateBombProjectiles(BombProjectile *active_bombs, float dt);
void DrawBombProjectiles(BombProjectile *active_bombs);

#endif