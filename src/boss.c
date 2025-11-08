#include "boss.h"
#include <math.h>
#include "bullets.h"
#include "raymath.h"
#include "sprite.h"
#include <stdlib.h> 

#define FIRE_RATE 0.066f /* 15 tiros por segundo */
#define BULLET_DISTANCE_X 8
#define BULLET_DISTANCE_Y 20
#define BOSS_CENTER 15 

#define AI_CHANGE_TIME_MIN 1.0f 
#define AI_CHANGE_TIME_MAX 3.0f 
#define CHANCE_MUDAR_Y 20      


#define BOSS_X_MIN 50.0f       
#define BOSS_X_MAX 1230.0f     
#define BOSS_Y_MIN 20.0f        
#define BOSS_Y_MAX 200.0f       


void InitBoss(BOSS *boss, Vector2 initial_pos, float speed) 
{
    boss->position = initial_pos;
    boss->speed = speed;
    boss->shoot_timer = 0.0f; 
    
    boss->ai_direction = (Vector2){ 0, 0 }; 
    boss->ai_moveTimer = 0.0f; 
    
    LoadBossSprites(&boss->sprites); 
}


void UpdateBoss(BOSS *boss, float dt, Bullet *bullets, Sound shoot_sound)
{

    boss->ai_moveTimer -= dt;

    
    if (boss->ai_moveTimer <= 0.0f)
    {
        
        float randTime = (rand() % (int)((AI_CHANGE_TIME_MAX - AI_CHANGE_TIME_MIN) * 100)) / 100.0f;
        boss->ai_moveTimer = AI_CHANGE_TIME_MIN + randTime;

       
        float new_x;
        float new_y = 0.0f; 

        
        if (boss->position.x > BOSS_X_MAX)
        {
            new_x = -1.0f; 
        }
        else if (boss->position.x < BOSS_X_MIN)
        {
            new_x = 1.0f; 
        }
        else
        {
           
            new_x = (float)(rand() % 3) - 1.0f; 
        }

        if ((rand() % 100) < CHANCE_MUDAR_Y) 
        {
            if (boss->position.y > BOSS_Y_MAX)
            {
                new_y = -1.0f;
            }
            else if (boss->position.y < BOSS_Y_MIN)
            {
                new_y = 1.0f; 
            }
            else
            {
                new_y = (float)(rand() % 3) - 1.0f; 
            }
        }
        
        boss->ai_direction = (Vector2){new_x, new_y};
        if (Vector2Length(boss->ai_direction) != 0)
        {
            boss->ai_direction = Vector2Normalize(boss->ai_direction);
        }
    }
    
    Vector2 input = boss->ai_direction;

    boss->shoot_timer -= dt; 
    if (boss->shoot_timer <= 0.0f) 
    {
        BossShoot(boss, bullets); 
        boss->shoot_timer = FIRE_RATE; 
        PlaySound(shoot_sound);
    }

    boss->position.x += input.x * boss->speed * dt; 
    boss->position.y += input.y * boss->speed * dt;

    Animation *anim = &boss->sprites.idle; 
    if (input.x < 0)
    {
        anim = &boss->sprites.fly_left; 
    }
    else if (input.x > 0)
    {
        anim = &boss->sprites.fly_right; 
    }

    UpdateAnimation(anim, dt);
}

void DrawBoss(BOSS *boss) 
{
    Animation *anim = &boss->sprites.idle; 

    if (boss->ai_direction.x < 0)
    {
        anim = &boss->sprites.fly_left; 
    }
    else if (boss->ai_direction.x > 0)
    {
        anim = &boss->sprites.fly_right; 
    }

    DrawAnimationFrame(anim, boss->position, 2.0f, WHITE);
}

void BossShoot(BOSS *boss, Bullet *bullets) 
{
    Vector2 center = 
    {
        boss->position.x + boss->sprites.idle.frames[0].width / 2,
        boss->position.y + boss->sprites.idle.frames[0].height / 2 
    };

    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (!bullets[i].active)
        {
            bullets[i].position = (Vector2){center.x - BULLET_DISTANCE_X + BOSS_CENTER, center.y - BULLET_DISTANCE_Y}; 
            bullets[i].velocity = (Vector2){0, -BULLET_SPEED};
            bullets[i].active = true;
            break;
        }
    }

    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (!bullets[i].active)
        {
            bullets[i].position = (Vector2){ center.x + BULLET_DISTANCE_X + BOSS_CENTER, center.y - BULLET_DISTANCE_Y }; 
            bullets[i].velocity = (Vector2){0, -BULLET_SPEED};
            bullets[i].active = true;
            break;
        }
    }
}

void UnloadBoss(BOSS *boss) 
{
    UnloadBossSprites(&boss->sprites); 
}