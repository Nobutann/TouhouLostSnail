#include "bullets.h"
#include "raymath.h"
#include <stddef.h>

static Bullet *g_player_bullets = NULL;
static EnemyBullet *g_enemy_bullets = NULL;
static bool g_bullets_enabled = true;

void InitBullet(Bullet *bullets, Texture2D sprite)
{
    g_player_bullets = bullets;
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
            DrawTextureEx(bullets[i].sprite, bullets[i].position, -90.0f, 1.0f, WHITE);
        }
    }
}

void InitEnemyBullets(EnemyBullet *bullets)
{
    g_enemy_bullets = bullets;
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        bullets[i].active = false;
        bullets[i].radius = 4.0f;
    }
}

void SpawnEnemyBullet(EnemyBullet *bullets, Vector2 position, float angle, float speed, EnemyBulletType type, Texture2D sprite)
{
    if (!g_bullets_enabled)
    {
        return;
    }

    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        if (!bullets[i].active)
        {
            bullets[i].position = position;
            bullets[i].angle = angle;
            bullets[i].speed = speed;
            bullets[i].velocity.x = cosf(angle) * speed;
            bullets[i].velocity.y = sinf(angle) * speed;
            bullets[i].type = type;
            bullets[i].active = true;
            bullets[i].sprite = sprite;
            bullets[i].lifetime = 0.0f;
            break;
        }
    }
}

void UpdateEnemyBullets(EnemyBullet *bullets, float dt)
{
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        if (bullets[i].active)
        {
            bullets[i].lifetime += dt;

            bullets[i].position.x += bullets[i].velocity.x * dt;
            bullets[i].position.y += bullets[i].velocity.y * dt;

            if (bullets[i].position.x < 25 || bullets[i].position.x > 805 || bullets[i].position.y < 25 || bullets[i].position.y > 780)
            {
                bullets[i].active = false;
            }
        }
    }
}

void DrawEnemyBullets(EnemyBullet *bullets)
{
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        if (bullets[i].active)
        {
            float rotation_degrees = bullets[i].angle * RAD2DEG;

            rotation_degrees += 90.0f;

            Vector2 origin = 
            {
                bullets[i].sprite.width / 2.0f,
                bullets[i].sprite.height / 2.0f
            };

            Rectangle source = {0, 0, (float)bullets[i].sprite.width, (float)bullets[i].sprite.height};
            Rectangle dest = 
            {
                bullets[i].position.x,
                bullets[i].position.y,
                (float)bullets[i].sprite.width,
                (float)bullets[i].sprite.height
            };

            DrawTexturePro(bullets[i].sprite, source, dest, origin, rotation_degrees, RAYWHITE);
        }
    }
}

void ClearAllBullets(void)
{
    if (g_player_bullets != NULL)
    {
        for (int i = 0; i < MAX_BULLETS; i++)
        {
            g_player_bullets[i].active = false;
        }
    }

    if (g_enemy_bullets != NULL)
    {
        for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
        {
            g_enemy_bullets[i].active = false;
        }
    }
}

void DisableBullets(void)
{
    g_bullets_enabled = false;
}

void EnableBullets(void)
{
    g_bullets_enabled = true;
}