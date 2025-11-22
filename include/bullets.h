#ifndef BULLETS_H
#define BULLETS_H

#include "raylib.h"

#define MAX_BULLETS 100
#define BULLET_SPEED 2000
#define MAX_ENEMY_BULLETS 1000
#define PLAYER_BULLET_HITBOX 8.0f


typedef struct
{
    Vector2 position;
    Vector2 velocity;
    Texture2D sprite;
    bool active;
} Bullet;

typedef enum
{
    BULLET_TYPE_NORMAL,
    BULLET_TYPE_AIMED,
    BULLET_TYPE_CURVE,
    BULLET_TYPE_ACCEL
} EnemyBulletType;

typedef struct
{
    Vector2 position;
    Vector2 velocity;
    float angle;
    float speed;
    EnemyBulletType type;
    Texture2D sprite;
    float lifetime;
    bool active;
    float radius;
} EnemyBullet;

void InitBullet(Bullet *bullets, Texture2D sprite);
void UpdateBullets(Bullet *bullets, float dt);
void DrawBullets(Bullet *bullets);

void InitEnemyBullets(EnemyBullet *bullets);
void SpawnEnemyBullet(EnemyBullet *bullets, Vector2 position, float angle, float speed, EnemyBulletType type, Texture2D sprite);
void UpdateEnemyBullets(EnemyBullet *bullets, float dt);
void DrawEnemyBullets(EnemyBullet *bullets);

void ClearAllBullets(void);
void DisableBullets(void);
void EnableBullets(void);

#endif