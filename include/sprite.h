#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"

typedef struct
{
    Texture2D *frames;
    int frame_count;
    int current_frame;
    float frame_time;
    float timer;
} Animation;

typedef struct
{
    Animation idle;
    Animation fly_left;
    Animation fly_right;
} PlayerSprites;

typedef struct
{
    Animation idle;
    Animation direction;
} BossSprites;

typedef struct
{
    Texture2D bullet_red;
    Texture2D bullet_pink;
    Texture2D bullet_orange;
    Texture2D bullet_yellow_glow;
    Texture2D bullet_blue_outline;
    Texture2D bullet_blue_solid;
} BossAssets;

void LoadPlayerSprites(PlayerSprites *player_sprites);
void UnloadPlayerSprites(PlayerSprites *player_sprites);

void LoadBossSprites(BossSprites *boss_sprites);
void UnloadBossSprites(BossSprites *boss_sprites);

void UpdateAnimation(Animation *anim, float dt);
void DrawAnimationFrame(Animation *anim, Vector2 position, float scale, Color tint);

void LoadMapSprites(Animation *map);
void UnloadMapSprites(Animation *map);

#endif