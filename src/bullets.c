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

void InitEnemyBullets(EnemyBullet *bullets)
{
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        bullets[i].active = false;
        bullets[i].radius = 4.0f;
    }
}

void SpawnEnemyBullet(EnemyBullet *bullets, Vector2 position, float angle, float speed, EnemyBulletType type, Texture2D sprite)
{
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

            if (bullets[i].position.x < -50 || bullets[i].position.x > 850 || bullets[i].position.y < -50 || bullets[i].position.y > 850)
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
            Vector2 draw_pos =
            {
                bullets[i].position.x - (bullets[i].sprite.width / 2.0f),
                bullets[i].position.y - (bullets[i].sprite.height / 2.0f)
            };

            DrawTextureEx(bullets[i].sprite, draw_pos, 0.0f, 1.0f, WHITE);
        }
    }
}