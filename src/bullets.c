#include "bullets.h"
#include "raymath.h"

#define MAX_BULLETS 1000

void InitBullet(Bullet *bullets)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        bullets[i].active = false;
    }

    bullets->sprite = LoadTexture('assets/sprites/bullets/playerbullet.png');
}

void UpdateBullets(Bullet *bullets)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullets[i].active)
        {
            bullets[i].position = Vector2Add(bullets[i].position, Vector2Scale(bullets[i].velocity, GetFrameTime()));

            if (bullets[i].position.x < 0 || bullets[i].position.x > GetScreenWidth() || bullets[i].position.y < 0 || bullets[i].position.y > GetScreenHeight())
            {
                bullets[i].active = false;
            }
        }
    }
}

void DrawBullets(Bullet *bullets)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullets[i].active)
        {
            DrawTextureV(bullets[i].sprite, bullets[i].position, WHITE);
        }
    }
}