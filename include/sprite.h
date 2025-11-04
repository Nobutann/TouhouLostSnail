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

static Texture2D* LoadTextureArray(const char **filepaths, int count);
static Texture2D* UnloadTextureArray(Texture2D *textures, int count);

#endif