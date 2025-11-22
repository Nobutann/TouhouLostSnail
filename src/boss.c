#include "boss.h"
#include "bullets.h"
#include "raymath.h"
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265358979323846f
#define DEG2RAD (PI/180.0f)
#define RAD2DEG (180.0f/PI)

static Boss *g_boss = NULL;

void InitBoss(Boss *boss, Vector2 initial_pos)
{
    g_boss = boss;
    boss->position = initial_pos;
    boss->target_position = initial_pos;
    boss->last_position = initial_pos;
    boss->health = BOSS_HEALTH_NONSPELL1;
    boss->max_health = BOSS_HEALTH_NONSPELL1;
    boss->current_phase = BOSS_PHASE_NONSPELL1;
    boss->frame_counter = 0;
    boss->move_timer = 0.0f;
    boss->is_moving = false;

    LoadBossSprites(&boss->sprites);
}

void NonSpell1(Boss *boss, EnemyBullet *enemy_bullets, Vector2 player_pos, BossAssets *assets)
{
    boss->frame_counter++;

    boss->move_timer += GetFrameTime();

    if (boss->move_timer >= 2.5f)
    {
        boss->move_timer = 0.0f;

        float min_x = 120.0f;
        float max_x = 680.0f;
        boss->target_position.x = min_x + (rand() % (int)(max_x - min_x));
        boss->target_position.y = 100.0f;
    }

    float move_speed = 150.0f * GetFrameTime();
    boss->position.x += (boss->target_position.x - boss->position.x) * move_speed * 0.1f;
    boss->position.y += (boss->target_position.y - boss->position.y) * move_speed * 0.1f;

    if (boss->frame_counter % 50 == 0)
    {
        int wave_bullets = 16;
        float angle_step = (2.0f * PI) / wave_bullets;
        float base_rotation = (boss->frame_counter * 0.05f);

        for (int i = 0; i < wave_bullets; i++)
        {
            float angle = (angle_step * i) + base_rotation;
            float speed = 150.0f;

            SpawnEnemyBullet(enemy_bullets, boss->position, angle, speed, BULLET_TYPE_NORMAL, assets->bullet_orange_oval);
        }
    }

    if (boss->frame_counter % 10 == 0)
    {
        for (int i = 0; i < 2; i++)
        {
            float angle = (float)(rand() % 360) * DEG2RAD;
            float speed = 120.0f + (rand() % 60);

            SpawnEnemyBullet(enemy_bullets, boss->position, angle, speed, BULLET_TYPE_NORMAL, assets->bullet_orange_oval);
        }
    }

    if (boss->frame_counter % 35 == 0)
    {
        float dx = player_pos.x - boss->position.x;
        float dy = player_pos.y - boss->position.y;
        float base_angle = atan2f(dy, dx);

        for (int i = 0; i < 3; i++)
        {
            float speed = 200.0f + (i * 20.0f);

            SpawnEnemyBullet(enemy_bullets, boss->position, base_angle, speed, BULLET_TYPE_AIMED, assets->bullet_orange_outline);
        }
    }

    if (boss->frame_counter % 120 == 0)
    {
        int dense_bullets = 24;
        float angle_step = (2.0f * PI) / dense_bullets;

        for (int i = 0; i < dense_bullets; i++)
        {
            float angle = angle_step * i;
            float speed = 130.0f;

            SpawnEnemyBullet(enemy_bullets, boss->position, angle, speed, BULLET_TYPE_NORMAL, assets->bullet_orange_oval);
        }
    }
}

void SpellCard1(Boss *boss, EnemyBullet *enemy_bullets, Vector2 player_pos, BossAssets *assets)
{
    boss->frame_counter++;
    
    boss->target_position.x = 400.0f;
    boss->target_position.y = 150.0f;

    float move_speed = 100.0f * GetFrameTime();
    boss->position.x += (boss->target_position.x - boss->position.x) * move_speed * 0.1f;
    boss->position.y += (boss->target_position.y - boss->position.y) * move_speed * 0.1f;

    if (boss->frame_counter % 3 == 0)
    {
        float base_rotation = (boss->frame_counter * 0.05);

        float directions[4] = {0.0f, PI / 2.0f, PI, 3.0f * PI / 2.0f};

        Texture2D colors[4] = 
        {
            assets->bullet_red,
            assets->bullet_blue_solid,
            assets->bullet_pink,
            assets->bullet_yellow_glow
        };

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                float angle = directions[i] + base_rotation + (j * 0.15f);

                float speed = 200.0f + (j * 30.0f);

                SpawnEnemyBullet(enemy_bullets, boss->position, angle, speed, BULLET_TYPE_NORMAL, colors[i]);
            }
        }
    }

    if (boss->frame_counter % 60 == 0)
    {
        int wave_count = 20;
        float angle_step = (2.0f * PI) / wave_count;

        for (int i = 0; i < wave_count; i++)
        {
            float angle = angle_step * i;
            float speed = 120.0f;

            SpawnEnemyBullet(enemy_bullets, boss->position, angle, speed, BULLET_TYPE_NORMAL, assets->bullet_orange);
        }
    }
}

