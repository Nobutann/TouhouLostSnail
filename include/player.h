#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "sprite.h"
#include "bullets.h"
#include "screens.h"

#define BASE_SPEED 350.0f
#define HITBOX_RADIUS 3.0f

typedef struct HealthNode {
    struct HealthNode *next;
} HealthNode;

typedef struct UltsNode {
    struct UltsNode *next;
} UltsNode;

typedef struct
{
    HealthNode *healths;
    Vector2 position;
    float speed;
    PlayerSprites sprites;
    Vector2 hitbox_center;
    float shoot_timer;
    UltsNode *ults;
    bool is_invulnerable;
    float invul_timer;
} Player;

void InitPlayer(Player *player, Vector2 initial_pos, float speed);
void UpdatePlayer(Player *player, float dt, Bullet *bullets, Sound shoot_sound, BombProjectile *active_bombs);
void DrawPlayer(Player *player);
void UnloadPlayer(Player *player);
void PlayerShoot(Player *player, Bullet *bullets);
void LoseHealth(Player *player, GameScreen *current_screen);
void DrawHealths(Player *player);
void LoseUlts(Player *player);
void DrawUlts(Player *player);

#endif