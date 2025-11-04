#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"

typedef struct
{
    Texture2D *frames;
    int frame_count;
} Animation;

typedef struct
{
    Animation idle;
    Animation fly_left;
    Animation fly_right;
    float frame_change;
    float timer;
    Animation *current_anim;
} PlayerSprites;

Animation LoadAnimation(const char *base_path, int frame_count);

#endif