void NonSpell2(Boss *boss, EnemyBullet *enemy_bullets, Vector2 player_pos, BossAssets *assets)
{
    boss->frame_counter++;

    boss->move_timer += GetFrameTime();

    if (boss->move_timer >= 2.0f)
    {
        boss->move_timer = 0.0f;

        float min_x = 150.0f;
        float max_x = 650.0f;

        boss->target_position.x = min_x + (rand() % (int)(max_x - min_x));
        boss->target_position.y = 100.0f;
    }

    float move_speed = 120.0f * GetFrameTime();
    boss->position.x += (boss->target_position.x - boss->position.x) * move_speed * 0.12f;
    boss->position.y += (boss->target_position.y - boss->position.y) * move_speed * 0.12f;

    if (boss->frame_counter % 60 == 0)
    {
        int wave_bullets = 16;
        float angle_step = (2.0f * PI) / wave_bullets;
        float base_rotation = (boss->frame_counter * 0.04f);

        for (int i = 0; i < wave_bullets; i++)
        {
            float angle = (angle_step * i) + base_rotation;
            float speed = 120.0f;

            SpawnEnemyBullet(enemy_bullets, boss->position, angle, speed, BULLET_TYPE_NORMAL, assets->bullet_red);
        }
    }

    if (boss->frame_counter % 45 == 0)
    {
        float base_rotation = (boss->frame_counter * 0.05f);

        for (int i = 0; i < 5; i++)
        {
            float angle = (PI * 0.7f) + (i * 0.15f) + base_rotation;
            float speed = 140.0f + (i * 10.0f);

            SpawnEnemyBullet(enemy_bullets, boss->position, angle, speed, BULLET_TYPE_NORMAL, assets->bullet_blue_solid);
        }

        for (int i = 0; i < 5; i++)
        {
            float angle = (PI * 0.3f) - (i * 0.15f) + base_rotation;
            float speed = (140.0f + (i * 10.0f));

            SpawnEnemyBullet(enemy_bullets, boss->position, angle, speed, BULLET_TYPE_NORMAL, assets->bullet_blue_solid);
        }
    }    

    if (boss->frame_counter % 45 == 0)
    {
        float dx = player_pos.x - boss->position.x;
        float dy = player_pos.y - boss->position.y;
        float base_angle = atan2f(dy, dx);

        for (int i = -1; i < 1; i++)
        {
            float angle = base_angle + (i * 15.0f * DEG2RAD);
            float speed = 200.0f;

            SpawnEnemyBullet(enemy_bullets, boss->position, angle, speed, BULLET_TYPE_AIMED, assets->bullet_pink);
        }
    }

    if (boss->frame_counter % 80 == 0)
    {
        float cross_rotation = (boss->frame_counter * 0.06f);

        for (int i = 0; i < 4; i++)
        {
            float angle = (i * PI / 2.0f) + cross_rotation;
            
            for (int j = 0; j < 3; j++)
            {
                float speed = 100.0f + (j * 40.0f);
                
                SpawnEnemyBullet(enemy_bullets, boss->position, angle, speed, BULLET_TYPE_NORMAL, assets->bullet_orange);
            }
        }
    }
}

