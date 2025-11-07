#ifndef BULLETS_H
#define BULLETS_H

#include "raylib.h"

typedef struct
{
    Vector2 position;
    Vector2 velocity;
    Texture2D sprite;
    bool active;
} Bullet;

void InitBullet(Bullet *bullets);
void UpdateBullets(Bullet *bullets);
void DrawBullets(Bullet *bullets);

#endif