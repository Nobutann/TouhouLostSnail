#ifndef BULLETS_H
#define BULLETS_H

#include "raylib.h"
#define MAX_BULLETS 100

typedef struct
{
    Vector2 position;
    Vector2 velocity;
    Texture2D sprite;
    bool active;
} Bullet;

void InitBullet(Bullet *bullets, Texture2D sprite);
void UpdateBullets(Bullet *bullets, float dt);
void DrawBullets(Bullet *bullets);

#endif