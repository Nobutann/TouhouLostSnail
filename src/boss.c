#include "boss.h"
#include "bullets.h"
#include "raymath.h"
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265358979323846f
#define DEG2RAD (PI/180.0f)
#define RAD2DEG (180.0f/PI)

void InitBoss(Boss *boss, Vector2 initial_pos)
{
    boss->position = initial_pos;
    boss->target_position = initial_pos;
    boss->health = BOSS_HEALTH_NONSPELL1;
    boss->max_health = BOSS_HEALTH_NONSPELL1;
    boss->current_phase = BOSS_PHASE_NONSPELL1;
    boss->frame_counter = 0;
    boss->move_timer = 0.0f;
    boss->is_moving = false;
}

void NonSpell1(Boss *boss, EnemyBullet *enemy_bullets, Vector2 player_pos)
{
    boss->frame_counter++;

    boss->move_timer += GetFrameTime();

    if (boss->move_timer >= 2.0f)
    {
        boss->move_timer = 0.0f;

        float min_x = 100.0f;
        float max_x = 700.0f;
        boss->target_position.x = min_x + (rand() % (int)(max_x - min_x));
        boss->target_position.y = 100.0f;
    }

    float move_speed = 150.0f * GetFrameTime();
    boss->position.x += (boss->target_position.x - boss->position.x) * move_speed * 0.1f;
    boss->position.y += (boss->target_position.y - boss->position.y) * move_speed * 0.1f;

    if (boss->frame_counter % 6 == 0)
    {
        for (int i = 0; i < 8; i++)
        {
            float angle = (float)(rand() % 360) * DEG2RAD;
            float speed = 180.0f + (rand() % 100);
            Texture2D *sprite;
            SpawnEnemyBullet(enemy_bullets, boss->position, angle, speed, BULLET_TYPE_NORMAL, sprite);
        }
    }

    if (boss->frame_counter % 20 == 0)
    {
        float dx = player_pos.x - boss->position.x;
        float dy = player_pos.y - boss->position.y;
        float base_angle = atan2f(dy, dx);

        float spread_angles[] = {-15.0f * DEG2RAD, 0.0f, 15.0f * DEG2RAD};

        for (int i = 0; i < 3; i++)
        {
            float angle = base_angle + spread_angles[i];
            float speed = 320.0f;

            Texture2D *sprite;
            SpawnEnemyBullet(enemy_bullets, boss->position, angle, speed, BULLET_TYPE_AIMED, sprite);
        }
    }

    if (boss->frame_counter % 45 == 0)
    {
        int wave_bullets = 16;
        float angle_step = (2.0f * PI) / wave_bullets;
        float base_rotation = (boss->frame_counter * 0.1f);

        for (int i = 0; i < wave_bullets; i++)
        {
            float angle = (angle_step * i) + base_rotation;
            float speed = 140.0f;

            Texture2D *sprite;
            SpawnEnemyBullet(enemy_bullets, boss->position, angle, speed, BULLET_TYPE_NORMAL, sprite);
        }
    }
}

void UpdateBoss(Boss *boss, float dt, EnemyBullet *enemy_bullets, Vector2 player_pos)
{
    switch (boss->current_phase)
    {
        case BOSS_PHASE_NONSPELL1:
            NonSpell1(boss, enemy_bullets, player_pos);

            if (boss->health <= 0)
            {
                boss->current_phase = BOSS_PHASE_SPELL1;
                boss->frame_counter = 0;
            }
            break;
    }
}

void DrawBoss(Boss *boss)
{
    float bar_width = 400.0f;
    float bar_height = 20.0f;
    float bar_x = 200.0f;
    float bar_y = 30.0f;

    DrawRectangle(bar_x, bar_y, bar_width, bar_height, DARKGRAY);
    float health_percent = boss->health / boss->max_health;
    DrawRectangle(bar_x, bar_y, bar_width * health_percent, bar_height, PURPLE);

    DrawRectangleLines(bar_x, bar_y, bar_width, bar_height, BLACK);
}

void UnloadBoss(Boss *boss)
{
    //ja ja
}