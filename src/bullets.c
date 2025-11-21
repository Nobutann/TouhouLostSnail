#include "bullets.h"
#include "raymath.h"
#include <string.h> 
#include <stdio.h>


void InitPopups(ScorePopup *popups)
{
    for (int i = 0; i < MAX_POPUPS; i++)
    {
        popups[i].active = false;
        popups[i].text[0] = '\0';
    }
}

void SpawnPopup(ScorePopup *popups, Vector2 pos, const char *text, Color color, float size)
{
    for (int i = 0; i < MAX_POPUPS; i++)
    {
        if (!popups[i].active)
        {
            popups[i].position = pos;
            
            strcpy(popups[i].text, text);
            
            popups[i].color = color;
            popups[i].active = true;
            popups[i].lifetime = 1.5f;     
            popups[i].max_lifetime = 1.5f;
            popups[i].fontSize = size;
            return;
        }
    }
}

void UpdatePopups(ScorePopup *popups, float dt)
{
    for (int i = 0; i < MAX_POPUPS; i++)
    {
        if (popups[i].active)
        {
            popups[i].lifetime -= dt;
            popups[i].position.y -= 60.0f * dt;

            if (popups[i].lifetime <= 0)
            {
                popups[i].active = false;
            }
        }
    }
}

void DrawPopups(ScorePopup *popups)
{
    for (int i = 0; i < MAX_POPUPS; i++)
    {
        if (popups[i].active)
        {
       
            DrawText(popups[i].text, (int)popups[i].position.x + 2, (int)popups[i].position.y + 2, (int)popups[i].fontSize, BLACK);
            
         
            DrawText(popups[i].text, (int)popups[i].position.x, (int)popups[i].position.y, (int)popups[i].fontSize, popups[i].color);
        }
    }
}



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
            DrawTextureEx(bullets[i].sprite, bullets[i].position, -90.0f, 1.0f, WHITE);
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
            bullets[i].hasBeenGrazed = false; 
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