void SpellCard2(Boss *boss, EnemyBullet *enemy_bullets, Vector2 player_pos, BossAssets *assets)
{
    boss->frame_counter++;

    boss->target_position.x = 400.0f;
    boss->target_position.y = 120.0f;

    float move_speed = 100.0f * GetFrameTime();
    boss->position.x += (boss->target_position.x - boss->position.x) * move_speed * 0.1f;
    boss->position.y += (boss->target_position.y - boss->position.y) * move_speed * 0.1f;

    if (boss->frame_counter % 80 == 0)
    {
        int main_wave_bullets = 32;
        float angle_step = (2.0f * PI) / main_wave_bullets;
        float base_rotation = (boss->frame_counter * 0.08f);

        for (int i = 0; i < main_wave_bullets; i++)
        {
            float angle = (angle_step * i) + base_rotation;

            for (int j = 0; j < 3; j++)
            {
                float speed = 80.0f + (j * 50.0f);
                SpawnEnemyBullet(enemy_bullets, boss->position, angle, speed, BULLET_TYPE_NORMAL, assets->bullet_red);
            }
        }
    }

    if (boss->frame_counter % 40 == 0)
    {
        int star_points = 16;
        float angle_step = (2.0f * PI) / star_points;
        float rotation_offset = (boss->frame_counter * 0.1f);

        for (int i = 0; i < star_points; i++)
        {
            float angle = (angle_step * i) + rotation_offset;

            if (i % 2 == 0)
            {
                SpawnEnemyBullet(enemy_bullets, boss->position, angle, 200.0f, BULLET_TYPE_NORMAL, assets->bullet_yellow_glow);
            }
            else
            {
                SpawnEnemyBullet(enemy_bullets, boss->position, angle, 150.0f, BULLET_TYPE_NORMAL, assets->bullet_orange_oval);
            }
        }
    }

    if (boss->frame_counter % 20 == 0)
    {
        float dx = player_pos.x - boss->position.x;
        float dy = player_pos.y - boss->position.y;
        float base_angle = atan2f(dy, dx);

        for (int i = -3; i <= 3; i++)
        {
            float angle = base_angle + (i * 8.0f * DEG2RAD);
            float speed = 250.0f;

            SpawnEnemyBullet(enemy_bullets, boss->position, angle, speed, BULLET_TYPE_AIMED, assets->bullet_pink);
        }
    }

    if (boss->frame_counter % 60 == 0)
    {
        float cross_rotation = (boss->frame_counter * 0.05f);

        for (int i = 0; i < 4; i++)
        {
            float base_angle = (i * PI / 2.0f) + cross_rotation;

            for (int j = 0; j < 5; j++)
            {
                float angle = base_angle;
                float speed = 100.0f + (j * 30.0f);

                SpawnEnemyBullet(enemy_bullets, boss->position, angle, speed, BULLET_TYPE_NORMAL, assets->bullet_blue_solid);
            }
        }
    }

    if (boss->frame_counter % 5 == 0)
    {
        float spiral_angle = (boss->frame_counter * 0.15f);

        for (int i = 0; i < 2; i++)
        {
            float angle = spiral_angle + (i * PI);
            float speed = 180.0f;

            SpawnEnemyBullet(enemy_bullets, boss->position, angle, speed, BULLET_TYPE_NORMAL, assets->bullet_orange);
        }
    }
}

void UpdateBoss(Boss *boss, float dt, EnemyBullet *enemy_bullets, Vector2 player_pos, BossAssets *assets)
{
    boss->last_position = boss->position;

    switch (boss->current_phase)
    {
        case BOSS_PHASE_NONSPELL1:
            NonSpell1(boss, enemy_bullets, player_pos, assets);

            if (boss->health <= 0)
            {
                boss->current_phase = BOSS_PHASE_SPELL1;
                boss->frame_counter = 0;
                boss->health = BOSS_HEALTH_SPELL1;
                boss->max_health = BOSS_HEALTH_SPELL1;
            }
            break;

        case BOSS_PHASE_SPELL1:
            SpellCard1(boss, enemy_bullets, player_pos, assets);

            if (boss->health <= 0)
            {
                for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
                {
                    enemy_bullets[i].active = false;
                }

                boss->current_phase = BOSS_PHASE_NONSPELL2;
                boss->frame_counter = 0;
                boss->health = BOSS_HEALTH_NONSPELL2;
                boss->max_health = BOSS_HEALTH_NONSPELL2;
            }
            break;
        
        case BOSS_PHASE_NONSPELL2:
            NonSpell2(boss, enemy_bullets, player_pos, assets);

            if (boss->health <= 0)
            {
                for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
                {
                    enemy_bullets[i].active = false;
                }

                boss->current_phase = BOSS_PHASE_SPELL2;
                boss->frame_counter = 0;
                boss->health = BOSS_HEALTH_SPELL2;
                boss->max_health = BOSS_HEALTH_SPELL2;
            }
            break;

        case BOSS_PHASE_SPELL2:
            SpellCard2(boss, enemy_bullets, player_pos, assets);

            if (boss->health <= 0)
            {
                for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
                {
                    enemy_bullets[i].active = false;
                }

                boss->current_phase = BOSS_PHASE_DEFEATED;
                boss->frame_counter = 0;
            }
            break;
    }
}

