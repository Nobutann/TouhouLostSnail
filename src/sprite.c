#include "sprite.h"
#include <stdlib.h>
#include <stdio.h>

Animation LoadAnimation(const char *base_path, int frame_count)
{
    Animation animation;
    animation.frame_count = frame_count;

    animation.frames = (Texture2D*)malloc(frame_count *sizeof(Texture2D));

    for (int i = 0; i < frame_count; i++)
    {
        char filepath[260];
        snprintf(filepath, sizeof(filepath), "%s-%d.png", base_path, i + 1);

        animation.frames[i] = LoadTexture(filepath);
    }

    return animation;
}

PlayerSprites LoadPlayerSprites(const char *idle_path, const char *left_path, const char *right_path, int idle_frames, int left_frames, int right_frames, float frame_change)
{
    PlayerSprites player;

    player.idle = LoadAnimation(idle_path, idle_frames);
    player.fly_left = LoadAnimation(left_path, left_frames);
    player.fly_right = LoadAnimation(right_path, right_frames);

    player.frame_change = frame_change;
}