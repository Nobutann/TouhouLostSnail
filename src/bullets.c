#include "bullets.h"
#include "raymath.h"

void InitBullet(Bullet *bullets, Texture2D sprite)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        bullets[i].active = false;
        bullets[i].sprite = sprite;
    }
}

void UpdateBullets(Bullet *bullets, float dt)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullets[i].active)
        {
            bullets[i].position = Vector2Add(bullets[i].position, Vector2Scale(bullets[i].velocity, dt));

            if (bullets[i].position.y < -bullets[i].sprite.height)
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
            Vector2 origin = {bullets[i].sprite.width / 1.0f, bullets[i].sprite.height / 1.0f};

            DrawTexturePro
            (
                bullets[i].sprite, 
                (Rectangle){0, 0, (float)bullets[i].sprite.width, (float)bullets[i].sprite.height},
                (Rectangle){bullets[i].position.x, bullets[i].position.y, (float)bullets[i].sprite.width, (float)bullets[i].sprite.height},
                origin,
                -90.0f,
                WHITE
            );
        }
    }
}

void UpdateBombProjectiles(BombProjectile *active_bombs, float dt)
{
    for (int i = 0; i < MAX_ACTIVE_BOMBS; i += 1)
    {
        if (active_bombs[i].active)
        {
            active_bombs[i].position.y += active_bombs[i].velocity.y * dt;

            if (active_bombs[i].position.y < -50)
            {
                active_bombs[i].active = false;
            }
        }
    }
}

void DrawBombProjectiles(BombProjectile *active_bombs)
{
    for (int i = 0; i < MAX_ACTIVE_BOMBS; i += 1)
    {
        if (active_bombs[i].active)
        {
            DrawCircleV(active_bombs[i].position, 30, YELLOW);
        }
    }
}