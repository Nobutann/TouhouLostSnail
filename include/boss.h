#ifndef BOSS_H
#define BOSS_H

#include "raylib.h"
#include "sprite.h"
#include "bullets.h"

#define BASE_SPEED 1000.0f

typedef struct
{
    int health;
    Vector2 position;
    float speed;
    PlayerSprites sprites; 
    float shoot_timer;
    Vector2 homePosition;     
    Vector2 ai_direction;     
    float ai_moveTimer;
} BOSS; 

void InitBoss(BOSS *boss, Vector2 initial_pos, float speed);
void UpdateBoss(BOSS *boss, float dt, Bullet *bullets, Sound shoot_sound);
void DrawBoss(BOSS *boss);
void UnloadBoss(BOSS *boss); 
void BossShoot(BOSS *boss, Bullet *bullets);

#endif