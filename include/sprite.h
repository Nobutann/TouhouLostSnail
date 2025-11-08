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

void LoadPlayerSprites(PlayerSprites *player_sprites);
void UnloadPlayerSprites(PlayerSprites *player_sprites);
void LoadBossSprites(PlayerSprites *player_sprites);
void UnloadBossSprites(PlayerSprites *player_sprites);
void UpdateAnimation(Animation *anim, float dt);
void DrawAnimationFrame(Animation *anim, Vector2 position, float scale, Color tint);
void LoadMapSprites(Animation *map);
void UnloadMapSprites(Animation *map);

#endif