void DrawBoss(Boss *boss)
{
    float dx = boss->position.x - boss->last_position.x;
    float threshold = 0.5f;

    Animation *current_anim = &boss->sprites.idle;
    bool flip_horizontal = false;

    if (fabs(dx) > threshold)
    {
        current_anim = &boss->sprites.direction;

        if (dx < 0)
        {
            flip_horizontal = true;
        }
    }

    UpdateAnimation(current_anim, GetFrameTime());

    Vector2 draw_pos = 
    {
        boss->position.x - (current_anim->frames[current_anim->current_frame].width / 2.0f),
        boss->position.y - (current_anim->frames[current_anim->current_frame].height / 2.0f)
    };

    if (flip_horizontal)
    {
        Rectangle source = 
        {
            0,
            0,
            (float)-current_anim->frames[current_anim->current_frame].width,
            (float)current_anim->frames[current_anim->current_frame].height
        };

        Rectangle dest = 
        {
            boss->position.x,
            draw_pos.y,
            (float)current_anim->frames[current_anim->current_frame].width,
            (float)current_anim->frames[current_anim->current_frame].height
        };

        Vector2 origin = 
        {
            (float)current_anim->frames[current_anim->current_frame].width / 2.0f, 0
        };

        DrawTexturePro(current_anim->frames[current_anim->current_frame], source, dest, origin, 0.0f, WHITE);
    }
    else
    {
        DrawTextureEx(current_anim->frames[current_anim->current_frame], draw_pos, 0.0f, 1.0f, WHITE);
    }

    float bar_width = 400.0f;
    float bar_height = 20.0f;
    float bar_x = 200.0f;
    float bar_y = 30.0f;

    DrawRectangle(bar_x, bar_y, bar_width, bar_height, DARKGRAY);
    float health_percent = boss->health / boss->max_health;

    Color bar_color = PURPLE;
    if (boss->current_phase == BOSS_PHASE_SPELL1 || boss->current_phase == BOSS_PHASE_SPELL2)
    {
        bar_color = GOLD;
    }
    DrawRectangle(bar_x, bar_y, bar_width * health_percent, bar_height, bar_color);

    DrawRectangleLines(bar_x, bar_y, bar_width, bar_height, BLACK);

    if (boss->current_phase == BOSS_PHASE_SPELL1)
    {
        const char *spell_name = "Taboo: Four of a Kind";
        int text_width = MeasureText(spell_name, 30);
        DrawText(spell_name, (800 - text_width) / 2, 60, 30, GOLD);
    }
    else if (boss->current_phase == BOSS_PHASE_SPELL2)
    {
        const char *spell_name = "Taboo: Crimson Barrage";
        int text_width = MeasureText(spell_name, 30);
        DrawText(spell_name, (800 - text_width) / 2, 60, 30, GOLD);
    }
}

void CheckPlayerVsBoss(Boss *boss, Bullet *player_bullets)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (player_bullets[i].active)
        {
            Vector2 bullet_pos = player_bullets[i].position;

            if (CheckCollisionCircles(bullet_pos, PLAYER_BULLET_HITBOX, boss->position, BOSS_HITBOX_RADIUS))
            {
                boss->health -= PLAYER_BULLET_DAMAGE;
                player_bullets[i].active = false;

                if (boss->health < 0)
                {
                    boss->health = 0;
                }
            }
        }
    }
}

void CheckBossVsPlayer(Player *player, EnemyBullet *enemy_bullets, GameScreen *current_screen)
{
    if (player->is_invulnerable)
    {
        return;
    }

    Vector2 player_center = 
    {
        player->position.x + (player->sprites.idle.frames[0].width / 1.3f),
        player->position.y + (player->sprites.idle.frames[0].height / 1.3f)
    };

    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        if (enemy_bullets[i].active)
        {
            if (CheckCollisionCircles(player_center, HITBOX_RADIUS, enemy_bullets[i].position, enemy_bullets[i].radius))
            {
                LoseHealth(player, current_screen);

                player->is_invulnerable = true;
                player->invul_timer = INVULNERABILITY_TIME;

                for (int j = 0; j < MAX_ENEMY_BULLETS; j++)
                {
                    enemy_bullets[j].active = false;
                }

                return;
            }
        }
    }
}
void UnloadBoss(Boss *boss)
{
    UnloadBossSprites(&boss->sprites);
}

void BossTakeUltDamage(int damage)
{
    if (g_boss == NULL)
    {
        return;
    }

    g_boss->health -= damage;
    if (g_boss->health < 0)
    {
        g_boss->health = 0;
    }
}