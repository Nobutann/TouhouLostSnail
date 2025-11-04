#include "sprite.h"
#include <stdlib.h>

static Texture2D* LoadTextureArray(const char **filepaths, int count)
{
    Texture2D *textures = (Texture2D*)MemAlloc(sizeof(Texture2D) * count);

    for (int i = 0; i < count; i++)
    {
        textures[i] = LoadTexture(filepaths[i]);
    }

    return textures;
}

static Texture2D* UnloadTextureArray(Texture2D *textures, int count)
{
    for (int i = 0; i < count; i++)
    {
        UnloadTexture(textures[i]);
    }

    MemFree(textures);
}

void LoadPlayerSprites(PlayerSprites *player_sprites)
{
    const char *idlepath[] = 
    {
        "assets/reimuidle/reimuidle-1.png",
        "assets/reimuidle/reimuidle-2.png",
        "assets/reimuidle/reimuidle-3.png",
        "assets/reimuidle/reimuidle-4.png",
        "assets/reimuidle/reimuidle-5.png",
        "assets/reimuidle/reimuidle-6.png",
        "assets/reimuidle/reimuidle-7.png",
        "assets/reimuidle/reimuidle-8.png",
    };

    int idle_frame_count = sizeof(idlepath);
    player_sprites->idle.frames = LoadTextureArray(idlepath, idle_frame_count);
    player_sprites->idle.frame_count = idle_frame_count;
    player_sprites->idle.frame_time = 0.15f;
    player_sprites->idle.current_frame = 0;
    player_sprites->idle.timer = 0.0f;

    const char *rightpath[] = 
    {
        "assets/reimuright/reimuright-1.png",
        "assets/reimuright/reimuright-2.png",
        "assets/reimuright/reimuright-3.png",
        "assets/reimuright/reimuright-4.png",
        "assets/reimuright/reimuright-5.png",
        "assets/reimuright/reimuright-6.png",
        "assets/reimuright/reimuright-7.png",
        "assets/reimuright/reimuright-8.png",
    };

    int right_frame_count = sizeof(rightpath);
    player_sprites->fly_right.frames = LoadTextureArray(rightpath, right_frame_count);
    player_sprites->fly_right.frame_count = right_frame_count;
    player_sprites->fly_right.frame_time = 0.15;
    player_sprites->fly_right.current_frame = 0;
    player_sprites->fly_right.timer = 0.0f;

    const char *leftpath[] = 
    {
        "assets/reimuleft/reimuleft-1.png",
        "assets/reimuleft/reimuleft-2.png",
        "assets/reimuleft/reimuleft-3.png",
        "assets/reimuleft/reimuleft-4.png",
        "assets/reimuleft/reimuleft-5.png",
        "assets/reimuleft/reimuleft-6.png",
        "assets/reimuleft/reimuleft-7.png",
        "assets/reimuleft/reimuleft-8.png",
        "assets/reimuleft/reimuleft-9.png",
    };

    int left_frame_count = sizeof(leftpath);
    player_sprites->fly_left.frames = LoadTextureArray(leftpath, left_frame_count);
    player_sprites->fly_left.frame_count = left_frame_count;
    player_sprites->fly_left.frame_time = 0.15f;
    player_sprites->fly_left.current_frame = 0;
    player_sprites->fly_right.timer = 0.0f;
}

void UnloadPlayerSprites(PlayerSprites *player_sprites)
{
    UnloadTextureArray(player_sprites->idle.frames, player_sprites->idle.frame_count);
    UnloadTextureArray(player_sprites->fly_right.frames, player_sprites->fly_right.frame_count);
    UnloadTextureArray(player_sprites->fly_left.frames, player_sprites->fly_left.frame_count);
}

void UpdateAnimation(Animation *anim, float dt)
{
    anim->timer += dt;

    if (anim->timer >= anim->frame_time)
    {
        anim->timer = 0.0f;
        anim->current_frame++;
        if (anim->current_frame >= anim->frame_count)
        {
            anim->current_frame = 0;
        }
    }
}

void DrawAnimationFrame(Animation *anim, Vector2 position, float scale, Color tint)
{
    if (anim -> frames != NULL && anim->frame_count > 0)
    {
        DrawTextureEx(anim->frames[anim->current_frame], position, 0.0f, scale, tint);
    }
}