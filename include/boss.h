#ifndef BOSS_H
#define BOSS_H

#include "raylib.h"
#include "sprite.h"
#include "bullets.h"
#include "player.h"

#define BOSS_HEALTH_NONSPELL1 3000.0f
#define BOSS_HEALTH_SPELL1 4500.0f
#define BOSS_HEALTH_NONSPELL2 3500.0f
#define BOSS_HITBOX_RADIUS 20.0f
#define PLAYER_BULLET_DAMAGE 10.0f
#define INVULNERABILITY_TIME 3.0f

typedef enum
{
    BOSS_PHASE_NONSPELL1,
    BOSS_PHASE_SPELL1,
    BOSS_PHASE_NONSPELL2,
    BOSS_PHASE_SPELL2,
    BOSS_PHASE_NONSPELL3,
    BOSS_PHASE_SPELL3,
    BOSS_PHASE_NONSPELL4,
    BOSS_PHASE_SPELL4,
    BOSS_PHASE_DEFEATED
} BossPhase;

typedef struct
{
    Vector2 position;
    Vector2 target_position;
    Vector2 last_position;
    float health;
    float max_health;
    BossPhase current_phase;
    BossSprites sprites;
    int frame_counter;
    float move_timer;
    bool is_moving;
} Boss;

void InitBoss(Boss *boss, Vector2 initial_pos);
void UpdateBoss(Boss *boss, float dt, EnemyBullet *enemy_bullets, Vector2 player_pos, BossAssets *assets);
void DrawBoss(Boss *boss);
void UnloadBoss(Boss *boss);

void CheckPlayerVsBoss(Boss *boss, Bullet *player_bullets);
void CheckBossVsPlayer(Player *player, EnemyBullet *enemy_bullets);

void NonSpell1(Boss *boss, EnemyBullet *enemy_bullets, Vector2 player_pos, BossAssets *assets);
void SpellCard1(Boss *boss, EnemyBullet *enemy_bullets, Vector2 player_pos, BossAssets *assets);

#endif